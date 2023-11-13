/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get_pixel_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:02:34 by acardona          #+#    #+#             */
/*   Updated: 2023/11/13 19:52:06 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map.h"

inline static t_vector_f	_map_get_world_relative_position_minimap(
								t_general *gen, float delta_x_map,
								float delta_y_map);
inline static t_vector_f	_map_get_world_relative_position_bigmap(
								t_general *gen, float delta_x_map,
								float delta_y_map);

/**
 * @brief get the color of the pixel correspondind to the chunk in the map
 * 
 * @param gen 
 * @param x the x position of the pixel in the minimap
 * @param y the y position of the pixel in the minimap
 * @return int the color of the pixel
 */
int	map_get_pixel_color(t_general *gen, t_map_type type, int x_map, int y_map)
{
	t_vector_f	world_position;

	if (type == MINIMAP)
		world_position = _map_get_world_relative_position_minimap(gen,
				x_map - (gen->settings.minimap_size >> 1),
				y_map - (gen->settings.minimap_size >> 1));
	else
		world_position = _map_get_world_relative_position_bigmap(gen,
				x_map - (gen->settings.minimap_size >> 1),
				y_map - (gen->settings.minimap_size >> 1));
	world_position.x += gen->player.p_co.x;
	world_position.y += gen->player.p_co.y;
	if (world_position.x < 0 || world_position.x >= gen->map.width
		|| world_position.y < 0 || world_position.y >= gen->map.height)
		return (MINIMAP_COLOR_NOTHING);
	return (*(int *)(gen->minimap.world.addr
		+ (gen->map.height - (int)world_position.y)
		* gen->minimap.world.line_len
		+ (int)world_position.x * gen->minimap.world.opp));
}

/**
 * @brief gets the position of chunk targettedby the minimap pixel (in float),
 *		with map rotation and zoom
 * 
 * @param gen 
 * @param delta_x_map coordinate x of the pixel in the minimap relative to its
 *	center
 * @param delta_y_map 
 * @return t_vector_f
 */
inline static t_vector_f	_map_get_world_relative_position_minimap(
	t_general *gen, float delta_x_map, float delta_y_map)
{
	t_vector_f	world_relative;

	delta_x_map /= gen->settings.minimap_zoom;
	delta_y_map /= gen->settings.minimap_zoom;
	world_relative.x = delta_x_map * gen->player.p_angle_cos
		- delta_y_map * gen->player.p_angle_sin;
	world_relative.y = -delta_x_map * gen->player.p_angle_sin
		- delta_y_map * gen->player.p_angle_cos;
	return (world_relative);
}

/**
 * @brief gets the position of chunk targettedby the minimap pixel (in float),
 *		with map zoom, no rotation
 * 
 * @param gen 
 * @param delta_x_map coordinate x of the pixel in the minimap relative to its
 *	center
 * @param delta_y_map 
 * @return t_vector_f
 */
inline static t_vector_f	_map_get_world_relative_position_bigmap(
	t_general *gen, float delta_x_map, float delta_y_map)
{
	t_vector_f	world_relative;

	world_relative.x = delta_x_map / gen->settings.minimap_zoom;
	world_relative.y = delta_y_map / gen->settings.minimap_zoom;
	return (world_relative);
}
