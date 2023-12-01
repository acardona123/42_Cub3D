/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_update_world.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 23:47:05 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 19:59:42 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/maps.h"

#ifdef BONUS

/**
 * @brief gets the map color of a chunk based on the world image
 * 
 * @param minimap 
 * @param map_height 
 * @param chunk_x 
 * @param chunk_y 
 * @return int 
 */
int	maps_world_get_chunk_color(t_minimap *minimap, int chunk_x, int chunk_y)
{
	return (*(int *)(minimap->world.addr
		+ (minimap->world.pix_height - chunk_y) * minimap->world.line_len
		+ chunk_x * minimap->world.opp));
}

void	maps_world_update_door(t_general *gen, t_chunk *chunk)
{
	if (chunk->status == DOOR_OPEN)
		*(int *)(gen->minimap.world.addr
				+ chunk->chunk_co.x * gen->minimap.world.opp
				+ (gen->map.height - chunk->chunk_co.y)
				* gen->minimap.world.line_len)
			= MINIMAP_COLOR_D_OPEN;
	else
		*(int *)(gen->minimap.world.addr
				+ chunk->chunk_co.x * gen->minimap.world.opp
				+ (gen->map.height - chunk->chunk_co.y)
				* gen->minimap.world.line_len)
			= MINIMAP_COLOR_D_CLOSED;
}

#endif