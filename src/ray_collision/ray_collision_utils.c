/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:11:15 by acardona          #+#    #+#             */
/*   Updated: 2023/11/07 15:25:20 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

/**
 * @brief checks if a point (x, y) is outside the map (ie insides the exterior
 * walls of the map)
 * 
 * @param map 
 * @param x 
 * @param y 
 * @return true if outside the map
 * @return false if inside the map
 */
bool	r_point_outside_map(t_map *map, t_coord_f P)
{
	return (P.x < 1. || P.y < 1. || P.x > map->x_max - 1. || P.y > map->y_max);
}

/**
 * @brief tests if the given chunk is solid ie the player can't go in it
 * 
 * @param map 
 * @param chunk_co_x 
 * @param chunk_co_y 
 * @return true if solid
 * @return false if not solid (reachable for the player)
 */
bool	r_ray_hit_check_solid_chunk(t_chunk **map, t_ray_data *rdata,
	int chunk_co_x, int chunk_co_y)
{
	if (ft_isinset(map[chunk_co_x][chunk_co_y].type, rdata->obstacles))
		return (true);
	if (rdata->door_behaviour != ray_pass_door_always
		&& map[chunk_co_x][chunk_co_y].type == DOOR)
		return (map[chunk_co_x][chunk_co_y].status != DOOR_OPEN);
	// if (ft_isinset(map[chunk_co_x][chunk_co_y].type, CHARS_TRANSPARENT))
	// 	return (false);
	return (false);
}
