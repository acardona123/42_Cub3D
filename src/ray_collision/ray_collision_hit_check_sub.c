/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_hit_check_sub.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:09:42 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 20:10:07 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

/**
 * @brief Used when a raycasting ray is sent (id rdata.shift == 0) and the ray
 *		hits the corner of a chunk. In this case checks the chunks adjacents to
 *		this point. If one of htem is an obstacle, the impact is confirmed by
 *		returning true and the hitpoint coordinates are updated to
 *		real_hitpoint_co
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
bool	r_ray_check_no_shift_diag(t_general *gen, t_ray_data *rdata,
	t_hitpoint *hit_pt, t_vector_f real_hitpt_co)
{
	int		chunk_x;
	int		chunk_y;

	chunk_x = (int)real_hitpt_co.x;
	chunk_y = (int)real_hitpt_co.y;
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

#ifdef BONUS

static bool	r_ray_check_shift_diag_sub(t_chunk **map, t_ray_data *rdata,
			t_coord_f dec, t_coord_i *chunk);

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
bool	r_ray_check_shift_diag_touch_h(t_general *gen, t_ray_data *rdata,
	t_hitpoint *hit_pt, t_coord_f real_hitpt_co)
{
	double	dec;

	dec = real_hitpt_co.x - floor(real_hitpt_co.x);
	if (!rdata->shift)
		return ((dec == 0. && r_ray_check_no_shift_diag(gen, rdata,
					hit_pt, real_hitpt_co)));
	if (dec <= rdata->shift || dec >= 1.f - rdata->shift)
		return (r_ray_check_shift_diag(gen, rdata, hit_pt, real_hitpt_co));
	return (false);
}

/**
 * @brief used only when looking for collision with minimal distance to wall and
 *		the point hits a vertical surface: 
 *		if the point is closed enough to the corner of a chunk it checks the
 *		closest diagonal chunk type to see if it's an obstacle and therefore if
 *		the hitpoint is hitting a obstacle
 * 
 * @param gen 
 * @param rdata
 * @param hit_pt contains the updated chunk_co but maybe not the right pt_co
 * @param real_hitpt_co real pt_co to use in calculous
 * @return true if an obstacle is hit
 * @return false if no obstacle hit
 */
bool	r_ray_check_shift_diag_touch_v(t_general *gen, t_ray_data *rdata,
	t_hitpoint *hit_pt, t_coord_f real_hitpt_co)
{
	double	dec;

	dec = real_hitpt_co.y - floor(real_hitpt_co.y);
	if (!rdata->shift)
		return ((dec == 0. && r_ray_check_no_shift_diag(gen, rdata,
					hit_pt, real_hitpt_co)));
	if (dec <= rdata->shift || dec >= 1.f - rdata->shift)
		return (r_ray_check_shift_diag(gen, rdata, hit_pt, real_hitpt_co));
	return (false);
}

/**
 * @brief checks if the ray hitpoint is closer to a neighbor chunk that the
 *		given shift (ex: DIST_WALL_MIN for ray_walk), if so checks if those
 *		neighbors generate a colision
 * 
 * @param gen 
 * @param rdata 
 * @param hit_pt 
 * @param real_hitpt_co 
 * @return true if collision detected, hitpoint->pt_co updated
 * @return false if no collision with the neighbors
 */
bool	r_ray_check_shift_diag(t_general *gen, t_ray_data *rdata,
	t_hitpoint *hit_pt, t_vector_f real_hitpt_co)
{
	t_coord_f	dec;
	t_coord_i	chunk;

	dec.x = real_hitpt_co.x - floor(real_hitpt_co.x);
	dec.y = real_hitpt_co.y - floor(real_hitpt_co.y);
	chunk = (t_coord_i){(int)real_hitpt_co.x, (int)real_hitpt_co.y};
	if ((dec.x <= rdata->shift || dec.x >= 1.f - rdata->shift)
		&& r_ray_check_shift_diag_sub(gen->map.map, rdata, dec, &chunk))
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

/**
 * @brief subfunction of r_ray_check_shift_diag
 * 
 * @param map 
 * @param rdata 
 * @param dec 
 * @param chunk 
 * @return true neighbor chunk hit
 * @return false 
 */
static bool	r_ray_check_shift_diag_sub(t_chunk **map, t_ray_data *rdata,
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

#endif
