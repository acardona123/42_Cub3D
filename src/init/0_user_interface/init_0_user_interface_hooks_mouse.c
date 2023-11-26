/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0_user_interface_hooks_mouse.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:29:30 by acardona          #+#    #+#             */
/*   Updated: 2023/11/26 00:42:44 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static const int	g_center_x = WIN_WIDTH / 2;
static const int	g_center_y = WIN_HEIGHT / 2;

int	in_0_hooks_mouse_move(int x, int y, t_general *gen)
{
	if (x == g_center_x && y == g_center_y)
		return (0);
	gen->next_turn_mouse += x - g_center_x;
	mlx_mouse_move(gen->disp.mlx, gen->disp.win, g_center_x, g_center_y);
	return (0);
}

int	in_0_hooks_mouse_button(int key, int x, int y, t_general *gen)
{
	(void)x;
	(void)y;
	if (key == MOUSE_LEFT_CLICK)
		return (gp_action_main(gen), 0);
	//mouse sensibility with scroll
	return (0);
}
