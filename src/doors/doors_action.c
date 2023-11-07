/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:44:50 by acardona          #+#    #+#             */
/*   Updated: 2023/11/07 01:42:06 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

#ifdef BONUS

/**
 * @brief makes the door change direction : closing if previously opened or
 *		opening, and opening if previously closed or closing.
 *		Updates the status, last action time and the texture of the wall the
 *		door goes through
 * 
 * @param gen 
 * @param time_now
 * @param action_data 
 * @param face face hited by the ray 
 */
void	doors_action(t_general *gen, size_t time_now, t_action *action_data,
	t_chunk_face face)
{
	t_chunk_face	face_to_update;
	int				old_status;

				// printf("in door action\n");//
	face_to_update = FACE_W * (face == FACE_N || face == FACE_S)
		+ FACE_S * (face == FACE_E || face == FACE_W);
	old_status = action_data->targets[TARGET_DOOR_ITSELF]->status;
				//printf("old_statut: %c\n", "CcOo"[old_status]);//
	if (old_status == DOOR_CLOSED || old_status == DOOR_CLOSING)
	{
				//printf("ici\n");
		action_data->targets[TARGET_DOOR_ITSELF]->status = DOOR_OPENING;
		action_data->targets[TARGET_DOOR_SIDE]->textures[face_to_update]
			= gen->textures.door_side_open_opening;
	}
	else if (old_status == DOOR_OPEN || old_status == DOOR_OPENING)
	{
		action_data->targets[TARGET_DOOR_ITSELF]->status = DOOR_CLOSING;
		action_data->targets[TARGET_DOOR_SIDE]->textures[face_to_update]
			= gen->textures.door_side_open_closing;
	}
				//printf("new_statut: %c\n", "CcOo"[(int)action_data->targets[TARGET_DOOR_ITSELF]->status]);//
				//printf("now: %ld\nold_time: %ld\n", now, action_data->time_last_act);//
	action_data->time_last_act = time_now
		- (old_status == DOOR_CLOSING || old_status == DOOR_OPENING)
		* (action_data->time_last_act + DOOR_ACTION_TIME - time_now);
				//printf("new_time: %ld\n", action_data->time_last_act);//
}

#else

void	doors_action(t_general *gen, size_t time_now, t_action *action_data, t_chunk_face face)
{
	(void)gen;
	(void)time_now;
	(void)action_data;
	(void)face;
}

#endif