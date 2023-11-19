/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_get_texture_column.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 00:32:31 by acardona          #+#    #+#             */
/*   Updated: 2023/11/17 17:32:10 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

#ifdef BONUS

/**
 * @brief checks if the bloc hit by the ray need a texture update before being
 *	casted
 *	note: for the current frame this texture update will not affect the colums
 *	of pixels already generated fr the raycasting (ie the one on the left side
 *	of the current column)
 * @param texture_pack 
 * @param map 
 * @param hit_point 
 * @param time time when the ray was seent
 */
void	r_update_texture(t_texture_pack *texture_pack, t_map *map,
	t_hitpoint *hit_point, size_t time)
{
	static size_t	last_time;
	static t_chunk	*last_chunk;

	if (time == last_time && &map->map[hit_point->chunk_co_x]
		[hit_point->chunk_co_y] == last_chunk)
		return ;
	last_time = time;
	last_chunk = &map->map[hit_point->chunk_co_x][hit_point->chunk_co_y];
	if (last_chunk->type == DOOR
		&& last_chunk->extra_data_i & 1 << DOOR_TEXTURE_NEED_UPDATE)
		doors_update_texture_main_side(texture_pack, last_chunk);
}

#else

void	r_update_texture(t_texture_pack *texture_pack, t_map *map,
	t_hitpoint *hit_point, size_t time)
{
	(void)texture_pack;
	(void)map;
	(void)hit_point;
	(void)time;
}

#endif

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
