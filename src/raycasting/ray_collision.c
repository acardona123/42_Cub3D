/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:14:53 by acardona          #+#    #+#             */
/*   Updated: 2023/09/22 15:20:09 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

static void	_r_ray_init_h(t_coord *P, float angle_ray, t_coord *last_h,
	t_vector *delta_h)
{
	if ((angle_ray >= M_PI / 2 - FLOAT_EPSILON && angle_ray <= M_PI / 2 + FLOAT_EPSILON)
			|| (angle_ray >= M_PI * 1.5 - FLOAT_EPSILON && angle_ray <= M_PI * 1.5 + FLOAT_EPSILON)) // (angle_ray == M_PI / 2 || angle_ray == M_PI * 1.5)
	{
		*last_h = (t_coord){-1, -1};
		*delta_h = (t_vector){0, 0};
		return ;
	}
	if (angle_ray >= 1.5 * M_PI || angle_ray < M_PI * 0.5) // cadran sup
	{
		*last_h = (t_coord){P->x + tan(angle_ray) * (ceil(P->y) - P->y), ceil(P->y)};
		*delta_h = (t_vector){tan(angle_ray), 1};
	}
	else
	{
		*last_h = (t_coord){P->x - tan(angle_ray) * (P->y - floor(P->y)), floor(P->y)};
		*delta_h = (t_vector){-tan(angle_ray), -1};
	}
}

static void	_r_ray_init_v(t_coord *P, float angle_ray, t_coord *last_v,
	t_vector *delta_v)
{
	if ((angle_ray >= - FLOAT_EPSILON && angle_ray <= FLOAT_EPSILON)
			|| (angle_ray >= M_PI - FLOAT_EPSILON && angle_ray <= M_PI + FLOAT_EPSILON)) // (angle_ray == 0 || angle_ray == M_PI)
	{
		*last_v = (t_coord){-1, -1};
		*delta_v = (t_vector){0, 0};
		return ;
	}
	if (angle_ray >= 0 && angle_ray < M_PI) // cadran droit
	{
		*last_v = (t_coord){ceil(P->x), P->y + (ceil(P->x) - P->x) / tan(angle_ray)};
		*delta_v = (t_vector){1, 1 / tan(angle_ray)};
	}
	else // gauche
	{
		*last_v = (t_coord){floor(P->x), P->y - (P->x - floor(P->x)) / tan(angle_ray)};
		*delta_v = (t_vector){-1, -1 / tan(angle_ray)};
	}
}

static bool	_r_point_inside_map_borders(t_data_map *data, t_coord *P)
{
	if (P->x < 1 || P->y < 1 || P->x > data->x_max - 1 || P->y > data->y_max)
		return (false);
	return (true);
}

static t_coord	_r_ray_collision(t_bloc_type type, t_coord P, float angle_ray,
	t_data_map *data)
{
	t_coord		last_h;
	t_coord		last_v;
	t_vector	delta_h;
	t_vector	delta_v;
	t_coord		last;

	_r_ray_init_h(&P, angle_ray, &last_h, &delta_h);
	_r_ray_init_v(&P, angle_ray, &last_v, &delta_v);
	if (to_vector_norm(P, last_v) > to_vector_norm(P, last_h))
	{
		last = last_h;
		last_v.x -= delta_v.x;
		last_v.y -= delta_v.y;
	}
	else
	{
		last = last_v;
		last_h.x -= delta_h.x;
		last_h.y -= delta_h.y;
	}
	if (!_r_point_inside_map_borders(data, &last))//ne peut pas arriver si le player est entre les murs de la map
		return ((t_coord){-1, -1});

	if (angle_ray < M_PI / 4) //N_NE
	{
		if (last.y != last_h.y)
		{
			if (data->map[(int)last.x][(int)last.y] == type)
				return (last_v);
			last = last_h;
		}
		while (last.y <= data->y_max - 1)
		{
			// to_vector_print(last);
			if (data->map[(int)last.x][(int)last.y] == type)
				return (last);
			last.x += delta_h.x;
			if (last_v.x != -1 && floor(last.x) != last_v.x)
			{
				last_v.x += delta_v.x;// <=> ++last_v.x
				if (last_v.x > data->x_max - 1)
					return ((t_coord){-1, -1});
				last_v.y += delta_v.y;
				// to_vector_print(last_v);
				// printf("map[%d][%d]=%c\n",(int)last_v.x, (int)last_v.y, data->map[(int)last_v.x][(int)last_v.y]);
				if (data->map[(int)last_v.x][(int)last_v.y] == type)
					return (last_v);
			}
			last.y += delta_h.y;//optimisable en ++last.y
		}
		return ((t_coord){-1, -1});
	}
	if (angle_ray < M_PI / 2) // NE_E
	{
		if (last.x != last_v.x)
		{
			if (data->map[(int)last.x][(int)last.y] == type)
				return (last_h);
			last = last_v;
		}
		while (last.x <= data->x_max - 1)
		{
			// to_vector_print(last);
			if (data->map[(int)last.x][(int)last.y] == type)
				return (last);
			last.y += delta_v.y;
			if (last_h.y != -1 && floor(last.y) != last_h.y)
			{
				last_h.y += delta_h.y;// <=> ++last_h.y
				if (last_h.y > data->y_max - 1)
					return ((t_coord){-1, -1});
				last_h.x += delta_h.x;
				if (data->map[(int)last_h.x][(int)last_h.y] == type)
					return (last_h);
			}
			last.x += delta_v.x;//optimisable en ++last.y
		}
		return ((t_coord){-1, -1});
	}
	if (angle_ray < M_PI * 0.75) // SE_E
	{
		if (last.x != last_v.x)
		{
			if (data->map[(int)last.x][(int)last.y - 1] == type)
				return (last_h);
			last = last_v;
		}
		while (last.x <= data->x_max - 1) // <=> < stricte
		{
			// to_vector_print(last);
			if (data->map[(int)last.x][(int)last.y] == type)
				return (last);
			last.y += delta_v.y;
			if (last_h.y != -1 && ceil(last.y) != last_h.y)
			{
				last_h.y += delta_h.y;// <=> ++last_h.y
				if (last_h.y < 1)
					return ((t_coord){-1, -1});
				last_h.x += delta_h.x;
				if (data->map[(int)last_h.x][(int)last_h.y - 1] == type)
					return (last_h);
			}
			last.x += delta_v.x;//optimisable en ++last.y
		}
		return ((t_coord){-1, -1});
	}
	if (angle_ray < M_PI) // S_SE
	{
		if (last.y != last_h.y)
		{
			if (data->map[(int)last.x][(int)last.y] == type)
				return (last_v);
			last = last_h;
		}
		while (last.y >= 1.)
		{
			// to_vector_print(last);
			if (data->map[(int)last.x][(int)last.y - 1] == type)
				return (last);
			last.x += delta_h.x;
			if (last_v.x != -1 && floor(last.x) != last_v.x)
			{
				last_v.x += delta_v.x;// <=> ++last_v.x
				if (last_v.x > data->x_max - 1)
					return ((t_coord){-1, -1});
				last_v.y += delta_v.y;
				if (data->map[(int)last_v.x][(int)last_v.y] == type)
					return (last_v);
			}
			last.y += delta_h.y;//optimisable en ++last.y
		}
		return ((t_coord){-1, -1});
	}
	if (angle_ray < M_PI * 1.25) // S_SO
	{
		if (last.y != last_h.y)
		{
			if (data->map[(int)last.x - 1][(int)last.y] == type)
				return (last_v);
			last = last_h;
		}
		while (last.y >= 1.)
		{
			// to_vector_print(last);
			if (data->map[(int)last.x][(int)last.y - 1] == type)
				return (last);
			last.x += delta_h.x;
			if (last_v.x != -1 && ceil(last.x) != last_v.x)
			{
				last_v.x += delta_v.x;// <=> --last_v.x
				if (last_v.x < 1)
					return ((t_coord){-1, -1});
				last_v.y += delta_v.y;
				if (data->map[(int)last_v.x - 1][(int)last_v.y] == type)
					return (last_v);
			}
			last.y += delta_h.y;//optimisable en ++last.y
		}
		return ((t_coord){-1, -1});
	}
	if (angle_ray < M_PI * 1.5) // O_SO
	{
		if (last.x != last_v.x)
		{
			if (data->map[(int)last.x][(int)last.y - 1] == type)
				return (last_h);
			last = last_v;
		}
		while (last.x >= 1.)
		{
			// to_vector_print(last);
			if (data->map[(int)last.x - 1][(int)last.y] == type)
				return (last);
			last.y += delta_v.y;
			if (last_h.y != -1 && ceil(last.y) != last_h.y)
			{
				last_h.y += delta_h.y;// <=> --last_h.y
				if (last_h.y < 1)
					return ((t_coord){-1, -1});
				last_h.x += delta_h.x;
				if (data->map[(int)last_h.x][(int)last_h.y - 1] == type)
					return (last_h);
			}
			last.x += delta_v.x;//optimisable en --last.x
		}
		return ((t_coord){-1, -1});
	}
	if (angle_ray < M_PI * 1.75) // O_NO
	{
		if (last.x != last_v.x)
		{
			if (data->map[(int)last.x][(int)last.y] == type)
				return (last_h);
			last = last_v;
		}
		while (last.x >= 1.)
		{
			// to_vector_print(last);
			if (data->map[(int)last.x - 1][(int)last.y] == type)
				return (last);
			last.y += delta_v.y;
			if (last_h.y != -1 && floor(last.y) != last_h.y)
			{
				last_h.y += delta_h.y;// <=> ++last_h.y
				if (last_h.y > data->y_max - 1)
					return ((t_coord){-1, -1});
				last_h.x += delta_h.x;
				if (data->map[(int)last_h.x][(int)last_h.y] == type)
					return (last_h);
			}
			last.x += delta_v.x;//optimisable en --last.x
		}
		return ((t_coord){-1, -1});
	}
	else // N_NO
	{
		if (last.y != last_h.y)
		{
			if (data->map[(int)last.x - 1][(int)last.y] == type)
				return (last_v);
			last = last_h;
		}
		while (last.y <= data->y_max - 1)
		{
			// to_vector_print(last);
			if (data->map[(int)last.x][(int)last.y] == type)
				return (last);
			last.x += delta_h.x;
			if (last_v.x != -1 && ceil(last.x) != last_v.x)
			{
				last_v.x += delta_v.x;// <=> ++last_v.x
				if (last_v.x < 1)
					return ((t_coord){-1, -1});
				last_v.y += delta_v.y;
				if (data->map[(int)last_h.x - 1][(int)last_h.y] == type)
					return (last_v);
			}
			last.y += delta_h.y;//optimisable en ++last.y
		}
		return ((t_coord){-1, -1});
	}
	return ((t_coord){-1, -1});
}

int	main(int ac, char **av)
{
	char	*y9 = "1111111111";
	char	*y8 = "1000000001";
	char	*y7 = "1000000001";
	char	*y6 = "1001000101";
	char	*y5 = "1000000001";
	char	*y4 = "1000000001";
	char	*y3 = "1000000001";
	char	*y2 = "1001000101";
	char	*y1 = "1000000001";
	char	*y0 = "1111111111";
	char	*map[10] = {y0, y1, y2, y3, y4, y5, y6, y7, y8, y9};

	char *map_transposee[10];
	int	i = -1;
	while ( ++i < 10)
	{
		map_transposee[i] = malloc(10 * sizeof(char));
		for(int j = 0; j < 10; j++)
		{
			map_transposee[i][j] = map[j][i];
		}
	}

	t_data_map	data = {10, 10, (char **)map_transposee};
	t_coord	co_p = {atof(av[1]), atof(av[2])};
	
	float	angle_ray = 0;
	while(angle_ray < 360)
	{
		printf("\nangle %.0f: ", angle_ray);
	// printf("toto\n");
		to_vector_print(_r_ray_collision(WALL, co_p, angle_ray * M_PI / 180, &data));
		angle_ray += 10;
	}

	while (--i >= 0)
		free(map_transposee[i]);
	
	return (0);
}
