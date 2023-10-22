/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:11:15 by acardona          #+#    #+#             */
/*   Updated: 2023/10/21 23:14:02 by acardona         ###   ########.fr       */
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
 * @brief checks if the chunk in which the point (float coordinates) is an
 *		obstacle for the ray (not floor or nothing)
 * 
 * @param map 
 * @param x 
 * @param y 
 * @return true is an ostacle
 * @return false is "transparent" to the ray
 */
bool	r_is_obstacle_f(t_map *map, float x, float y)
{
	if (map->map[(int)x][(int)y].type != NOTHING
		&& map->map[(int)x][(int)y].type != FLOOR)
		return (true);
	return (false);
}

/**
 * @brief checks if the chunk designated by the coordinates x and y is an
 *		obstacle for the ray (not floor or nothing)
 * 
 * @param map 
 * @param x 
 * @param y 
 * @return true is an ostacle
 * @return false is "transparent" to the ray
 */
bool	r_is_obstacle_i(t_map *map, int x, int y)
{
	if (map->map[x][y].type != NOTHING
		&& map->map[x][y].type != FLOOR)
		return (true);
	return (false);
}
