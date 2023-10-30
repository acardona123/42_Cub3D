/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:35:26 by acardona          #+#    #+#             */
/*   Updated: 2023/10/30 03:17:36 by acardona         ###   ########.fr       */
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
 *		the t_chunk->extra_data.
 */
float	doors_update_status(t_chunk *door, size_t time)
{
	static t_door_last_update	last = {0, NULL, 0.};

	if (time == last.time && door == last.chunk)
		return (door->extra_data = last.data, last.data);
	last = (t_door_last_update){time, door, time - door->tlast_action};//here the data is just temporary used as a buffer for the delta-time value, for norm puposes
	if (door->status == DOOR_OPEN)
		last.data = 1.;
	else if (door->status == DOOR_CLOSED)
		last.data = 0.;
	else if (door->status == DOOR_CLOSING && last.data >= DOOR_ACTION_TIME)
	{
		door->status = DOOR_CLOSED;
		last.data = 0.;
	}
	else if (door->status == DOOR_CLOSING)
		last.data = 1. - last.data / DOOR_ACTION_TIME;
	else if (door->status == DOOR_OPENING && last.data >= DOOR_ACTION_TIME)
	{
		door->status = DOOR_OPEN;
		last.data = 1.;
	}
	else//ie else id (door->status == DOOR_OPENING && ... <= ...)
		last.data = last.data / DOOR_ACTION_TIME;
	door->extra_data = last.data;
	return (last.data);
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
#endif