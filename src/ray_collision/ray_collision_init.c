/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:50:56 by acardona          #+#    #+#             */
/*   Updated: 2023/11/10 16:05:28 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

static void			_r_ray_init_h(t_coord_f *p_co, t_ray_data *rdata,
						float angle_ray);
static void			_r_ray_init_v(t_coord_f *p_co, t_ray_data *rdata,
						float angle_ray);
static t_1st_type	_r_ray_init_hitpoint(t_coord_f *pco, t_ray_data *rdata,
						t_hitpoint *hitpt);
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

	_r_ray_init_h(p_co, rdata, angle_ray);
	_r_ray_init_v(p_co, rdata, angle_ray);
	rdata->first = _r_ray_init_hitpoint(p_co, rdata, &hitpoint);
	if (hitpoint.pt_co.x >= 0. && r_point_outside_map(map, hitpoint.pt_co))//ne peut pas arriver si le player est entre les murs de la map
		hitpoint.pt_co.x = -1;
	if (hitpoint.hit_face == FACE_E
		|| (rdata->first == FIRST_ANY && rdata->dial >= S_SW))
		hitpoint.chunk_co_x = (int)(hitpoint.pt_co.x - rdata->shift) - 1;
	else
		hitpoint.chunk_co_x = (int)(hitpoint.pt_co.x
				+ rdata->shift * (1 - 2 * (rdata->dial >= S_SW)));
	if (hitpoint.hit_face == FACE_N
		|| (rdata->first == FIRST_ANY && rdata->dial >= E_SE
			&& rdata->dial <= SW_W))
		hitpoint.chunk_co_y = (int)(hitpoint.pt_co.y - rdata->shift) - 1;
	else
		hitpoint.chunk_co_y = (int)(hitpoint.pt_co.y + rdata->shift
				* (1 - 2 * (rdata->dial >= E_SE && rdata->dial <= SW_W)));
	printf("--- INIT:---\n");//
		printf("H:\n check_H: %d\n first_h: (%.4f, %.4f) -> first_h - (int)player :\
	(%.4f, %.4f)\n delta_x: %.4f\n",
			rdata->check_h,
			rdata->last_h.x, rdata->last_h.y,
			rdata->last_h.x - floor(p_co->x), rdata->last_h.y - floor(p_co->y),
			rdata->delta_x);
		printf("V:\n check_V: %d\n first_v: (%.4f, %.4f) -> first_v - (int)player :\
	(%.4f, %.4f)\n delta_y: %.4f\n",
			rdata->check_v,
			rdata->last_v.x, rdata->last_v.y,
			rdata->last_v.x - floor(p_co->x), rdata->last_v.y - floor(p_co->y),
			rdata->delta_y);
		printf("==>\n -angle: %f\n -hit_pt: (%.3f, %.3f)\n -chunk: (%d, %d)\n---- End init\n", angle_ray, hitpoint.pt_co.x, hitpoint.pt_co.y, hitpoint.chunk_co_x, hitpoint.chunk_co_y);//
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
static void	_r_ray_init_h(t_coord_f *p_co, t_ray_data *rdata, float angle_ray)
{
	rdata->check_h = false;
	if ((angle_ray > M_PI / 2 - EPSILON && angle_ray < M_PI / 2 + EPSILON) || \
		(angle_ray > M_PI * 1.5 - EPSILON && angle_ray < M_PI * 1.5 + EPSILON))
		return ;
	rdata->check_h = true;
	if (rdata->dial >= W_NW || rdata->dial <= NE_E) // cadran sup
	{
		rdata->delta_x = tan(angle_ray);
		rdata->last_h.y = ceil(p_co->y + rdata->shift) - rdata->shift;
		if ((rdata->shift && p_co->y == rdata->last_h.y) //the player is on a grid line
			|| (!rdata->shift && p_co->y == floor(p_co->y)))
			rdata->last_h = *p_co;
		else
			rdata->last_h.x = p_co->x + rdata->delta_x
				* (rdata->last_h.y - p_co->y);
	}
	else
	{
		rdata->delta_x = -tan(angle_ray);
		rdata->last_h.y = floor(p_co->y - rdata->shift) + rdata->shift;
		rdata->last_h.x = p_co->x
			+ rdata->delta_x * (p_co->y - rdata->last_h.y);
	}
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
static void	_r_ray_init_v(t_coord_f *p_co, t_ray_data *rdata, float angle_ray)
{
	rdata->check_v = false;
	if (angle_ray > 2 * M_PI - EPSILON || angle_ray < EPSILON
		|| (angle_ray > M_PI - EPSILON && angle_ray < M_PI + EPSILON))
		return ;
	rdata->check_v = true;
	if (rdata->dial <= SE_S) // cadran droit
	{
		rdata->delta_y = 1. / tan(angle_ray);
		rdata->last_v.x = ceil(p_co->x + rdata->shift) - rdata->shift;
		if ((rdata->shift && p_co->x == rdata->last_v.x)
			|| (!rdata->shift && p_co->x == floor(p_co->x)))
			rdata->last_v = *p_co;
		else
			rdata->last_v.y = p_co->y
				+ (rdata->last_v.x - p_co->x) * rdata->delta_y;
	}
	else // gauche
	{
		rdata->delta_y = -1. / tan(angle_ray);
		rdata->last_v.x = floor(p_co->x - rdata->shift) + rdata->shift;
		rdata->last_v.y = p_co->y
			+ (p_co->x - rdata->last_v.x) * rdata->delta_y;
	}
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
	t_hitpoint *hitpt)
{
	t_1st_type	first_type;

	*hitpt = (t_hitpoint){0};
	first_type = _r_ray_init_get_first_type(pco, rdata);
	if (first_type == FIRST_H
		|| (first_type == FIRST_ANY && rdata->prim == PRIMARY_H))//hits an horizontal first
	{
		hitpt->pt_co = rdata->last_h;
		if (rdata->dial >= E_SE && rdata->dial <= SW_W)//looks down
			hitpt->hit_face = FACE_N;
		else
			hitpt->hit_face = FACE_S;
	}
	else
	{
		hitpt->pt_co = rdata->last_v;
		if (rdata->dial >= S_SW)
			hitpt->hit_face = FACE_E;
		else
			hitpt->hit_face = FACE_W;
	}
	return (first_type);
}

static t_1st_type	_r_ray_init_get_first_type(t_coord_f *pco,
	t_ray_data *rdata)
{
	if (!rdata->check_h)
	{
		if ((rdata->dial >= E_SE && rdata->dial <= SW_W
				&& floor(rdata->last_v.y) + rdata->shift == rdata->last_v.y)
			|| ((rdata->dial <= NE_E || rdata->dial >= W_NW)
				&& ceil(rdata->last_v.y) - rdata->shift == rdata->last_v.y))
			return (FIRST_ANY);
		return (FIRST_V);
	}
	if (!rdata->check_v)
	{
		if ((rdata->dial >= S_SW && floor(rdata->last_h.x) + rdata->shift
				== rdata->last_h.x) || (rdata->dial <= SE_S
				&& ceil(rdata->last_h.x) - rdata->shift == rdata->last_h.x))
			return (FIRST_ANY);
		return (FIRST_H);
	}
	if (rdata->last_h.x > rdata->last_v.x - EPSILON
		&& rdata->last_h.x < rdata->last_v.x + EPSILON)
		return (rdata->last_h.x = rdata->last_v.x,
			rdata->last_v.y = rdata->last_h.y, FIRST_ANY);
	if (pow(pco->x - rdata->last_v.x, 2.) + pow(pco->y - rdata->last_v.y, 2.)
		< pow(pco->x - rdata->last_h.x, 2.) + pow(pco->y - rdata->last_h.y, 2.))
		return (FIRST_V);
	return (FIRST_H);
}

/*
//==== tests _r_ray_init_h and _r_ray_init_v only ====
// https://www.geogebra.org/m/zw7kz29a

#include "../../includes/cub3d.h"

static void			_test_r_ray_full_one(t_general	*gen, t_coord_f *p_co,
						float angle_deg, t_ray_type ray_type);
static void			_test_r_ray_for_top_l_angle(t_general *gen,
						t_coord_f p_co_init, float alpha_top_right_deg,
						t_ray_type ray_type);
static void			_test_r_ray_for_top_r_angle(t_general *gen,
						t_coord_f p_co_init, float alpha_top_right_deg,
						t_ray_type ray_type);
static void			_test_r_ray_for_bot_l_angle(t_general *gen,
						t_coord_f p_co_init, float alpha_top_right_deg,
						t_ray_type ray_type);
static void			_test_r_ray_for_bot_r_angle(t_general *gen,
						t_coord_f p_co_init, float alpha_top_right_deg,
						t_ray_type ray_type);
static void			_test_r_ray_init_h(t_coord_f *p_co, t_ray_data *rdata,
						float angle_ray);
static void			_test_r_ray_init_v(t_coord_f *p_co, t_ray_data *rdata,
						float angle_ray);
static void			_test_r_ray_init_rdata_hitpoint(t_coord_f *p_co,
						float angle_ray, t_map *map, t_ray_data *rdata);

int	main(int ac, char **av)
{
	t_general	gen;
	float		angle_deg;
	t_coord_f	p_co_init;
	t_ray_type	ray_type = ray_raycasting;


	gen = (t_general){0};

	init_main(ac, av, &gen);
	printf("Player co init: (%f, %f)\n\n", gen.player.p_co.x,
		gen.player.p_co.y);
	p_co_init = gen.player.p_co;
	
	if (true) //tests different angles
	{
		printf("===========\nMultiple angles from position\n===========\n\n");
		// gen.player.p_co.x -= 0.5;
		// gen.player.p_co.y += 0.5;
		printf("Player_co : (%f, %f)\n\n", gen.player.p_co.x,
			gen.player.p_co.y);
		// printf("new player data:\n co: (%f, %f)\nangle: %f (%f deg)\n\n",
		// 	gen.player.p_co.x, gen.player.p_co.y, gen.player.p_angle,
		// 	gen.player.p_angle * 180 / M_PI);
		angle_deg = 0.;
		while (angle_deg < 360)
		{
			_test_r_ray_full_one(&gen, &gen.player.p_co, angle_deg,
				ray_type);
			angle_deg += 15.;
		}
	}
	if (false) //test top right angle
	{	
		printf("\n\n===========\nTop right angle\n===========\n\n");
		float	alpha_to_angle = 10;// [0,90]
		_test_r_ray_for_top_r_angle(&gen, p_co_init, alpha_to_angle,
			ray_type);
	}
	if (false) //test top left angle
	{
		printf("\n\n===========\nTop left angle\n===========\n\n");
		float	alpha_to_angle = 10;// [0,90]
		_test_r_ray_for_top_l_angle(&gen, p_co_init, alpha_to_angle,
			ray_type);
	}
	if (false) //test bottom left angle
	{
		printf("\n\n===========\nBottom left angle\n===========\n\n");
		float	alpha_to_angle = 10;// [0,90]
		_test_r_ray_for_bot_l_angle(&gen, p_co_init, alpha_to_angle,
			ray_type);
	}
	if (false) //test bottom right angle
	{
		printf("\n\n===========\nBottom right angle\n===========\n\n");
		float	alpha_to_angle = 10;// [0,90]
		_test_r_ray_for_bot_r_angle(&gen, p_co_init, alpha_to_angle,
			ray_type);
	}
	return (0);
}

//repositionning the player and recalculating the ray angle so that it crosses
// chunk angle
// /!\ the angles given n arguments must be between 0 and 90 deg

static void	_test_r_ray_for_top_r_angle(t_general *gen,
						t_coord_f p_co_init, float alpha_top_right_deg,
						t_ray_type ray_type)
{
	float	angle_deg;

	gen->player.p_co.x = p_co_init.x
		+ 0.5 - fabs(cos(alpha_top_right_deg * M_PI / 180));
	gen->player.p_co.y = p_co_init.y
		+ 0.5 - fabs(sin(alpha_top_right_deg * M_PI / 180));
	printf("Player_co : (%f, %f)\n", gen->player.p_co.x,
		gen->player.p_co.y);
	angle_deg = 90 - alpha_top_right_deg;
	_test_r_ray_full_one(gen, &gen->player.p_co, angle_deg, ray_type);
}

static void	_test_r_ray_for_top_l_angle(t_general *gen,
						t_coord_f p_co_init, float alpha_top_left_deg,
						t_ray_type ray_type)
{
	float	angle_deg;

	gen->player.p_co.x = p_co_init.x
		+ -0.5 + fabs(cos(alpha_top_left_deg * M_PI / 180));
	gen->player.p_co.y = p_co_init.y
		+ 0.5 - fabs(sin(alpha_top_left_deg * M_PI / 180));
	printf("Player_co : (%f, %f)\n", gen->player.p_co.x,
		gen->player.p_co.y);
	angle_deg = 360 - (90 - alpha_top_left_deg);
	_test_r_ray_full_one(gen, &gen->player.p_co, angle_deg, ray_type);
}

static void	_test_r_ray_for_bot_l_angle(t_general *gen,
						t_coord_f p_co_init, float alpha_bot_left_deg,
						t_ray_type ray_type)
{
	float	angle_deg;

	gen->player.p_co.x = p_co_init.x
		+ -0.5 + fabs(cos(alpha_bot_left_deg * M_PI / 180));
	gen->player.p_co.y = p_co_init.y
		+ -0.5 + fabs(sin(alpha_bot_left_deg * M_PI / 180));
	printf("Player_co : (%f, %f)\n", gen->player.p_co.x,
		gen->player.p_co.y);
	angle_deg = 180 + (90 - alpha_bot_left_deg);
	_test_r_ray_full_one(gen, &gen->player.p_co, angle_deg, ray_type);
}

static void	_test_r_ray_for_bot_r_angle(t_general *gen,
						t_coord_f p_co_init, float alpha_bot_right_deg,
						t_ray_type ray_type)
{
	float	angle_deg;

	gen->player.p_co.x = p_co_init.x
		+ 0.5 - fabs(cos(alpha_bot_right_deg * M_PI / 180));
	gen->player.p_co.y = p_co_init.y
		- 0.5 + fabs(sin(alpha_bot_right_deg * M_PI / 180));
	printf("Player_co : (%f, %f)\n", gen->player.p_co.x,
		gen->player.p_co.y);
	angle_deg = 180 - (90 - alpha_bot_right_deg);
	_test_r_ray_full_one(gen, &gen->player.p_co, angle_deg, ray_type);
}

static void	_r_ray_extract_param(t_ray_params *params, t_ray_data *rdata)
{
	rdata->time_now = params->ray_time;
	rdata->dial = (int)(params->ray_angle * 4. / M_PI);
	if (rdata->dial == N_NE || rdata->dial == SE_S
		|| rdata->dial == S_SW || rdata->dial == NW_N)
		rdata->prim = PRIMARY_H;
	else
		rdata->prim = PRIMARY_V;
	if (params->ray_type == ray_raycasting)
	{
		rdata->obstacles = CHARS_OBSTACLE_RAYCASTING;
		rdata->door_behaviour = ray_pass_door_no_touch;
	}
	else if (params->ray_type == ray_walk)
	{
		rdata->shift = DIST_WALL_MIN;
		rdata->obstacles = CHARS_OBSTACLE_WALK;
		rdata->door_behaviour = ray_pass_door_fully_open;
	}
	else //if params->ray_type == ray_action
		rdata->obstacles = CHARS_OBSTACLE_ACTION;
}

// end position related to grid intersection

static void	_test_r_ray_full_one(t_general	*gen, t_coord_f *p_co,
	float angle_deg, t_ray_type ray_type)
{
	t_ray_data		rdata;
	float			angle_rad;
	t_ray_params	params;

	angle_rad = angle_deg * M_PI / 180.;
	printf("\n-----------------------\nangle: %.2f (%.4f)\n\n",
		angle_deg, angle_rad);
	rdata = (t_ray_data){0};
	params = (t_ray_params){ray_type, to_getime(), *p_co, angle_deg};
	_r_ray_extract_param(&params, &rdata);
	printf("first h and first v detection :\n");
	_test_r_ray_init_h(p_co, &rdata, angle_rad);
	_test_r_ray_init_v(p_co, &rdata, angle_rad);
	printf("\nAfter selection:\n");
	_test_r_ray_init_rdata_hitpoint(p_co, angle_rad, &gen->map, &rdata);
}

static void	_test_r_ray_init_h(t_coord_f *p_co, t_ray_data *rdata,
				float angle_ray)
{
	_r_ray_init_h(p_co, rdata, angle_ray);
	printf("H:\n check_H: %d\n first_h: (%.4f, %.4f)\n  -> first_h - (int)player :\
 (%.4f, %.4f)\n delta_x: %.4f\n",
		rdata->check_h,
		rdata->last_h.x, rdata->last_h.y,
		rdata->last_h.x - floor(p_co->x), rdata->last_h.y - floor(p_co->y),
		rdata->delta_x);
}

static void	_test_r_ray_init_v(t_coord_f *p_co, t_ray_data *rdata,
				float angle_ray)
{
	_r_ray_init_v(p_co, rdata, angle_ray);
	printf("V:\n check_V: %d\n first_v: (%.4f, %.4f)\n  -> first_v - (int)player :\
 (%.4f, %.4f)\n delta_y: %.4f\n",
		rdata->check_v,
		rdata->last_v.x, rdata->last_v.y,
		rdata->last_v.x - floor(p_co->x), rdata->last_v.y - floor(p_co->y),
		rdata->delta_y);
}

static void	_test_r_ray_init_rdata_hitpoint(t_coord_f *p_co, float angle_ray,
	t_map *map, t_ray_data *rdata)
{
	t_hitpoint	first;

	first = r_ray_init_rdata_hitpoint(p_co, angle_ray, map, rdata);
// 	printf("H:\n check_H: %d\n first_h: (%.4f, %.4f) -> delta_h - player :\
//  (%.4f, %.4f)\n delta_x: %.4f\n", rdata->check_h, rdata->last_h.x,
// 		rdata->last_h.y, rdata->last_h.x - floor(p_co->x),
// 		rdata->last_h.y - floor(p_co->y), rdata->delta_x);
// 	printf("V:\n check_v: %d\n first_v: (%.4f, %.4f) -> delta_v - player :\
//  (%.4f, %.4f)\n delta_y: %.4f\n", rdata->check_v, rdata->last_v.x,
// 		rdata->last_v.y, rdata->last_v.x - floor(p_co->x),
// 		rdata->last_v.y - floor(p_co->y), rdata->delta_y);
	printf("First hitpoint:\n first: %c\n pt_co : (%.4f, %.4f) -> pt_co - \
player_co : (%.3f, %.3f)\n chunk_co: (%d, %d)\n  -> chunk_co - player_co :\
 (%d, %d)\n face: %c\n",
		"HVA"[rdata->first],
		first.pt_co.x, first.pt_co.y,
		first.pt_co.x - floor(p_co->x), first.pt_co.y - floor(p_co->y),
		first.chunk_co_x, first.chunk_co_y,
		first.chunk_co_x - (int)p_co->x, first.chunk_co_y - (int)p_co->y,
		"NESW"[first.hit_face]);
}

*/