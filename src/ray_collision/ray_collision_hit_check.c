/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_hit_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:09:42 by acardona          #+#    #+#             */
/*   Updated: 2023/10/31 01:15:27 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

static bool	_r_ray_check_no_shift_diag(t_map *map, t_dial dial,
				t_hitpoint *hit_pt, t_vector_f real_hitpt_co);

#ifdef BONUS

static const float	g_max_dec_to_wall = 1. - DIST_WALL_MIN;

static bool	_r_ray_check_shift_diag_touch_h(t_map *map, t_ray_data *rdata,
				t_hitpoint *hit_pt, t_coord_f real_hitpt_co);
static bool	_r_ray_check_shift_diag_touch_v(t_map *map, t_ray_data *rdata,
				t_hitpoint *hit_pt, t_coord_f real_hitpt_co);

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
	if (map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type == WALL
		|| map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type == NOTHING)
		return (true);
	if (rdata->prim == PRIMARY_H && _r_ray_check_shift_diag_touch_h(map, rdata,
			hit_pt, hit_pt->pt_co))
		return (true);
	if (rdata->prim != PRIMARY_H && _r_ray_check_shift_diag_touch_v(map, rdata,
			hit_pt, hit_pt->pt_co))
		return (true);
	if (map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type == DOOR)
	{//all this will go into chek door: the door need to be updated before these checks


//to do

	
		if (rdata->shift && map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y]
			.status != DOOR_OPEN)
			return (true);
		else if (rdata->shift)
			return (false);
		return (r_ray_hit_check_doors(map, hit_pt, rdata, hit_pt->pt_co));
	}
	return (false);
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
	if (map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type == WALL
		|| map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type == NOTHING)
		return (hit_pt->pt_co = real_hitpt_co, true);
	if (rdata->prim != PRIMARY_H && _r_ray_check_shift_diag_touch_h(map,
			rdata, hit_pt, real_hitpt_co))
		return (true);
	if (rdata->prim == PRIMARY_H && _r_ray_check_shift_diag_touch_v(map,
			rdata, hit_pt, real_hitpt_co))
		return (true);
	if (map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type == DOOR)
	{//all this will go into chek door: the door need to be updated before these checks
		if (rdata->shift && map->map[hit_pt->chunk_co_x][hit_pt->chunk_co_y]
			.status != DOOR_OPEN)
			return (hit_pt->pt_co = real_hitpt_co, true);
		else if (rdata->shift)
			return (false);
		return (r_ray_hit_check_doors(map, hit_pt, rdata, real_hitpt_co));
	}
	return (false);
}

/**
 * @brief used only when looking for collision with minimal distance to wall and
 *		the point hit an horizontal surface: 
 *		if the point is closed enough to the corner of a chunk it checks the
 *		closest diagonal chunk type to see if it's an obstacle and therefore if
 *		the hitpoint is truelly hitting a obstacle
 * 
 * @param map 
 * @param hit_pt 
 * @param dec 
 * @param touch_horiz 
 * @return true if an obstacle is hit
 * @return false if no obstacle hit
 */
static bool	_r_ray_check_shift_diag_touch_h(t_map *map, t_ray_data *rdata,
	t_hitpoint *hit_pt, t_coord_f real_hitpt_co)
{
	double	dec;

	dec = real_hitpt_co.x - floor(real_hitpt_co.x);
	// printf(" dec_h (%f, %f): %f\n", real_hitpt_co.x, real_hitpt_co.y, dec);//pb d'arrondi ici qd sur une verticale
	if (!rdata->shift)
		return ((dec == 0. && _r_ray_check_no_shift_diag(map, rdata->dial,
					hit_pt, real_hitpt_co)));
	if (dec == DIST_WALL_MIN || dec == g_max_dec_to_wall)
		return (_r_ray_check_no_shift_diag(map, rdata->dial, hit_pt, real_hitpt_co));
	if (dec < DIST_WALL_MIN)
	{
		if (r_ray_hit_check_solid_chunk(map->map,
				hit_pt->chunk_co_x - 1, hit_pt->chunk_co_y))
			return (--hit_pt->chunk_co_x, true);
		return (false);
	}
	else if (dec > g_max_dec_to_wall)
	{
		if (r_ray_hit_check_solid_chunk(map->map,
				hit_pt->chunk_co_x + 1, hit_pt->chunk_co_y))
			return (++hit_pt->chunk_co_x, true);
		return (false);//useless as there is the same line just after this line
	}
	return (false);
}

/**
 * @brief used only when looking for collision with minimal distance to wall and
 *		the point hit an vertical surface: 
 *		if the point is closed enough to the corner of a chunk it checks the
 *		closest diagonal chunk type to see if it's an obstacle and therefore if
 *		the hitpoint is truelly hitting a obstacle
 * 
 * @param map 
 * @param dial rdata.dial 
 * @param hit_pt contains the updated chunk_co but maybe not the right pt_co
 * @param real_hitpt_co real pt_co to use in calculous
 * @return true if an obstacle is hit
 * @return false if no obstacle hit
 */
static bool	_r_ray_check_shift_diag_touch_v(t_map *map, t_ray_data *rdata,
	t_hitpoint *hit_pt, t_coord_f real_hitpt_co)
{
	float	dec;

	dec = real_hitpt_co.y - floor(real_hitpt_co.y);
	if (!rdata->shift)
		return ((dec == 0. && _r_ray_check_no_shift_diag(map, rdata->dial,
					hit_pt, real_hitpt_co)));
	if (dec == DIST_WALL_MIN || dec == g_max_dec_to_wall)
		return (_r_ray_check_no_shift_diag(map, rdata->dial, hit_pt, real_hitpt_co));
	if (dec < DIST_WALL_MIN)
	{
		if (r_ray_hit_check_solid_chunk(map->map, hit_pt->chunk_co_x,
				hit_pt->chunk_co_y - 1))
			return (--hit_pt->chunk_co_y, true);
		return (false);
	}
	else if (dec > g_max_dec_to_wall)
	{
		if (r_ray_hit_check_solid_chunk(map->map, hit_pt->chunk_co_x,
				hit_pt->chunk_co_y + 1))
			return (++hit_pt->chunk_co_y, true);
		return (false);//useless as there is the same line just after this line
	}
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
	if ((rdata->prim == PRIMARY_H
			&& hit_pt->pt_co.x == floor(hit_pt->pt_co.x))
		|| (rdata->prim == PRIMARY_V
			&& hit_pt->pt_co.y == floor(hit_pt->pt_co.y)))
		return (_r_ray_check_no_shift_diag(map, rdata->dial, hit_pt,
				hit_pt->pt_co));
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

/**
 * @brief Used when a raycasting ray is sent (id rdata.shift == 0) and the ray
 *		hits the corner of a chunk. In this case checks the chunks adjacents to
 *		this point except the one from wich the ray comes from. In this case the
 *		impact is confirmed by a return true and the hitpoint coordinates are
*		updated to real_hitpoint_co
 * 
 * @param map 
 * @param hit_pt contains the updated hit hunk_co but not necessarly the right
 *		hitpoint coordinates
 * @param rdata 
 * @param real_hitpt_co the real hitpoint coordinates
 * @return true if an non tranparent object is hit on any of the three adjacent
 *		chunk, chunk_co updated
 * @return false otherwise
 */
/*
//version longue mais plus claire, ne permet pas de redefinir le chunk d'impacte
//si impacte
static bool	_r_ray_check_no_shift_diag(t_map *map, t_hitpoint *hit_pt,
	t_ray_data *rdata, t_vector_f real_hitpt_co)
{
	int	rtn;

	if (rdata->dial == SW_W || rdata->dial == S_SW) //arrive par cadran sup droit
		rtn = (r_ray_hit_check_solid_chunk(map->map, hit_pt->chunk_co_x,
					hit_pt->chunk_co_y + 1) || r_ray_hit_check_solid_chunk
				(map->map, hit_pt->chunk_co_x + 1, hit_pt->chunk_co_y));
	else if (rdata->dial == NW_N || rdata->dial == W_NW) //arrive par cadran inf droit
		rtn = (r_ray_hit_check_solid_chunk(map->map, hit_pt->chunk_co_x,
					hit_pt->chunk_co_y - 1) || r_ray_hit_check_solid_chunk
				(map->map, hit_pt->chunk_co_x + 1, hit_pt->chunk_co_y));
	else if (rdata->dial == N_NE || rdata->dial == NE_E) //arrive par cadran inf gauche
		rtn = (r_ray_hit_check_solid_chunk(map->map, hit_pt->chunk_co_x - 1,
					hit_pt->chunk_co_y) || r_ray_hit_check_solid_chunk
				(map->map, hit_pt->chunk_co_x, hit_pt->chunk_co_y - 1));
	else //arrive par cadran sup gauche
		rtn = (r_ray_hit_check_solid_chunk(map->map, hit_pt->chunk_co_x,
					hit_pt->chunk_co_y + 1) || r_ray_hit_check_solid_chunk
				(map->map, hit_pt->chunk_co_x - 1, hit_pt->chunk_co_y));
	if (rtn)
		return (hit_pt->pt_co = real_hitpt_co, true);
	return (false);
}
//verion courte qui change la nature du bloc touchee par celle du bloc rencontre
*/
static bool	_r_ray_check_no_shift_diag(t_map *map, t_dial dial,
	t_hitpoint *hit_pt, t_vector_f real_hitpt_co)
{
	if (dial >= S_SW)//cadrans gauche
	{
		if (r_ray_hit_check_solid_chunk(map->map, hit_pt->chunk_co_x + 1,
				hit_pt->chunk_co_y))
			return (++hit_pt->chunk_co_x, hit_pt->pt_co = real_hitpt_co, true);
	}
	else if (r_ray_hit_check_solid_chunk(map->map, hit_pt->chunk_co_x - 1,
		hit_pt->chunk_co_y))
		return (--hit_pt->chunk_co_x, hit_pt->pt_co = real_hitpt_co, true);
	if (dial >= E_SE && dial <= SW_W)//cadran inf
	{
		if (r_ray_hit_check_solid_chunk(map->map, hit_pt->chunk_co_x,
				hit_pt->chunk_co_y + 1))
			return (++hit_pt->chunk_co_y, hit_pt->pt_co = real_hitpt_co, true);
	}
	else if (r_ray_hit_check_solid_chunk(map->map, hit_pt->chunk_co_x,
			hit_pt->chunk_co_y - 1))
		return (--hit_pt->chunk_co_y, hit_pt->pt_co = real_hitpt_co, true);
	return (false);
}
