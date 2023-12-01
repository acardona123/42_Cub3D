/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_turn_head.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:56:00 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 18:29:20 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

#ifdef BONUS

/**
 * @brief turns the player head in the direction given by gen->next_turn_key.
 *		the angle increment is calculated based on the rotational speed and
 *		the delay between frames
 * 
 * @param gen 
 * @param delay time in ms passed since the last rendering (use to keep a
 *		constant rotation velocity)
 */
void	gp_turn_head(t_general *gen, size_t delay)
{
	if (gen->next_turn_key[TURN_L] || gen->next_turn_key[TURN_R])
	{
		gen->player.p_angle += (float)(gen->next_turn_key[TURN_R]
				- gen->next_turn_key[TURN_L])
			*gen->settings.key_turn_speed * delay;
	}
	else if (gen->next_turn_mouse)
	{
		gen->player.p_angle
			+= gen->next_turn_mouse * gen->settings.mouse_turn_sensibility;
	}
	else
		return ;
	gen->next_turn_mouse = 0.f;
	while (gen->player.p_angle > 2 * M_PI)
		gen->player.p_angle -= 2 * M_PI;
	while (gen->player.p_angle < 0)
		gen->player.p_angle += 2 * M_PI;
	gen->player.p_angle_cos = cosf(gen->player.p_angle);
	gen->player.p_angle_sin = sinf(gen->player.p_angle);
}

#else

/**
 * @brief turns the player head in the direction given by gen->next_turn_key.
 *		the angle increment is fixed as in this mandatory part the delay is
 *		ignored
 * 
 * @param gen 
 * @param delay ignored
 */
void	gp_turn_head(t_general *gen, size_t delay)
{
	(void)delay;
	if (gen->next_turn_key[TURN_L] || gen->next_turn_key[TURN_R])
	{
		gen->player.p_angle += (float)(gen->next_turn_key[TURN_R]
				- gen->next_turn_key[TURN_L])
			*gen->settings.key_turn_speed * FIXED_DELAY;
	}
	else
		return ;
	while (gen->player.p_angle > 2 * M_PI)
		gen->player.p_angle -= 2 * M_PI;
	while (gen->player.p_angle < 0)
		gen->player.p_angle += 2 * M_PI;
	gen->player.p_angle_cos = cosf(gen->player.p_angle);
	gen->player.p_angle_sin = sinf(gen->player.p_angle);
}

#endif