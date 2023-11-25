/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:44:50 by acardona          #+#    #+#             */
/*   Updated: 2023/11/23 19:53:31 by acardona         ###   ########.fr       */
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
void	doors_action(t_general *gen, size_t time_now, t_chunk *chunk,
	t_chunk_face face)
{
	t_chunk_face	face_to_update;
	int				old_status;

	face_to_update = FACE_W * (face == FACE_N || face == FACE_S)
		+ FACE_S * (face == FACE_E || face == FACE_W);
	old_status = chunk->action->targets[TARGET_DOOR_ITSELF]->status;
	if (old_status == DOOR_CLOSED || old_status == DOOR_CLOSING)
	{
		chunk->action->targets[TARGET_DOOR_ITSELF]->status = DOOR_OPENING;
		init_chunk_set_texture(chunk->action->targets[TARGET_DOOR_SIDE],
			face_to_update, &gen->textures.door_side_open_opening, false);
	}
	else if (old_status == DOOR_OPEN || old_status == DOOR_OPENING)
	{
		chunk->action->targets[TARGET_DOOR_ITSELF]->status = DOOR_CLOSING;
		init_chunk_set_texture(chunk->action->targets[TARGET_DOOR_SIDE],
			face_to_update, &gen->textures.door_side_open_closing, false);
	}
	chunk->action->time_last_act = time_now
		- (old_status == DOOR_CLOSING || old_status == DOOR_OPENING)
		* (chunk->action->time_last_act + DOOR_ACTION_TIME - time_now);
	maps_world_update_door(gen, chunk->action->targets[TARGET_DOOR_ITSELF]);
	maps_bigmap_draw_chunk(&gen->minimap,
		chunk->action->targets[TARGET_DOOR_ITSELF]->chunk_co.x,
		chunk->action->targets[TARGET_DOOR_ITSELF]->chunk_co.y);
}

#else

void	doors_action(t_general *gen, size_t time_now, t_action *action_data,
	t_chunk_face face)
{
	(void)gen;
	(void)time_now;
	(void)action_data;
	(void)face;
}

#endif