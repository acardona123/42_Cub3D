/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get_pixel_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:02:34 by acardona          #+#    #+#             */
/*   Updated: 2023/11/11 23:35:49 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map.h"

/**
 * @brief get the color of the pixel correspondind to the chunk in the map
 * 
 * @param gen 
 * @param x the x position of the pixel in the minimap
 * @param y the y position of the pixel in the minimap
 * @return int the color of the pixel
 */
int	map_get_pixel_color(t_general *gen, int x_map, int y_map)
{
	float	in_world_x;//ici on peut gagner en erformances en ne passant pas par des variales mais directement le calcul
	float	in_world_y;

	in_world_x = gen->player.p_co.x
		+ (float)(x_map - (gen->settings.minimap_size >> 1))
		/ gen->settings.minimap_zoom;
	in_world_y = gen->player.p_co.y
		+ (float)((gen->settings.minimap_size >> 1) - y_map)
		/ gen->settings.minimap_zoom;
	if (in_world_x < 0 || in_world_x >= gen->map.width
		|| in_world_y < 0 || in_world_y >= gen->map.height)
		return (MINIMAP_COLOR_NOTHING);
	return (*(int *)(gen->minimap.world.addr
		+ (gen->map.height - (int)in_world_y) * gen->minimap.world.line_len
		+ (int)in_world_x * gen->minimap.world.opp));
}
