/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_1_init_display_hooks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:27:59 by acardona          #+#    #+#             */
/*   Updated: 2023/09/22 22:42:22 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static int	_in_1_hooks_init_keys(int key, t_general *gen);
static int	_in_1_hooks_destroy(void *gen);
// static int	_in_1_ihooks_init_mouse(... , t_general *gen)

/**
 * @brief initializes all the hooks for the mlx
 * TODO: function to be done 
 *
 * @param gen 
 * @return can't fail
 */
void	in_1_hooks_init(t_general *gen)
{
	mlx_hook(gen->disp.mlx, 2, 1L, _in_1_hooks_init_keys, gen);
	mlx_hook(gen->disp.mlx, 17, 0, _in_1_hooks_destroy, gen);
	//mouse_hook
}

/**
 * @brief initializes all hooks associated to keybord keys
 * TODO: function to be done 
 *
 * @param key 
 * @param gen 
 * @return int 
 */
static int	_in_1_hooks_init_keys(int key, t_general *gen)
{
	return (0);
}

/**
 * @brief initializes the hook to close with the cross
 * 
 * @param gen 
 * @return int 
 */
static int	_in_1_hooks_destroy(void *gen)
{
	end_destroy_general((t_general *)gen);
	exit (0); //verifier
	return (0);
}

// static int	_in_1_ihooks_init_mouse(... , t_general *gen)