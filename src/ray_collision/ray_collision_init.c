/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:50:56 by acardona          #+#    #+#             */
/*   Updated: 2023/10/25 04:23:03 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

static void			_r_ray_init_h(t_coord_f *p_co, t_ray_data *rdata,
						float angle_ray, t_init_chunks *chunks);
static void			_r_ray_init_v(t_coord_f *p_co, t_ray_data *rdata,
						float angle_ray, t_init_chunks *chunks);
static t_1st_type	_r_ray_init_hitpoint(t_coord_f *pco, t_ray_data *rdata,
						t_hitpoint *hitpt, t_init_chunks *chunks);
static t_1st_type	_r_ray_init_get_first_type(t_coord_f *pco,
						t_ray_data *rdata);

/**
 * @brief calculates the parameters used too check the ray intersection with the
 *		grid (deltas between consecutive horizontal/vertical line) set hitpoint
 *		float coordonites to the intersection with the closet
 *		vertical/hirizontal grid line. 
 * 
 * @param p_co player coordinates
 * @param angle_ray angle of the ray in rad
 * @param map pointer to the map structure
 * @param rdata structure that will be used for the ray propagation calculation
 * @return t_hitpoint , empty except for the pt_co that are set to the first
 *		intersection point with the grid
 */
t_hitpoint	r_ray_init_rdata_hitpoint(t_coord_f *p_co, float angle_ray,
	t_map *map, t_ray_data *rdata)
{
	t_hitpoint		hitpoint;
	t_init_chunks	init_chunks;

	init_chunks.init0_hx = 0;
	init_chunks.init0_hy = 0;
	init_chunks.init0_vx = 0;
	init_chunks.init0_vy = 0;
	_r_ray_init_h(p_co, rdata, angle_ray, &init_chunks);
	_r_ray_init_v(p_co, rdata, angle_ray, &init_chunks);
	rdata->first = _r_ray_init_hitpoint(p_co, rdata, &hitpoint, &init_chunks);
	if (angle_ray >= M_PI / 2 && angle_ray < 3 * M_PI / 2
		&& (((floor(p_co->x) + rdata->shift == p_co->x
					&& (floor(p_co->y) + rdata->shift == p_co->y
						|| ceil(p_co->y) - rdata->shift == p_co->y)))
			|| (ceil(p_co->x) - rdata->shift == p_co->x
				&& (floor(p_co->y) + rdata->shift == p_co->y
					|| ceil(p_co->y) - rdata->shift == p_co->y))))
		--hitpoint.chunk_co_y;
	if (hitpoint.pt_co.x >= 0. && r_point_outside_map(map, hitpoint.pt_co))//ne peut pas arriver si le player est entre les murs de la map
		hitpoint.pt_co.x = -1;
	return (hitpoint);
}

/**
 * @brief calculates the coordonites of the first intersecton between the ray
 *		and a horizontal line and calculate the x step when jumping
 *		from one horizontal line to the next one
 * 
 * @param p_co coordonites of the player
 * @param rdata structure that will be partially completed
 * @param angle_ray angle of the ray in rad
 */
static void	_r_ray_init_h(t_coord_f *p_co, t_ray_data *rdata, float angle_ray,
	t_init_chunks *chunks)
{
	float	tan_a;
	float	round_y;

		rdata->check_h = false;
	if ((angle_ray > M_PI / 2 - EPSILON && angle_ray < M_PI / 2 + EPSILON) || \
		(angle_ray > M_PI * 1.5 - EPSILON && angle_ray < M_PI * 1.5 + EPSILON))
		return ;
	rdata->check_h = true;
	tan_a = tan(angle_ray);
	if (angle_ray > 1.5 * M_PI || angle_ray < M_PI * 0.5) // cadran sup
	{
		rdata->delta_x = tan_a;
		round_y = ceil(p_co->y + rdata->shift) - rdata->shift;
		chunks->init0_hy = (int)(p_co->y + rdata->shift) + ((rdata->shift && \
		p_co->y != round_y) || (!rdata->shift && p_co->y != floor(p_co->y)));
	}
	else
	{
		rdata->delta_x = -tan_a;
		round_y = floor(p_co->y - rdata->shift) + rdata->shift;
		chunks->init0_hy = (int)(p_co->y - rdata->shift) - 1;
	}
	rdata->last_h.x = p_co->x + tan_a * (round_y - p_co->y);
	rdata->last_h.y = round_y;
	chunks->init0_hx = (int)rdata->last_h.x;
}

/**
 * @brief calculates the coordonites of the first intersecton between the ray
 *		and a vertical line; and calculates the y step when jumping
 *		from one vertical line to the next one
 * 
 * @param P coordonites of the player
 * @param rdata structure that will be partially completed
 * @param angle_ray angle of the ray in rad
 */
static void	_r_ray_init_v(t_coord_f *p_co, t_ray_data *rdata, float angle_ray,
	t_init_chunks *chunks)
{
	register float	ratio_tan_a;
	register float	round_x;

	rdata->check_v = false;
	if (angle_ray > 2 * M_PI - EPSILON || angle_ray < EPSILON
		|| (angle_ray > M_PI - EPSILON && angle_ray < M_PI + EPSILON))
		return ;
	rdata->check_v = true;
	ratio_tan_a = 1. / tan(angle_ray);
	if (angle_ray < M_PI) // cadran droit
	{
		rdata->delta_y = ratio_tan_a;
		round_x = ceil(p_co->x + rdata->shift) - rdata->shift;
		chunks->init0_vx = (int)(p_co->x + rdata->shift) + ((rdata->shift && \
		p_co->x != round_x) || (!rdata->shift && p_co->x != floor(p_co->x)));
	}
	else // gauche
	{
		rdata->delta_y = -ratio_tan_a;
		round_x = floor(p_co->x - rdata->shift) + rdata->shift;
		chunks->init0_vx = (int)(p_co->x - rdata->shift) - 1;
	}
	rdata->last_v.x = round_x;
	rdata->last_v.y = p_co->y + (round_x - p_co->x) * ratio_tan_a;
	chunks->init0_vy = (int)rdata->last_v.y;
}

/**
 * @brief calculates the first intersection point between the grid and the ray,
 *		this pt is the starting point for the ray projection at the closest one.
 *		Modifies rdata accordingly.
 * 
 * @param p_co 
 * @param rdata 
 * @param hitpoint 
 */
static t_1st_type	_r_ray_init_hitpoint(t_coord_f *pco, t_ray_data *rdata,
	t_hitpoint *hitpt, t_init_chunks *chunks)
{
	t_1st_type	first_type;

	*hitpt = (t_hitpoint){0};
	first_type = _r_ray_init_get_first_type(pco, rdata);
	if (first_type == FIRST_H)//hits an horizontal first
	{
		hitpt->pt_co = rdata->last_h;
		hitpt->chunk_co_x = chunks->init0_hx;
		hitpt->chunk_co_y = chunks->init0_hy;
		if (rdata->dial >= E_SE && rdata->dial <= SW_W)//looks down
			return (hitpt->hit_face = FACE_N, FIRST_H);
		return (hitpt->hit_face = FACE_S, FIRST_H);
	}
	hitpt->pt_co = rdata->last_v;
	hitpt->chunk_co_x = chunks->init0_vx;
	hitpt->chunk_co_y = chunks->init0_vy;
	if (rdata->dial >= S_SW)
		hitpt->hit_face = FACE_E;
	else
		hitpt->hit_face = FACE_W;
	return (first_type);
}

static t_1st_type	_r_ray_init_get_first_type(t_coord_f *pco,
	t_ray_data *rdata)
{
	if (!rdata->check_h)
		return (FIRST_V);
	if (!rdata->check_v)
		return (FIRST_H);
	if (rdata->last_h.x > rdata->last_v.x - EPSILON
		&& rdata->last_h.x < rdata->last_v.x + EPSILON)
	{
		rdata->last_h.x = rdata->last_v.x;
		rdata->last_v.y = rdata->last_h.y;
		return (FIRST_IS_ANY);
	}
	if (pow(pco->x - rdata->last_v.x, 2.) + pow(pco->y - rdata->last_v.y, 2.)
		< pow(pco->x - rdata->last_h.x, 2.) + pow(pco->y - rdata->last_h.y, 2.))
		return (FIRST_V);
	return (FIRST_H);
}

/*
//==== tests _r_ray_init_h and _r_ray_init_v only ====
// https://www.geogebra.org/m/zw7kz29a

#include "../../includes/cub3d.h"

static void			_test_r_ray_init_h(t_coord_f *p_co, t_ray_data *rdata,
						float angle_ray);
static void			_test_r_ray_init_v(t_coord_f *p_co, t_ray_data *rdata,
						float angle_ray);
static void			_test_r_ray_init_rdata_hitpoint(t_coord_f *p_co,
						float angle_ray, t_map *map, t_ray_data *rdata);

int	main(int ac, char **av)
{
	t_general	gen;
	t_ray_data	rdata;
	float		angle_deg;

	gen = (t_general){0};

	init_main(ac, av, &gen);
	gen.player.p_co.x  += 0.5;
	gen.player.p_co.y += 0.5;
	printf("Player_co : (%f, %f)\n\n", gen.player.p_co.x, gen.player.p_co.y);
	// printf("new player data:\n co: (%f, %f)\nangle: %f (%f deg)\n\n",
	// 	gen.player.p_co.x, gen.player.p_co.y, gen.player.p_angle,
	// 	gen.player.p_angle * 180 / M_PI);
	angle_deg = 0.;
	while (angle_deg < 360.)
	{
		printf("\n-----------------------\nangle: %.2f (%.4f)\n\n", angle_deg,
			angle_deg * M_PI / 180.);

		printf("first h and first v detection :");
		_test_r_ray_init_h(&gen.player.p_co, &rdata, angle_deg * M_PI / 180.);
		_test_r_ray_init_v(&gen.player.p_co, &rdata, angle_deg * M_PI / 180.);

		printf("\nAfter selection:\n");
		_test_r_ray_init_rdata_hitpoint(&gen.player.p_co,
			angle_deg * M_PI / 180, &gen.map, &rdata);
		angle_deg += 5.;
	}
	return (0);
}

static void	_test_r_ray_init_h(t_coord_f *p_co, t_ray_data *rdata,
				float angle_ray)
{
	t_init_chunks	init_chunks;

	init_chunks.init0_hx = 0;
	init_chunks.init0_hy = 0;
	init_chunks.init0_vx = 0;
	init_chunks.init0_vy = 0;
	_r_ray_init_h(p_co, rdata, angle_ray, &init_chunks);
	printf("H:\n check_H: %d\n first_h: (%.4f, %.4f) -> first_h - (int)player :\
 (%.4f, %.4f)\n init_chunk_h: (%d, %d) -> init_chunk_h - (int)player: (%d,%d)\n\
 delta_x: %.4f\n",
		rdata->check_h,
		rdata->last_h.x, rdata->last_h.y,
		rdata->last_h.x - floor(p_co->x), rdata->last_h.y - floor(p_co->y),
		init_chunks.init0_hx, init_chunks.init0_hy,
		init_chunks.init0_hx - (int)p_co->x,
		init_chunks.init0_hy - (int)p_co->y,
		rdata->delta_x);
}

static void	_test_r_ray_init_v(t_coord_f *p_co, t_ray_data *rdata,
				float angle_ray)
{
	t_init_chunks	init_chunks;

	init_chunks.init0_hx = 0;
	init_chunks.init0_hy = 0;
	init_chunks.init0_vx = 0;
	init_chunks.init0_vy = 0;
	_r_ray_init_v(p_co, rdata, angle_ray, &init_chunks);
	printf("V:\n check_v: %d\n first_v: (%.4f, %.4f) -> first_v - (int)player :\
 (%.4f, %.4f)\n init_chunk_v: (%d, %d) -> init_chunk_h - (int)player: (%d,%d)\n\
 delta_y: %.4f\n",
		rdata->check_v,
		rdata->last_v.x, rdata->last_v.y,
		rdata->last_v.x - floor(p_co->x), rdata->last_v.y - floor(p_co->y),
		init_chunks.init0_vx, init_chunks.init0_vy,
		init_chunks.init0_vx - (int)p_co->x,
		init_chunks.init0_vy - (int)p_co->y,
		rdata->delta_y);
}

static void	_test_r_ray_init_rdata_hitpoint(t_coord_f *p_co, float angle_ray,
	t_map *map, t_ray_data *rdata)
{
	t_hitpoint	first;
	t_init_chunks	init_chunks;

	init_chunks.init0_hx = 0;
	init_chunks.init0_hy = 0;
	init_chunks.init0_vx = 0;
	init_chunks.init0_vy = 0;
	first = r_ray_init_rdata_hitpoint(p_co, angle_ray, map, rdata);
// 	printf("H:\n check_H: %d\n first_h: (%.4f, %.4f) -> delta_h - player :\
//  (%.4f, %.4f)\n delta_x: %.4f\n", rdata->check_h, rdata->last_h.x,
// 		rdata->last_h.y, rdata->last_h.x - floor(p_co->x),
// 		rdata->last_h.y - floor(p_co->y), rdata->delta_x);
// 	printf("V:\n check_v: %d\n first_v: (%.4f, %.4f) -> delta_v - player :\
//  (%.4f, %.4f)\n delta_y: %.4f\n", rdata->check_v, rdata->last_v.x,
// 		rdata->last_v.y, rdata->last_v.x - floor(p_co->x),
// 		rdata->last_v.y - floor(p_co->y), rdata->delta_y);
	printf("\nFirst hitpoint:\n prio: %c\n pt_co : (%.4f, %.4f) -> pt_co - \
player_co : (%.3f, %.3f)\n chunk_co: (%d, %d) -> chunk_co - player_co :\
 (%d, %d)\n face: %c\n",
		"HVA"[rdata->first],
		first.pt_co.x, first.pt_co.y,
		first.pt_co.x - floor(p_co->x), first.pt_co.y - floor(p_co->y),
		first.chunk_co_x, first.chunk_co_y,
		first.chunk_co_x - (int)p_co->x, first.chunk_co_y - (int)p_co->y,
		"NESW"[first.hit_face]);
}

*/