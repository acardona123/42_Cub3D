/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_hit_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:09:42 by acardona          #+#    #+#             */
/*   Updated: 2023/10/21 20:27:48 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

/**
 * @brief if the hitpoint touch an obstacle (not floor or nothing), if so return
 *		true and update the hitpoint if needed (ie if it hit a door)
 * 
 * @param map 
 * @param hit_pt hitpoint detected that need to be checked
 * @param rdata 
 * @return true if the ray hit an obstacle, hit_pt updated if hit a door
 * @return false if no obstacle
 */
bool	r_ray_hit_check_basic(t_map *map, t_hitpoint *hit_pt,
	t_ray_data *rdata)
{
	if (hit_pt->pt_co.x <= -EPSILON)
		return (true);
	if (ft_isinset(map->map[hit_pt->chunk_co.x][hit_pt->chunk_co.y].type,
		CHARS_TRANSPARENT))
		return (false);
	if (map->map[hit_pt->chunk_co.x][hit_pt->chunk_co.y].type == WALL)
		return (true);
	else if (map->map[hit_pt->chunk_co.x][hit_pt->chunk_co.y].type == DOOR)
		return (r_ray_hit_check_doors(map, hit_pt, rdata, hit_pt->pt_co));
	return (true);
}

/**
 * @brief same as r_ray_hit_check_basic but the hitpoint coordinates that
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
bool	r_ray_hit_check_extra_co(t_map *map, t_hitpoint *hit_pt,
	t_ray_data *rdata, t_vector_f real_hitpt_co)
{
	if (real_hitpt_co.x <= -EPSILON)
		return (hit_pt->pt_co.x = -1., true);
	if (ft_isinset(map->map[hit_pt->chunk_co.x][hit_pt->chunk_co.y].type,
		CHARS_TRANSPARENT))
		return (false);
	if (map->map[hit_pt->chunk_co.x][hit_pt->chunk_co.y].type == WALL)
		return (hit_pt->pt_co = real_hitpt_co, true);
	else if (map->map[hit_pt->chunk_co.x][hit_pt->chunk_co.y].type == DOOR)
		return (r_ray_hit_check_doors(map, hit_pt, rdata, hit_pt->pt_co));
	return (true);
}
