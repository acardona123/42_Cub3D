/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_action_main.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:15:20 by acardona          #+#    #+#             */
/*   Updated: 2023/12/06 00:44:21 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

#ifdef BONUS

/**
 * @brief sends a ray in front of the player. If the chunk touched triger an
 *		action and is close enough then the action is done.
 * 
 * @param gen 
 */
void	gp_action_main(t_general *gen)
{
	t_hitpoint	hit_point;
	t_chunk		*hit_chunk;
	size_t		time_now;

	time_now = to_getime();
	hit_point = r_ray_hit(gen, (t_ray_params){ray_action, time_now,
			gen->player.p_co, gen->player.p_angle});
	hit_chunk = &gen->map.map[hit_point.chunk_co_x][hit_point.chunk_co_y];
	if (!hit_chunk->action || !hit_chunk->action->active_faces)
		return ;
	hit_point.dist = to_vector_norm(gen->player.p_co, hit_point.pt_co);
	if (hit_point.dist > hit_chunk->action->dist_range)
		return ;
	(*hit_chunk->action->execute)(gen, time_now, &hit_point);
}

#else

/**
 * @brief sends a ray in front of the player. If the chunk touched triger an
 *		action and is close enough then the action is done.
 * 
 * @param gen 
 */
void	gp_action_main(t_general *gen)
{
	(void)gen;
}

#endif