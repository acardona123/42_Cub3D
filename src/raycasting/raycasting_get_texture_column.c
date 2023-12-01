/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_get_texture_column.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 00:32:31 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 20:37:35 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

/**
 * @brief given a certain animated texture, a reference time t0 and a current
 *		time, this function calculates the static texture associated to the
 *		animated texture at this moment.
 * 
 * @param texture pointer to the animated texture
 * @param time current time (in ms)
 * @param t0 reference time for the animated texture, corresponding to the one
 *				of the chunk (in ms)
 * @return t_static_texture* returns the static texture
 */
t_static_texture	*r_get_texture_of_column(t_map *map, t_hitpoint *hitpoint,
	size_t time_now)
{
	register unsigned int	time_in_cycle;
	t_animated_texture		*texture;

	texture = map->map[hitpoint->chunk_co_x][hitpoint->chunk_co_y]
		.textures[hitpoint->hit_face];
	if (texture->frame_number == 1)
		return (&texture->frame_array[0]);
	else
	{
		time_in_cycle = (time_now - map->map[hitpoint->chunk_co_x]
			[hitpoint->chunk_co_y].t0) % texture->frame_cycle_long;
		if (time_in_cycle >= texture->frame_cycle_short)
			return (&texture->frame_array[texture->frame_number - 1]);
		else
			return (&texture->frame_array[time_in_cycle / texture->frame_ms]);
	}
	return (NULL);
}
