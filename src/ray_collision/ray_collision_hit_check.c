/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_hit_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:09:42 by acardona          #+#    #+#             */
/*   Updated: 2023/11/29 19:49:03 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

static bool	_r_ray_check_no_shift_diag(t_general *gen, t_ray_data *rdata,
				t_hitpoint *hit_pt, t_vector_f real_hitpt_co);

#ifdef BONUS

static bool	_r_ray_check_shift_diag_touch_h(t_general *gen, t_ray_data *rdata,
				t_hitpoint *hit_pt, t_coord_f real_hitpt_co);
static bool	_r_ray_check_shift_diag_touch_v(t_general *gen, t_ray_data *rdata,
				t_hitpoint *hit_pt, t_coord_f real_hitpt_co);
static bool	_r_ray_check_shift_diag(t_general *gen, t_ray_data *rdata,
				t_hitpoint *hit_pt, t_vector_f real_hitpt_co);
static bool	_r_ray_check_shift_diag_sub(t_chunk **map, t_ray_data *rdata,
				t_coord_f dec, t_coord_i *chunk);

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
	if (rdata->prim == PRIMARY_H && _r_ray_check_shift_diag_touch_h(gen, rdata,
			hit_pt, hit_pt->pt_co))
		return (true);
	if (rdata->prim != PRIMARY_H && _r_ray_check_shift_diag_touch_v(gen, rdata,
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
	if (rdata->prim != PRIMARY_H && _r_ray_check_shift_diag_touch_h(gen,
			rdata, hit_pt, real_hitpt_co))
		return (true);
	if (rdata->prim == PRIMARY_H && _r_ray_check_shift_diag_touch_v(gen,
			rdata, hit_pt, real_hitpt_co))
		return (true);
	return (false);
}

/**
 * @brief used only when looking for collision with a potentially non null
 *		minimal distance to wall and the point hit an horizontal surface: 
 *		if the point is closed enough to the corner of a chunk it checks the
 *		closest diagonal chunk type to see if it's an obstacle and therefore if
 *		the hitpoint is truelly hitting a obstacle
 * 
 * @param gen 
 * @param rdata 
 * @param hit_pt 
 * @param real_hitpt_co 
 * @return true if an obstacle is hit
 * @return false if no obstacle hit
 */
static bool	_r_ray_check_shift_diag_touch_h(t_general *gen, t_ray_data *rdata,
	t_hitpoint *hit_pt, t_coord_f real_hitpt_co)
{
	double	dec;

	dec = real_hitpt_co.x - floor(real_hitpt_co.x);
	if (!rdata->shift)
		return ((dec == 0. && _r_ray_check_no_shift_diag(gen, rdata,
					hit_pt, real_hitpt_co)));
	if (dec <= rdata->shift || dec >= 1.f - rdata->shift)
		return (_r_ray_check_shift_diag(gen, rdata, hit_pt, real_hitpt_co));
	return (false);
}

/**
 * @brief used only when looking for collision with minimal distance to wall and
 *		the point hit an vertical surface: 
 *		if the point is closed enough to the corner of a chunk it checks the
 *		closest diagonal chunk type to see if it's an obstacle and therefore if
 *		the hitpoint is truelly hitting a obstacle
 * 
 * @param gen 
 * @param rdata
 * @param hit_pt contains the updated chunk_co but maybe not the right pt_co
 * @param real_hitpt_co real pt_co to use in calculous
 * @return true if an obstacle is hit
 * @return false if no obstacle hit
 */
static bool	_r_ray_check_shift_diag_touch_v(t_general *gen, t_ray_data *rdata,
	t_hitpoint *hit_pt, t_coord_f real_hitpt_co)
{
	double	dec;

	dec = real_hitpt_co.y - floor(real_hitpt_co.y);
	if (!rdata->shift)
		return ((dec == 0. && _r_ray_check_no_shift_diag(gen, rdata,
					hit_pt, real_hitpt_co)));
	if (dec <= rdata->shift || dec >= 1.f - rdata->shift)
		return (_r_ray_check_shift_diag(gen, rdata, hit_pt, real_hitpt_co));
	return (false);
}


/**
 * @brief 
 * 
 * @param gen 
 * @param rdata 
 * @param hit_pt 
 * @param real_hitpt_co 
 * @return true 
 * @return false 
 */
static bool	_r_ray_check_shift_diag(t_general *gen, t_ray_data *rdata,
	t_hitpoint *hit_pt, t_vector_f real_hitpt_co)
{
	t_coord_f	dec;
	t_coord_i	chunk;

	dec.x = real_hitpt_co.x - floor(real_hitpt_co.x);
	dec.y = real_hitpt_co.y - floor(real_hitpt_co.y);
	chunk = (t_coord_i){(int)real_hitpt_co.x, (int)real_hitpt_co.y};
	if ((dec.x <= rdata->shift || dec.x >= 1.f - rdata->shift)
		&& _r_ray_check_shift_diag_sub(gen->map.map, rdata, dec, &chunk))
		return (hit_pt->chunk_co_x = chunk.x, hit_pt->chunk_co_y = chunk.y,
			hit_pt->pt_co = real_hitpt_co, true);
	if (dec.y <= rdata->shift && r_ray_hit_is_solid_chunk(gen->map.map, rdata,
			chunk.x, chunk.y - 1))
		return (hit_pt->chunk_co_x = chunk.x, hit_pt->chunk_co_y = chunk.y - 1,
			hit_pt->pt_co = real_hitpt_co, true);
	if (dec.y >= 1.f - rdata->shift
		&& r_ray_hit_is_solid_chunk(gen->map.map, rdata, chunk.x, chunk.y + 1))
		return (hit_pt->chunk_co_x = chunk.x, hit_pt->chunk_co_y = chunk.y + 1,
			hit_pt->pt_co = real_hitpt_co, true);
	return (false);
}

static bool	_r_ray_check_shift_diag_sub(t_chunk **map, t_ray_data *rdata,
	t_coord_f dec, t_coord_i *chunk)
{
	chunk->x += 1 - 2 * (dec.x <= rdata->shift);
	if (r_ray_hit_is_solid_chunk(map, rdata, chunk->x, chunk->y))
		return (true);
	if (dec.y <= rdata->shift && r_ray_hit_is_solid_chunk(
			map, rdata, chunk->x, chunk->y - 1))
	{
		--chunk->y;
		return (true);
	}
	if (dec.y >= 1.f - rdata->shift && r_ray_hit_is_solid_chunk(
			map, rdata, chunk->x, chunk->y + 1))
	{
		++chunk->y;
		return (true);
	}
	chunk->x -= 1 - 2 * (dec.x <= rdata->shift);
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
		return (_r_ray_check_no_shift_diag(gen, rdata, hit_pt,
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
		return (_r_ray_check_no_shift_diag(gen, rdata, hit_pt,
				real_hitpt_co));
	return (false);
}

#endif

/**
 * @brief Used when a raycasting ray is sent (id rdata.shift == 0) and the ray
 *		hits the corner of a chunk. In this case checks the chunks adjacents to
 *		this point. In this case the impact is confirmed by a return true and
 *		the hitpoint coordinates are updated to real_hitpoint_co
 * 
 * @param gen 
 * @param rdata 
 * @param hit_pt contains the updated hit hunk_co but not necessarly the right
 *		hitpoint coordinates
 * @param real_hitpt_co the real hitpoint coordinates
 * @return true if a non tranparent object is hit on any of the adjacent chunks,
 *			chunk_co updated
 * @return false otherwise
 */
static bool	_r_ray_check_no_shift_diag(t_general *gen, t_ray_data *rdata,
	t_hitpoint *hit_pt, t_vector_f real_hitpt_co)
{
	int		chunk_x;
	int		chunk_y;
	bool	rtn;

	chunk_x = (int)real_hitpt_co.x;
	chunk_y = (int)real_hitpt_co.y;
	rtn = true;
	if (r_ray_hit_is_solid_chunk(gen->map.map, rdata, chunk_x - 1, chunk_y))
		--chunk_x;
	else if (r_ray_hit_is_solid_chunk(gen->map.map, rdata, chunk_x - 1,
			chunk_y - 1))
	{
		--chunk_x;
		--chunk_y;
	}
	else if (r_ray_hit_is_solid_chunk(gen->map.map, rdata, chunk_x,
			chunk_y - 1))
		--chunk_y;
	else if (!r_ray_hit_is_solid_chunk(gen->map.map, rdata, chunk_x, chunk_y))
		return (false);
	return (hit_pt->chunk_co_x = chunk_x, hit_pt->chunk_co_y = chunk_y,
		hit_pt->pt_co = real_hitpt_co, true);
}
