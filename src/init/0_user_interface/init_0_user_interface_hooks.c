/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0_user_interface_hooks.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:27:59 by acardona          #+#    #+#             */
/*   Updated: 2023/10/05 01:34:11 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"
#include "../../../includes/gameplay.h"

static int		_in_0_hooks_keys(int key, t_general *gen);
static t_bool	_in_0_hooks_keys_move(t_general *gen, int key);
// static t_bool	_in_0_hooks_keys_settings(t_general *gen, int key);
static int		_in_0_hooks_destroy(void *gen);
// static int	_in_0_ihooks_init_mouse(... , t_general *gen)

/**
 * @brief initializes all the hooks for the mlx
 * TODO: function to be done 
 *
 * @param gen 
 * @return can't fail
 */
void	in_0_hooks_init(t_general *gen)
{
	mlx_hook(gen->disp.win, 2, 1L, _in_0_hooks_keys, gen);
	mlx_hook(gen->disp.win, 33, 0L, _in_0_hooks_destroy, gen);
}


/**
 * @brief initializes all hooks associated to keybord keys
 * TODO: function to be done 
 *
 * @param key 
 * @param gen 
 * @return int 
 */
static int	_in_0_hooks_keys(int key, t_general *gen)
{
	if (_in_0_hooks_keys_move(gen, key) == SUCCESS)
		return (0);
	// if (key == KEY_ACT)
	// 	return (, 0);//wsa
	// if (_in_0_hooks_keys_settings(gen, key))
	// 	return (0);
	if (key == XK_Escape)
		end_destroy_exit(gen, 0);
	printf("XK_Escape = %d, touche = %d\n", XK_Escape, key);
	return (0);
}

static t_bool	_in_0_hooks_keys_move(t_general *gen, int key)
{
	if (key == KEY_RIGHT)
		return (game_move_player(gen, (t_vector_f){1., 0.}), SUCCESS);
	if (key == KEY_LEFT)
		return (game_move_player(gen, (t_vector_f){-1., 0.}), SUCCESS);
	if (key == KEY_FORWARD)
		return (game_move_player(gen, (t_vector_f){0., 1.}), SUCCESS);
	if (key == KEY_BACK)
		return (game_move_player(gen, (t_vector_f){0., -1.}), SUCCESS);
	if (key == KEY_LOOK_LEFT)
		return (game_turn_head(gen, TURN_SIGN_L), SUCCESS);
	if (key == KEY_LOOK_RIGHT)
		return (game_turn_head(gen, TURN_SIGN_R), SUCCESS);
	return (FAIL);
}

// static t_bool	_in_0_hooks_keys_settings(t_general *gen, int key)
// {
// 	if (key == KEY_WALK_SPEED_UP)
// 		return (gen->settings.walk_speed  += WALK_SPEED_INCREMENT, SUCCESS);
// 	if (key == KEY_WALK_SPEED_DOWN)
// 		return (gen->settings.walk_speed  -= WALK_SPEED_INCREMENT, SUCCESS);
// 	if (key == KEY_ROT_SPEED_UP)
// 		return (gen->settings.walk_speed  += ROTATE_SPEED_KEY_INCREMENT, SUCCESS);
// 	if (key == KEY_ROT_SPEED_DOWN)
// 		return (gen->settings.walk_speed  -= ROTATE_SPEED_KEY_INCREMENT, SUCCESS);
// 	if (key == KEY_FOV_UP)
// 		return (gen->settings.walk_speed  += FOV_INCREMENT, SUCCESS);//recalculer les angles_set
// 	if (key == KEY_FOV_DOWN)
// 		return (gen->settings.walk_speed  -= FOV_INCREMENT, SUCCESS);//recalculer les angles_set
// }

// static t_bool	_in_0_hooks_mouse(t_general *gen, int key)
// {
// 	return (FAIL);
// }

static int	_in_0_hooks_destroy(void *gen)
{
	end_destroy_exit((t_general *)gen, 0);
	return (0);
}
