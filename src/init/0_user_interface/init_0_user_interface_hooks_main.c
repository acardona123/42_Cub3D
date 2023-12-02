/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0_user_interface_hooks_main.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:27:59 by acardona          #+#    #+#             */
/*   Updated: 2023/12/02 21:12:50 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static int		_in_0_hooks_destroy(void *gen);

#ifdef BONUS

/**
 * @brief initializes all the hooks for the mlx
 *
 * @param gen
 * @return can't fail
 */
void	in_0_hooks_init(t_general *gen)
{
	mlx_hook(gen->disp.win, KeyPress, KeyPressMask, in_0_hooks_keys_press, gen);
	mlx_key_hook(gen->disp.win, in_0_hooks_keys_release, gen);
	mlx_hook(gen->disp.win, MotionNotify, PointerMotionMask,
		in_0_hooks_mouse_move, gen);
	mlx_hook(gen->disp.win, 33, 0L, _in_0_hooks_destroy, gen);
	mlx_mouse_hide(gen->disp.mlx, gen->disp.win);
	mlx_mouse_hook(gen->disp.win, in_0_hooks_mouse_button_press, gen);
	mlx_hook(gen->disp.win, ButtonRelease, ButtonReleaseMask,
		in_0_hooks_mouse_button_release, gen);
}

#else

/**
 * @brief initializes all the hooks for the mlx
 *
 * @param gen
 * @return can't fail
 */
void	in_0_hooks_init(t_general *gen)
{
	mlx_hook(gen->disp.win, KeyPress, KeyPressMask, in_0_hooks_keys_press, gen);
	mlx_key_hook(gen->disp.win, in_0_hooks_keys_release, gen);
	mlx_hook(gen->disp.win, 33, 0L, _in_0_hooks_destroy, gen);
}

#endif

static int	_in_0_hooks_destroy(void *gen)
{
	end_destroy_exit((t_general *)gen, 0);
	return (0);
}
