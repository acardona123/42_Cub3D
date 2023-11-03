/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:44:50 by acardona          #+#    #+#             */
/*   Updated: 2023/11/03 04:57:02 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

/**
 * @brief makes the door change direction : closing if previously opened or
 *		opening, and opening if previously closed or closing.
 *		Updates the status, last action time and the texture of the wall the
 *		door goes through
 * 
 * @param gen 
 * @param action_data 
 * @param face face hited by the ray 
 */
void	doors_action(t_general *gen, t_action *action_data, t_chunk_face face)
{
	size_t			now;
	t_chunk_face	face_to_update;
	int				old_status;

				printf("in door action\n");//
	face_to_update = FACE_W * (face == FACE_N || face == FACE_S)
		+ FACE_S * (face == FACE_E || face == FACE_W);
	old_status = action_data->targets[TARGET_DOOR_ITSELF]->status;
				printf("old_statut: %c\n", "CcOo"[old_status]);//
	now = to_getime();
	if (old_status == DOOR_CLOSED || old_status == DOOR_CLOSING)
	{
				printf("ici\n");
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
				printf("new_statut: %c\n", "CcOo"[(int)action_data->targets[TARGET_DOOR_ITSELF]->status]);//
				printf("now: %ld\nold_time: %ld\n", now, action_data->time_last_act);//
	action_data->time_last_act = now
		- (old_status == DOOR_CLOSING || old_status == DOOR_OPENING)
		* (action_data->time_last_act + DOOR_ACTION_TIME - now);
				printf("new_time: %ld\n", action_data->time_last_act);//
	doors_update_texture_main_side(&gen->textures,
		action_data->targets[TARGET_DOOR_ITSELF]);
}
