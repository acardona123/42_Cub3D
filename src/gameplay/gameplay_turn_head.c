/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_turn_head.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:56:00 by acardona          #+#    #+#             */
/*   Updated: 2023/11/13 16:01:05 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/gameplay.h"

/**
 * @brief turns the player head in the given direction. the angle increment is
 *		calculated based on the rotational speed and the fps
 * 
 * @param gen 
 * @param direction direction of the rotation (<0 = left, >0 = right)
 * @param delay time in ms passed since the last rendering (use to keep a
 *		constant rotation velocity)
 */
void	gp_turn_head(t_general *gen, t_head_rotate direction, size_t delay)
{
	if (!direction)
		return ;
	gen->player.p_angle += (float)direction
		* gen->settings.key_turn_speed * delay;
	while (gen->player.p_angle > 2 * M_PI)
		gen->player.p_angle -= 2 * M_PI;
	while (gen->player.p_angle < 0)
		gen->player.p_angle += 2 * M_PI;
	gen->player.p_angle_cos = cosf(gen->player.p_angle);
	gen->player.p_angle_sin = sinf(gen->player.p_angle);
}
