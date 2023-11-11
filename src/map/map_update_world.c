/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_update_world.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 23:47:05 by acardona          #+#    #+#             */
/*   Updated: 2023/11/12 00:15:58 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map.h"

void	map_update_world_door(t_general *gen, t_chunk *chunk)
{
	if (chunk->status == DOOR_OPEN)
		*(int *)(gen->minimap.world.addr
				+ chunk->chunk_co.x * gen->minimap.world.opp
				+ (gen->map.height - chunk->chunk_co.y) * gen->minimap.world.line_len)
			= MINIMAP_COLOR_D_OPEN;
	else
		*(int *)(gen->minimap.world.addr
				+ chunk->chunk_co.x * gen->minimap.world.opp
				+ (gen->map.height - chunk->chunk_co.y) * gen->minimap.world.line_len)
			= MINIMAP_COLOR_D_CLOSED;
}
