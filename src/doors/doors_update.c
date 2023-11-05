/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:35:26 by acardona          #+#    #+#             */
/*   Updated: 2023/11/05 01:16:42 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doors.h"

#ifdef BONUS

/**
 * @brief updates the door status if it was closing or opening based on the
 *	current time and the time it starts to move.
 *	note: static variables have been used to avoid repeating the calculous when
 *	consecutive ray hit the same door in the same frame during the raycasting
 *	
 * 
 * @param door chunk of the map correspondingto the door to update
 * @param time time at which the ray has been thrown
 * @return float returns the width of the opening of the door (0 = closed, 0.5 =
 *		mid-opened, 1 = fully opended and so on). This value is also saved in
 *		the t_chunk->extra_data_f.
 *		If the door status changed due to time running then the texture of the
 *		door and/or the adjacent walls may need an update. The extra_data_i is
 *		therefore updated (add DOOR_TEXTURE_NEED_UPDATE to it) for further
 *		detection of this update need
 */
float	doors_update_status(t_chunk *door, size_t time)
{
	static t_door_last_update	last = {0, NULL, 0.};

	if (time == last.time && door == last.chunk)
		return (door->extra_data_f = last.data, last.data);
	last = (t_door_last_update){time, door, time - door->action->time_last_act};//here the data is just temporary used as a buffer for the delta-time value, for norm puposes
	if (door->status == DOOR_CLOSING && last.data >= DOOR_ACTION_TIME)
	{
		door->status = DOOR_CLOSED;
		door->extra_data_i |= 1 << DOOR_TEXTURE_NEED_UPDATE;//can use = instead of += if extra_data isn´t used for any other info transmission
	}
	else if (door->status == DOOR_CLOSING)
		last.data = 1. - last.data / DOOR_ACTION_TIME;
	else if (door->status == DOOR_OPENING && last.data >= DOOR_ACTION_TIME)
	{
		door->status = DOOR_OPEN;
		door->extra_data_i |= 1 << DOOR_TEXTURE_NEED_UPDATE;
	}
	else if (door->status == DOOR_OPENING)
		last.data = last.data / DOOR_ACTION_TIME;
	if (door->status == DOOR_OPEN)
		last.data = 1.;
	else if (door->status == DOOR_CLOSED)
		last.data = 0.;
	return (door->extra_data_f = last.data, last.data);
}

/**
 * @brief updates the texture of the wall the door goes through when opening and
 *			closing (different animation depending on the door movement)
 * 
 * @param texture_pack 
 * @param door 
 */
void	doors_update_texture_main_side(t_texture_pack *texture_pack,
	t_chunk *door)
{
	t_chunk_face	face_to_update;

	if (door->extra_data_i & 1 << DOOR_TEXTURE_NEED_UPDATE)
		door->extra_data_i -= 1 << DOOR_TEXTURE_NEED_UPDATE;
	if (door->extra_data_i & 1 << DOOR_HORIZONTAL)
		face_to_update = FACE_W;
	else
		face_to_update = FACE_S;
	if (door->status == DOOR_OPEN)
		door->action->targets[TARGET_DOOR_SIDE]->textures[face_to_update]
			= texture_pack->door_side_open_opened;
	else if (door->status == DOOR_OPENING)
		door->action->targets[TARGET_DOOR_SIDE]->textures[face_to_update]
			= texture_pack->door_side_open_opening;
	else if (door->status == DOOR_CLOSED)
		door->action->targets[TARGET_DOOR_SIDE]->textures[face_to_update]
			= texture_pack->door_side_open_closed;
	else if (door->status == DOOR_CLOSING)
		door->action->targets[TARGET_DOOR_SIDE]->textures[face_to_update]
			= texture_pack->door_side_open_closing;
}

#else

/**
 * @brief unused
 * 
 * @param door 
 * @param time 
 * @return float 
 */
float	doors_update_status(t_chunk *door, size_t time)
{
	(void)door;
	(void)time;
	return (0.);
}

void	doors_update_texture_main_side(t_texture_pack *texture_pack,
	t_chunk *door)
{
	(void)texture_pack;
	(void)door;
}

#endif