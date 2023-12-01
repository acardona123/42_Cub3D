/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_doors_update.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:35:26 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 16:53:44 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doors.h"

#ifdef BONUS

/**
 * @brief updates the door status if it was closing or opening based on the
 *	current time and the time it started to move.
 *	Updates t_chunk->extra_data_f : takes the width of the opening of the door
 *		(0 = closed, 0.5 = mid-opened, 1 = fully opended and so on)
 *	If the door status changed due to time running then the texture of the
 *		door and/or the adjacent walls may need an update, the funtion therefore
 *		returns true
 *	note: static variables have been used to avoid repeating the calculous when
 *	consecutive ray hit the same door in the same frame during the raycasting
 *	
 * 
 * @param gen
 * @param door chunk of the map corresponding to the door to update
 * @param time time at which the ray has been thrown
 * @return true the door status changed due to time, the texture has to beupdated
 * @return false no change in the door sttus
 *		
 */
bool	sh_doors_update_status(t_general *gen, t_chunk *door, size_t time)
{
	static t_door_last_update	last = {0, NULL, 0.};

	if (time == last.time && door == last.chunk)
		return (door->extra_data_f = last.data, false);
	last = (t_door_last_update){time, door, time - door->action->time_last_act};
	if (door->status == DOOR_OPEN)
		last.data = 1.;
	else if (door->status == DOOR_CLOSED)
		last.data = 0.;
	else if (door->status == DOOR_CLOSING && last.data >= ACTION_DOOR_TIME)
		return (door->status = DOOR_CLOSED, last.data = 0.,
			door->extra_data_f = last.data, true);
	else if (door->status == DOOR_CLOSING)
		last.data = 1. - last.data / ACTION_DOOR_TIME;
	else if (door->status == DOOR_OPENING && last.data >= ACTION_DOOR_TIME)
		return (door->status = DOOR_OPEN, maps_world_update_door(gen, door),
			maps_bigmap_draw_chunk(&gen->minimap, door->chunk_co.x,
				door->chunk_co.y), last.data = 1., door->extra_data_f = 1.,
			true);
	else if (door->status == DOOR_OPENING)
		last.data = last.data / ACTION_DOOR_TIME;
	return (door->extra_data_f = last.data, false);
}

/**
 * @brief updates the texture of the wall the door goes through when opening and
 *			closing (different animation depending on the door movement)
 * 
 * @param texture_pack 
 * @param door 
 */
void	sh_doors_update_texture_main_side(t_texture_pack *texture_pack,
	t_chunk *door)
{
	t_chunk_face	face_to_update;

	if (door->extra_data_i & 1 << DOOR_HORIZONTAL)
		face_to_update = FACE_W;
	else
		face_to_update = FACE_S;
	if (door->status == DOOR_OPEN)
		sh_chunk_set_texture(door->action->targets[TARGET_DOOR_SIDE],
			face_to_update, &texture_pack->door_side_open_opened, false);
	else if (door->status == DOOR_OPENING)
		sh_chunk_set_texture(door->action->targets[TARGET_DOOR_SIDE],
			face_to_update, &texture_pack->door_side_open_opening, false);
	else if (door->status == DOOR_CLOSED)
		sh_chunk_set_texture(door->action->targets[TARGET_DOOR_SIDE],
			face_to_update, &texture_pack->door_side_open_closed, false);
	else if (door->status == DOOR_CLOSING)
		sh_chunk_set_texture(door->action->targets[TARGET_DOOR_SIDE],
			face_to_update, &texture_pack->door_side_open_closing, false);
}

#endif