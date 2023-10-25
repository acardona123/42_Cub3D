/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_hit_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:09:42 by acardona          #+#    #+#             */
/*   Updated: 2023/10/24 20:04:31 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

#ifdef BONUS

static const float	g_max_dec_to_wall = 1. - DIST_WALL_MIN;

static bool	r_ray_check_basic_shift_diagonal_neighbors(t_map *map,
				t_hitpoint *hit_pt, float dec, bool touch_horiz);

/**
 * @brief if rdata.shift == 0.
 *			->then checks if the hitpoint of the ray touchs an obstacle (not
 *			floor or nothing), if so returns true and update the hitpoint if
 *			needed (ie if it hit a door)
 *		else
 *			->then checks if hitpoint as a player position is "touching" a
 *			solid obstaclem ie is as close as DIST_WALL_MIN from it.
 * 
 * @param map 
 * @param hit_pt hitpoint detected that need to be checked
 * @param rdata 
 * @return true if the ray hit an obstacle, hit_pt updated if hit a door.
 * @return false if no obstacle
 */
bool	r_ray_hit_primary(t_map *map, t_hitpoint *hit_pt, t_ray_data *rdata)
{
	if (hit_pt->pt_co.x <= -EPSILON)
		return (true);
	if (map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type == WALL)
		return (true);
	else if (map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type == DOOR)
	{
		if (rdata->shift && map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y]
			.status != DOOR_OPEN)
			return (true);
		else if (rdata->shift)
			return (false);
		return (r_ray_hit_check_doors(map, hit_pt, rdata, hit_pt->pt_co));
	}
	if (!rdata->shift)
		return (false);
	if (rdata->prim == PRIMARY_H)
		return (r_ray_check_basic_shift_diagonal_neighbors(map, hit_pt,
				hit_pt->pt_co.x - floor(hit_pt->pt_co.x), true));
	return (r_ray_check_basic_shift_diagonal_neighbors(map, hit_pt,
			hit_pt->pt_co.y - floor(hit_pt->pt_co.y), false));
}

/**
 * @brief same as r_ray_hit_primary but the hitpoint coordinates that
 *		are taken into account are not stored in hit_pt but in real_hitpt_co.
 *		Used to check the obstacles on the secondary axis
 *
 * @param map 
 * @param hit_pt hitpoint detected that need to be checked
 * @param rdata 
 * @param real_hitpt_co
 * @return true if the ray hit an obstacle, hit_pt updated (coord becomes
 *	real_hitpt_co) and are modified if hit a door
 * @return false if no obstacle, hit_pt unchanged
 */
bool	r_ray_hit_sec(t_map *map, t_hitpoint *hit_pt,
	t_ray_data *rdata, t_vector_f real_hitpt_co)
{
	if (real_hitpt_co.x <= -EPSILON)
		return (hit_pt->pt_co.x = -1., true);
	if (map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type == WALL)
		return (hit_pt->pt_co = real_hitpt_co, true);
	else if (map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type == DOOR)
	{
		if (rdata->shift && map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y]
			.status != DOOR_OPEN)
			return (hit_pt->pt_co = real_hitpt_co, true);
		else if (rdata->shift)
			return (false);
		return (r_ray_hit_check_doors(map, hit_pt, rdata, real_hitpt_co));
	}
	if (!rdata->shift)
		return (false);
	if (rdata->prim != PRIMARY_H //on a touché l'axe secondaire en premier ie axe V ici
		&& r_ray_check_basic_shift_diagonal_neighbors(map, hit_pt,
			real_hitpt_co.x - floor(real_hitpt_co.x), true))
		return (hit_pt->pt_co = real_hitpt_co, true);
	if (rdata->prim == PRIMARY_H
		&& r_ray_check_basic_shift_diagonal_neighbors(map, hit_pt,
			real_hitpt_co.y - floor(real_hitpt_co.y), false))
		return (hit_pt->pt_co = real_hitpt_co, true);
	return (false);
}

/**
 * @brief used only when looking for collision with minimal distance to wall: if
 *		the point is closed enough to the corner of a chunk it checks the
 *		closest diagonal chunk type to see if it's an obstacle and therefore if
 *		the hitpoint is truly hitting a obstacle
 * 
 * @param map 
 * @param hit_pt 
 * @param dec 
 * @param touch_horiz 
 * @return true if an obstacle is hit
 * @return false if no obstacle hit
 */
static bool	r_ray_check_basic_shift_diagonal_neighbors(t_map *map,
	t_hitpoint *hit_pt, float dec, bool touch_horiz)
{
	if (touch_horiz)
	{
		if (dec <= DIST_WALL_MIN)
			return (r_ray_hit_check_solid_chunk(map->map,
					hit_pt->chunk_co_x - 1, hit_pt->chunk_co_y));
		else if (dec >= g_max_dec_to_wall)
			return (r_ray_hit_check_solid_chunk(map->map,
					hit_pt->chunk_co_x + 1, hit_pt->chunk_co_y));
		return (false);
	}
	dec = hit_pt->pt_co.y - floor(hit_pt->pt_co.y);
	if (dec <= DIST_WALL_MIN)
		return (r_ray_hit_check_solid_chunk(map->map, hit_pt->chunk_co_x,
				hit_pt->chunk_co_y - 1));
	else if (dec >= g_max_dec_to_wall)
		return (r_ray_hit_check_solid_chunk(map->map, hit_pt->chunk_co_x,
				hit_pt->chunk_co_y + 1));
	return (false);
}

#else

/**
 * @brief only used for raycasting:
 *		used on primary axis hitpoint: if the hitpoint touch an obstacle
 *		(not floor or nothing), returns true and update the hitpoint if
 *		needed (ie if it hit a door)
 * 
 * @param map 
 * @param hit_pt hitpoint detected that need to be checked
 * @param rdata 
 * @return true if the ray hit an obstacle, hit_pt updated if hit a door.
 * @return false if no obstacle
 */
bool	r_ray_hit_primary(t_map *map, t_hitpoint *hit_pt, t_ray_data *rdata)
{
	(void)rdata;
	if (hit_pt->pt_co.x <= -EPSILON)
		return (true);
	if (map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type == WALL)
		return (true);
	return (false);
}

/**
 * @brief checks if real_hitpt_co touchs an obstacle (calculous base on
 *		hitpoint->chunk_co), if so hit_pt->pt_co is set to real_hitpt_co
 *
 * @param map 
 * @param hit_pt hitpoint detected that need to be checked
 * @param rdata 
 * @param real_hitpt_co
 * @return true if the ray hit an obstacle, hit_pt updated (coord becomes
 *	real_hitpt_co)
 * @return false if no obstacle, hit_pt unchanged
 */
bool	r_ray_hit_sec(t_map *map, t_hitpoint *hit_pt,
	t_ray_data *rdata, t_vector_f real_hitpt_co)
{
	(void)rdata;
	if (real_hitpt_co.x <= -EPSILON)
		return (hit_pt->pt_co.x = -1., true);
	if (map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type == WALL)
		return (hit_pt->pt_co = real_hitpt_co, true);
	return (false);
}

#endif
