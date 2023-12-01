/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_action_doors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:44:50 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 18:03:33 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

#ifdef BONUS

static void	_gp_action_doors_sub(t_general *gen, size_t time_now,
				t_chunk *door, t_chunk_face face_to_update);

/**
 * @brief makes the door change direction : closing if previously opened or
 *		opening, and opening if previously closed or closing.
 *		Updates the status, last action time and the texture of the wall the
 *		door goes through
 * 
 * @param gen 
 * @param time_now
 * @param hit_pt hitpoint of the action ray
 */
void	gp_action_doors(t_general *gen, size_t time_now, t_hitpoint *hit_pt)
{
	t_chunk			*door;
	t_chunk_face	face_to_update;

	door = &gen->map.map[hit_pt->chunk_co_x][hit_pt->chunk_co_y];
	face_to_update
		= FACE_W * (hit_pt->hit_face == FACE_N || hit_pt->hit_face == FACE_S)
		+ FACE_S * (hit_pt->hit_face == FACE_E || hit_pt->hit_face == FACE_W);
	_gp_action_doors_sub(gen, time_now, door, face_to_update);
	maps_world_update_door(gen, door->action->targets[TARGET_DOOR_ITSELF]);
	maps_bigmap_draw_chunk(&gen->minimap,
		door->action->targets[TARGET_DOOR_ITSELF]->chunk_co.x,
		door->action->targets[TARGET_DOOR_ITSELF]->chunk_co.y);
}

/**
 * @brief subfunction of gp_action_doors, updates the door data (status,
 *		adjacent, textures)
 * 
 * @param gen 
 * @param time_now 
 * @param door 
 * @param face_to_update 
 */
static void	_gp_action_doors_sub(t_general *gen, size_t time_now,
	t_chunk *door, t_chunk_face face_to_update)
{
	int				old_status;

	old_status = door->action->targets[TARGET_DOOR_ITSELF]->status;
	if (old_status == DOOR_CLOSED || old_status == DOOR_CLOSING)
	{
		door->action->targets[TARGET_DOOR_ITSELF]->status = DOOR_OPENING;
		sh_chunk_set_texture(door->action->targets[TARGET_DOOR_SIDE],
			face_to_update, &gen->textures.door_side_open_opening, false);
	}
	else if (old_status == DOOR_OPEN || old_status == DOOR_OPENING)
	{
		door->action->targets[TARGET_DOOR_ITSELF]->status = DOOR_CLOSING;
		sh_chunk_set_texture(door->action->targets[TARGET_DOOR_SIDE],
			face_to_update, &gen->textures.door_side_open_closing, false);
	}
	door->action->time_last_act = time_now
		- (old_status == DOOR_CLOSING || old_status == DOOR_OPENING)
		* (door->action->time_last_act + ACTION_DOOR_TIME - time_now);
}

#endif