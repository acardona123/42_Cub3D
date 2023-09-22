/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_naive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:04:34 by acardona          #+#    #+#             */
/*   Updated: 2023/09/22 15:20:09 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

#include <stdio.h>//


static void	_r_ray_collision_vertical_sub(float *sign_offset_y,
	float *angle_ray)
{
	if (*angle_ray < M_PI / 2)
		*sign_offset_y = 1;
	else if (*angle_ray < M_PI)
	{
		*angle_ray = M_PI - *angle_ray;
		*sign_offset_y = -1;
	}
	else if (*angle_ray < M_PI * 1.5)
	{
		*angle_ray = *angle_ray - M_PI;
		*sign_offset_y = -1;
	}
	else
	{
		*angle_ray = 2 * M_PI - *angle_ray;
		*sign_offset_y = 1;
	}
}

static t_coord	_r_ray_collision_vertical(t_bloc_type type, t_coord P,
	float angle_ray, t_data_map *data)
{
	float	x;
	float	y;
	float	sign_offset_y;
	float	ratio;

	if ((angle_ray >= -FLOAT_EPSILON && angle_ray <= FLOAT_EPSILON)
			|| (angle_ray >= M_PI - FLOAT_EPSILON && angle_ray <= M_PI + FLOAT_EPSILON))
		return ((t_coord){-1, -1});

	if (angle_ray >= 0 && angle_ray < M_PI) // cadran droit
	{
		_r_ray_collision_vertical_sub(&sign_offset_y, &angle_ray);
		x = ceil(P.x);
		ratio = sign_offset_y / tan(angle_ray);
		y = P.y +(x - P.x) * ratio;
		while (x <= data->x_max && y >= 1 && y <= data->y_max - 1)
		{
			if (data->map[(int)x][(int)y] == type)
				return ((t_coord){x, y});
			++x;
			y = P.y + (x - P.x) * ratio;
		}
	}
	else // cadran gauche
	{
		_r_ray_collision_vertical_sub(&sign_offset_y, &angle_ray);
									//printf("ici: sign = %f, angle = %f\n", sign_offset_y, angle_ray * 180 / M_PI);
		x = floor(P.x);
		ratio = sign_offset_y / tan(angle_ray);
		y = P.y + (P.x - x) * ratio;
									//printf("x, y = (%f , %f), tan=%f, (x - P.x) / tan(angle_ray) = %f\n", x, y, tan(angle_ray), (x - P.x) / tan(angle_ray));//
		while (x > 0 && y >= 1 && y <= data->y_max - 1)
		{
										//printf("map[%d][%d] = %c\n", (int)x - 1, (int)y, data->map[(int)x - 1][(int)y]);//
			if (data->map[(int)x - 1][(int)y] == type)
				return ((t_coord){x, y});
			--x;
			y = P.y + (P.x - x) * ratio;
										//printf("\ntan...=%f\n", (P.x - x) / tan(angle_ray));
										//printf("x, y = (%f , %f) -> ", x, y);//
		}
	}
	return ((t_coord){-1, -1});
}

static void	_r_ray_collision_horizontal_sub(float *sign_offset_x,
	float *angle_ray)
{
	if (*angle_ray < M_PI / 2)
		*sign_offset_x = 1;
	else if (*angle_ray < M_PI)
	{
		*angle_ray = M_PI - *angle_ray;
		*sign_offset_x = 1;
	}
	else if (*angle_ray < M_PI * 1.5)
	{
		*angle_ray = *angle_ray - M_PI;
		*sign_offset_x = -1;
	}
	else
	{
		*angle_ray = 2 * M_PI - *angle_ray;
		*sign_offset_x = -1;
	}
}

static t_coord	_r_ray_collision_horizontal(t_bloc_type type, t_coord P,
	float angle_ray, t_data_map *data)
{
	float	x;
	float	y;
	float	sign_offset_x;
	float	ratio;

	if ((angle_ray >= M_PI / 2 - FLOAT_EPSILON && angle_ray <= M_PI / 2 + FLOAT_EPSILON)
			|| (angle_ray >= M_PI * 1.5 - FLOAT_EPSILON && angle_ray <= M_PI * 1.5 + FLOAT_EPSILON))
		return ((t_coord){-1, -1});

	if (angle_ray >= 1.5 * M_PI || angle_ray < M_PI * 0.5) // cadran sup
	{
		_r_ray_collision_horizontal_sub(&sign_offset_x, &angle_ray);
		y = ceil(P.y);
		ratio = sign_offset_x * tan(angle_ray);
		x = P.x + (y - P.y) * ratio;
		while (y <= data->y_max - 1 && x > 0 && x <= data->x_max - 1)
		{
			if (data->map[(int)x][(int)y] == type)
				return ((t_coord){x, y});
			++y;
			x = P.x + (y - P.y) * ratio;
		}
	}
	else // cadran inf
	{
		_r_ray_collision_horizontal_sub(&sign_offset_x, &angle_ray);
		y = floor(P.y);
		ratio = sign_offset_x * tan(angle_ray);
		x = P.x + (P.y - y) * ratio;
		while (y > 0 && x >= 1 && x < data->x_max - 1)
		{
			if (data->map[(int)x][(int)y - 1] == type)
				return ((t_coord){x, y});
			--y;
			x = P.x + (P.y - y) * ratio;
		}
	}
	return ((t_coord){-1, -1});
}

float	r_norme2(t_coord P1, t_coord P2)
{
	return (sqrt(pow(P2.x - P1.x, 2) + pow(P2.y - P1.y, 2)));
}


//clear && cc -g hit_elem_naive.c -lm && ./a.out 62 && rm a.out

int	main(int ac, char **av)
{
	char	*x0 = "1111111111";
	char	*x1 = "1000000001";
	char	*x2 = "1000000001";
	char	*x3 = "1000000001";
	char	*x4 = "1000000001";
	char	*x5 = "1000000001";
	char	*x6 = "1000000001";
	char	*x7 = "1000000001";
	char	*x8 = "1000000001";
	char	*x9 = "1111111111";
	char	*map_[10] = {x0, x1, x2, x3, x4, x5, x6, x7, x8, x9};

	t_data_map	data = {10, 10, map_};
	t_coord	co_p = {5, 5};
	float	angle_ray =  atof(av[1]) * M_PI / 180;//M_PI;//;
	printf("angle: %f (%f)\n", atof(av[1]), angle_ray);

	t_coord	result_vertical;
	result_vertical = _r_ray_collision_vertical(WALL, co_p, angle_ray, &data);
	printf("Result_vertical : (%f, %f)\n", result_vertical.x, result_vertical.y);

	t_coord	result_horizontal;
	result_horizontal = _r_ray_collision_horizontal(WALL, co_p, angle_ray, &data);
	printf("Result_horizontal : (%f, %f)\n", result_horizontal.x, result_horizontal.y);

	if ((result_horizontal.x == -1 && result_horizontal.y == -1)
		|| r_norme2(co_p, result_vertical) < r_norme2(co_p, result_horizontal))
		printf("plus proche = vertical\n");
	else
		printf("plus proche = horizontal\n");
	
	return 0;
}