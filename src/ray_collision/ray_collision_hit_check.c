/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_hit_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:09:42 by acardona          #+#    #+#             */
/*   Updated: 2023/11/30 16:43:53 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

#ifdef BONUS

/**
 * @brief Used to check the obstacles on the primary axis
 *		if rdata.shift == 0.
 *			->then checks if the hitpoint of the ray touchs an obstacle (not
 *			floor or nothing), if so returns true and update the hitpoint if
 *			needed (ie if it hit a door)
 *		else
 *			->then checks if hitpoint as a player position is "touching" a
 *			solid obstaclem ie is as close as DIST_WALL_MIN from it.
 * 
 * @param gen 
 * @param hit_pt hitpoint detected that need to be checked
 * @param rdata 
 * @return true if the ray hit an obstacle, hit_pt updated if hit a door.
 * @return false if no obstacle
 */
bool	r_ray_hit_primary(t_general *gen, t_hitpoint *hit_pt, t_ray_data *rdata)
{
	if (hit_pt->pt_co.x <= -EPSILON)
		return (true);
	if (ft_isinset(gen->map.map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type,
		rdata->obstacles))
		return (true);
	if (rdata->door_behaviour != ray_pass_door_always
		&& gen->map.map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type == DOOR)
		return (r_ray_hit_check_doors_prim(gen, rdata, hit_pt, hit_pt->pt_co));
	if (rdata->prim == PRIMARY_H && r_ray_check_shift_diag_touch_h(gen, rdata,
			hit_pt, hit_pt->pt_co))
		return (true);
	if (rdata->prim != PRIMARY_H && r_ray_check_shift_diag_touch_v(gen, rdata,
			hit_pt, hit_pt->pt_co))
		return (true);
	return (false);
}

/**
 * @brief same as r_ray_hit_primary but the hitpoint coordinates that
 *		are taken into account are not stored in hit_pt but in real_hitpt_co.
 *		Used to check the obstacles on the secondary axis
 *
 * @param gen 
 * @param hit_pt hitpoint detected that need to be checked
 * @param rdata 
 * @param real_hitpt_co
 * @return true if the ray hit an obstacle, hit_pt updated (coord becomes
 *	real_hitpt_co) and are modified if hit a door
 * @return false if no obstacle, hit_pt unchanged
 */
bool	r_ray_hit_sec(t_general *gen, t_hitpoint *hit_pt,
	t_ray_data *rdata, t_vector_f real_hitpt_co)
{
	if (real_hitpt_co.x <= -EPSILON)
		return (hit_pt->pt_co.x = -1., true);
	if (ft_isinset(gen->map.map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type,
		rdata->obstacles))
		return (hit_pt->pt_co = real_hitpt_co, true);
	if (rdata->door_behaviour != ray_pass_door_always
		&& gen->map.map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type == DOOR)
		return (r_ray_hit_check_doors_sec(gen, rdata, hit_pt, real_hitpt_co));
	if (rdata->prim != PRIMARY_H && r_ray_check_shift_diag_touch_h(gen,
			rdata, hit_pt, real_hitpt_co))
		return (true);
	if (rdata->prim == PRIMARY_H && r_ray_check_shift_diag_touch_v(gen,
			rdata, hit_pt, real_hitpt_co))
		return (true);
	return (false);
}

#else

/**
 * @brief only used for raycasting:
 *		used on primary axis hitpoint: if the hitpoint touch an obstacle
 *		(not floor or nothing), returns true and update the hitpoint if
 *		needed (ie if it hit a door)
 * 
 * @param gen 
 * @param hit_pt hitpoint detected that need to be checked
 * @param rdata 
 * @return true if the ray hit an obstacle, hit_pt updated if hit a door.
 * @return false if no obstacle
 */
bool	r_ray_hit_primary(t_general *gen, t_hitpoint *hit_pt, t_ray_data *rdata)
{
	if (hit_pt->pt_co.x <= -EPSILON)
		return (true);
	if (ft_isinset(gen->map.map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type,
		rdata->obstacles))
		return (true);
	if ((rdata->prim == PRIMARY_H
			&& hit_pt->pt_co.x - floor(hit_pt->pt_co.x) == 0)
		|| (rdata->prim != PRIMARY_H
			&& hit_pt->pt_co.y - floor(hit_pt->pt_co.y) == 0))
		return (r_ray_check_no_shift_diag(gen, rdata, hit_pt,
				hit_pt->pt_co));
	return (false);
}

/**
 * @brief checks if real_hitpt_co touchs an obstacle (calculous base on
 *		hitpoint->chunk_co), if so hit_pt->pt_co is set to real_hitpt_co
 *
 * @param gen 
 * @param hit_pt hitpoint detected that need to be checked
 * @param rdata 
 * @param real_hitpt_co
 * @return true if the ray hit an obstacle, hit_pt updated (coord becomes
 *	real_hitpt_co)
 * @return false if no obstacle, hit_pt unchanged
 */
bool	r_ray_hit_sec(t_general *gen, t_hitpoint *hit_pt,
	t_ray_data *rdata, t_vector_f real_hitpt_co)
{
	if (real_hitpt_co.x <= -EPSILON)
		return (hit_pt->pt_co.x = -1., true);
	if (ft_isinset(gen->map.map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type,
		rdata->obstacles))
		return (hit_pt->pt_co = real_hitpt_co, true);
	if ((rdata->prim != PRIMARY_H
			&& real_hitpt_co.x - floor(real_hitpt_co.x) == 0.)
		|| (rdata->prim == PRIMARY_H
			&& real_hitpt_co.y - floor(real_hitpt_co.y) == 0.))
		return (r_ray_check_no_shift_diag(gen, rdata, hit_pt,
				real_hitpt_co));
	return (false);
}

#endif
