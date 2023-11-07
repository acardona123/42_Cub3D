/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:15:20 by acardona          #+#    #+#             */
/*   Updated: 2023/11/07 01:38:01 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

/**
 * @brief sends a ray in front of the player. If the chunk touched triger an
 *		action and is close enough then the action is done.
 * 
 * @param gen 
 */
void	gp_action_do(t_general *gen)
{
	t_hitpoint	hit_point;
	t_chunk		*hit_chunk;
	size_t		time_now;

				// printf("\n\e[103maction\e[0m\n---\n");//
	time_now = to_getime();
	hit_point = r_ray_hit(gen, (t_ray_params){ray_action, time_now,
			gen->player.p_co, gen->player.p_angle});
	hit_chunk = &gen->map.map[hit_point.chunk_co_x][hit_point.chunk_co_y];
				// printf("hit chunk : (%d, %d)->%c (%p)\n", hit_point.chunk_co_x,hit_point.chunk_co_y, hit_chunk->type, &hit_chunk);//
				// if (hit_chunk->action)//
				// 	printf("action (%p):\n target: {%p, %p}\n t_last_act: %zu\n range: %f\n execute: %p\n---\n", hit_chunk->action, &hit_chunk->action[0], &hit_chunk->action[1], hit_chunk->action->time_last_act, hit_chunk->action->dist_range, hit_chunk->action->execute);//
				// else//
				//  	printf("no action\n");//
	if (!hit_chunk->action)
		return ;
	hit_point.dist = to_vector_norm(gen->player.p_co, hit_point.pt_co);
	if (hit_point.dist > hit_chunk->action->dist_range)
		return ;
	(*hit_chunk->action->execute)(gen, time_now, hit_chunk->action,
		hit_point.hit_face);
}
