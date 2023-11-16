/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_turn_head.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:56:00 by acardona          #+#    #+#             */
/*   Updated: 2023/11/16 16:25:03 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

#ifdef BONUS

/**
 * @brief turns the player head in the given direction. the angle increment is
 *		calculated based on the rotational speed and the fps
 * 
 * @param gen 
 * @param delay time in ms passed since the last rendering (use to keep a
 *		constant rotation velocity)
 * @param turn_keys indicates wich rotatioal key is currently pressed
 * @param turn_mouse contains the number of pixels traveled by the mouse since\
 *		the last frame)
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
 * @brief turns the player head in the given direction. the angle increment is
 *		calculated based on the rotational speed and the fps
 * 
 * @param gen 
 * @param delay time in ms passed since the last rendering (use to keep a
 *		constant rotation velocity)
 * @param turn_keys indicates wich rotatioal key is currently pressed
 * @param turn_mouse contains the number of pixels traveled by the mouse since\
 *		the last frame)
 */
void	gp_turn_head(t_general *gen, size_t delay)
{
	if (gen->next_turn_key[TURN_L] || gen->next_turn_key[TURN_R])
	{
		gen->player.p_angle += (float)(gen->next_turn_key[TURN_R]
				- gen->next_turn_key[TURN_L])
			*gen->settings.key_turn_speed * delay;
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