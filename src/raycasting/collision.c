/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:27:00 by acardona          #+#    #+#             */
/*   Updated: 2023/09/20 02:58:27 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

static void	_r_ray_init_h_sub(double *sign_offset_x,
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

static void	_r_ray_init_h(t_coord *P, float angle_ray, t_coord *last_h,
	double *delta_h_x)
{
	double	sign_offset_x;

	if ((angle_ray >= M_PI / 2 - FLOAT_EPSILON && angle_ray <= M_PI / 2 + FLOAT_EPSILON)
			|| (angle_ray >= M_PI * 1.5 - FLOAT_EPSILON && angle_ray <= M_PI * 1.5 + FLOAT_EPSILON))
	{
		*last_h = (t_coord){-1, -1};
		*delta_h_x = 0;
		return ;
	}
	if (angle_ray >= 1.5 * M_PI || angle_ray < M_PI * 0.5) // cadran sup
	{
		_r_ray_init_h_sub(&sign_offset_x, &angle_ray);
		*delta_h_x = sign_offset_x * tan(angle_ray);
		if (P->y == ceil(P->y))
			P->y += FLOAT_EPSILON;
		last_h->y = ceil(P->y);
		last_h->x = P->x + *delta_h_x * (last_h->y - P->y);
	}
	else
	{
		_r_ray_init_h_sub(&sign_offset_x, &angle_ray);
		*delta_h_x = sign_offset_x * tan(angle_ray);
		if (P->y == floor(P->y))
			P->y -= FLOAT_EPSILON;
		last_h->y = floor(P->y);
		last_h->x = P->x + *delta_h_x * (P->y - last_h->y) ;
	}
}
static void	_r_ray_init_v_sub(double *sign_offset_y,
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

static void	_r_ray_init_v(t_coord *P, float angle_ray, t_coord *last_v,
	double *delta_h_y)
{
	double	sign_offset_y;

	if ((angle_ray >= -FLOAT_EPSILON && angle_ray <= FLOAT_EPSILON)
			|| (angle_ray >= M_PI - FLOAT_EPSILON && angle_ray <= M_PI + FLOAT_EPSILON))
	{
		*last_v = (t_coord){-1, -1};
		*delta_h_y = 0;
		return ;
	}
	if (angle_ray >= 0 && angle_ray < M_PI) // cadran droit
	{
		_r_ray_init_v_sub(&sign_offset_y, &angle_ray);
		if (P->x == ceil(P->x))
			P->x += FLOAT_EPSILON;
		last_v->x = ceil(P->x);
		*delta_h_y = sign_offset_y / tan(angle_ray);
		last_v->y = P->y + *delta_h_y * (last_v->x - P->x);
	}
	else
	{
		_r_ray_init_v_sub(&sign_offset_y, &angle_ray);
		if (P->x == floor(P->x))
			P->x -= FLOAT_EPSILON;
		last_v->x = floor(P->x);
		*delta_h_y = sign_offset_y / tan(angle_ray);
		last_v->y = P->y + *delta_h_y * (last_v->x - P->x);
	}
}

float	r_norme2(t_coord P1, t_coord P2) // inline
{
	return (sqrt(pow(P2.x - P1.x, 2) + pow(P2.y - P1.y, 2)));//opti ? x * x ou x^2
}

static t_coord	_r_ray_collision(t_type type, t_coord P, float angle_ray,
	t_data_tmp *data)
{
	t_coord				last_h;
	t_coord				last_v;
	double				delta_h_x;
	double				delta_v_y;
	t_coord				last;
	t_collision_history	history_h;
	t_collision_history	history_v;

	_r_ray_init_h(&P, angle_ray, &last_h, &delta_h_x);
	_r_ray_init_v(&P, angle_ray, &last_v, &delta_v_y);
	history_h = COL_FIRST;
	history_v = COL_FIRST;

	if (r_norme2(last_h, P) < r_norme2(last_v, P))
		last = last_h;
	else
		last = last_v;

	if (angle_ray < M_PI * 0.25 || angle_ray >= M_PI * 1.75 || (angle_ray >= M_PI * 0.75 && angle_ray < M_PI * 1.25)) // priorite incrementation vers le haut <=> delta_h_x
	{
		while (last.x <= data->x_max - 1 && last.x >= 1
			&& last.y <= data->y_max - 1 && last.y >= 1)//last est dans la map
		{
			if (delta_h_x > 0 && history_v != COL_LAST && last.x + delta_h_x > ceil(last.x))// cas  si on a croise une ligne verticale vers la droite     //opti? sauvegarder ceil
			{
				//calculer coordonnees de l'intersection avec ligne verticale
				if (history_v)//premiere verticale trouvee
				{
					last = last_v;
					history_v = COL_LAST;
				}
				else
				{
					last.x = last_v.x + 1;
					last.y = last_v.y + delta_v_y;
					last_v = last;
					history_v = COL_LAST;
				}
				if (data->map[(int)last.x][(int)last.y] == type)
					return (last);
			}
			else if (delta_h_x > 0)// on croise une horizontale vers la droite
			{
				if (history_h)//premiere verticale trouvee
				{
					last = last_h;
					history_h = 0;
				}
				else
				{
					last.y = last_h.y + 1;
					last.x = last_h.x + delta_h_x;
					last_h = last;
				}
				if (data->map[(int)last.x][(int)last.y - (angle_ray > M_PI * 0.5)] == type)
					return (last);
				history_v = COL_TOO_OLD;
			}
			else
			{
				printf("pas encore code vers la gauche haut verticale ou horizontale\n");
				break;
			}
		}
		return ((t_coord) {-1, -1});
	}
	else // priorite incrementation delta_v_y
	{
		printf("pas encore code pour cet angle\n");
		return ((t_coord) {-1, -1});
	}
}

//clear && cc -g collision.c -lm && ./a.out 12 

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

	t_data_tmp	data = {10, 10, map_};
	t_coord	co_p = {5, 5};
	float	angle_ray =  atof(av[1]) * M_PI / 180;//M_PI;//;
	printf("angle: %f (%f)\n\n", atof(av[1]), angle_ray);

	t_coord	result;
	result = _r_ray_collision(WALL, co_p, angle_ray, &data);
	printf("Resultat : (%lf, %lf)\n", result.x, result.y);

	return 0;
}