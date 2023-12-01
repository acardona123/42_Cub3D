/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:14:53 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 15:39:36 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

static const t_collision_function	g_collision_function[8]
	= {r_ray_hit_n_ne, r_ray_hit_ne_e, r_ray_hit_e_se, r_ray_hit_se_s,
	r_ray_hit_s_sw, r_ray_hit_sw_w, r_ray_hit_w_nw, r_ray_hit_nw_n};

static void	_r_ray_extract_param(t_ray_params *params, t_ray_data *rdata);

/**
 * @brief sendsd a ray from the player, in a certain direction and returns the
 *	impact point with the first obstacle found.
 *	(if no obstacle found the abscisse of the returned obstacle is set to -1.)
 * 
 * @param gen 
 * @param params structure contining the characterstics of the ray
 * @return t_hitpoint structure contining the datas oh the first bloc hitten and
 *		the imact point.
 */
t_hitpoint	r_ray_hit(t_general *gen, t_ray_params params)
{
	t_hitpoint	last_hit;
	t_ray_data	rdata;

	while (params.ray_angle < 0)
		params.ray_angle += 2 * M_PI;
	while (params.ray_angle > 2 * M_PI)
		params.ray_angle -= 2 * M_PI;
	rdata = (t_ray_data){0};
	_r_ray_extract_param(&params, &rdata);
	last_hit = r_ray_init_rdata_hitpoint(&params.ray_start_point,
			params.ray_angle, &gen->map, &rdata);
	return (g_collision_function[rdata.dial](gen, last_hit, rdata));
}

#ifdef BONUS

/**
 * @brief extract parameters from params to fill rdata elements
 * 
 * @param params 
 * @param rdata 
 */
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
	else
		rdata->obstacles = CHARS_OBSTACLE_ACTION;
}

#else

/**
 * @brief extract parameters from params to fill rdata elements
 * 
 * @param params 
 * @param rdata 
 */
static void	_r_ray_extract_param(t_ray_params *params, t_ray_data *rdata)
{
	rdata->time_now = params->ray_time;
	rdata->dial = (int)(params->ray_angle * 4. / M_PI);
	if (rdata->dial == N_NE || rdata->dial == SE_S
		|| rdata->dial == S_SW || rdata->dial == NW_N)
		rdata->prim = PRIMARY_H;
	else
		rdata->prim = PRIMARY_V;
	rdata->obstacles = CHARS_OBSTACLE_RAYCASTING;
}

#endif

/*
#include "../../includes/cub3d.h"
int	main(int ac, char **av)
{
	t_general	gen;
	t_hitpoint	hitpoint;
	float		angle_deg;
	t_ray_type	ray_type = ray_walk;

	gen = (t_general){0};
	init_main(ac, av, &gen);
	gen.player.p_co.x = 10.250001;
	gen.player.p_co.y = 1.250001;
	// gen.player.p_co.x -= 0.5 + DIST_WALL_MIN;
	// gen.player.p_co.y += 0.5 - DIST_WALL_MIN;
	// gen.player.p_co.x -= .4;
	// gen.player.p_co.y += .5;
	printf("player co: (%f, %f)\n\n", gen.player.p_co.x, gen.player.p_co.y);
	angle_deg = 0.;
	while (angle_deg < 360)
	{
		printf("angle: %f (%f)\n", angle_deg, angle_deg * M_PI / 180);
		fflush(stdout);
		hitpoint = r_ray_hit(&gen, (t_ray_params){ray_type, to_getime(),
				gen.player.p_co, angle_deg * M_PI / 180});
		printf(" last_hit : (%f, %f)\n", hitpoint.pt_co.x, hitpoint.pt_co.y);
		fflush(stdout);
		if (hitpoint.chunk_co_x >= 0.)
			printf(" chunk: (%d, %d) -> \'%c\'\n", hitpoint.chunk_co_x,
				hitpoint.chunk_co_y,
				gen.map.map[hitpoint.chunk_co_x][hitpoint.chunk_co_y].type);
		else
			printf("chunk: no\n");
		printf(" face: %c\n\n", "NESW"[hitpoint.hit_face]);
		fflush(stdout);
		angle_deg += 15.;
	}
	return (0);
}
*/