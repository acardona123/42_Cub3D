/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0_user_interface_hooks.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:27:59 by acardona          #+#    #+#             */
/*   Updated: 2023/10/11 20:12:17 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"
#include "../../../includes/gameplay.h"

static int		_in_0_hooks_keys_press(int key, t_general *gen);
static t_bool	_in_0_hooks_keys_move_press(t_general *gen, int key);
static int		_in_0_hooks_keys_move_release(int key, t_general *gen);
static t_bool	_in_0_hooks_keys_settings(t_general *gen, int key);
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
	mlx_hook(gen->disp.win, 2, 1L, _in_0_hooks_keys_press, gen);
	mlx_key_hook(gen->disp.win, _in_0_hooks_keys_move_release, gen);
	mlx_hook(gen->disp.win, 33, 0L, _in_0_hooks_destroy, gen);
}

// /**
//  * @brief initializes all hooks associated to keybord keys release
//  * TODO: function to be done 
//  *
//  * @param key 
//  * @param gen 
//  * @return int 
//  */
// stati
// static int	_in_0_hooks_keys_release(int key, t_general *gen)
// {
	
// }

/**
 * @brief initializes all hooks associated to keybord keys press
 * TODO: function to be done 
 *
 * @param key 
 * @param gen 
 * @return int 
 */
static int	_in_0_hooks_keys_press(int key, t_general *gen)
{
	if (_in_0_hooks_keys_move_press(gen, key) == SUCCESS)
		return (0);
	// if (_in_0_hooks_keys_move_release(gen, key) == SUCCESS)
	// 	return (0);
	// if (key == KEY_ACT)
	// 	return (, 0);//wsa
	if (_in_0_hooks_keys_settings(gen, key) == SUCCESS)
		return (0);
	if (key == XK_Escape)
		end_destroy_exit(gen, 0);
	return (0);
}

/**
 * @brief sets hooks activaed by pressing a key. Goal: move player
 * 
 * @param gen 
 * @param key 
 * @return t_bool 
 */
static t_bool	_in_0_hooks_keys_move_press(t_general *gen, int key)
{
	if (key == KEY_RIGHT)
		return (gen->next_moove[GO_RIGHT] = true, SUCCESS);
	if (key == KEY_LEFT)
		return (gen->next_moove[GO_LEFT] = true, SUCCESS);
	if (key == KEY_FORWARD)
		return (gen->next_moove[GO_FORWARD] = true, SUCCESS);
	if (key == KEY_BACK)
		return (gen->next_moove[GO_BACK] = true, SUCCESS);
	if (key == KEY_LOOK_LEFT)
		return (gen->next_moove[TURN_L] = true, SUCCESS);
	if (key == KEY_LOOK_RIGHT)
		return (gen->next_moove[TURN_R] = true, SUCCESS);
	return (FAIL);
}

/**
 * @brief sets hooks activaed by releasing a key. Goal: stop player mouvement
 * 
 * @param gen 
 * @param key 
 * @return t_bool 
 */
static int	_in_0_hooks_keys_move_release(int key ,t_general *gen)
{
	if (key == KEY_RIGHT)
		return (gen->next_moove[GO_RIGHT] = false, SUCCESS);
	if (key == KEY_LEFT)
		return (gen->next_moove[GO_LEFT] = false, SUCCESS);
	if (key == KEY_FORWARD)
		return (gen->next_moove[GO_FORWARD] = false, SUCCESS);
	if (key == KEY_BACK)
		return (gen->next_moove[GO_BACK] = false, SUCCESS);
	if (key == KEY_LOOK_LEFT)
		return (gen->next_moove[TURN_L] = false, SUCCESS);
	if (key == KEY_LOOK_RIGHT)
		return (gen->next_moove[TURN_R] = false, SUCCESS);
	return (FAIL);
}

//protegerrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
static t_bool	_in_0_hooks_keys_settings(t_general *gen, int key)
{
	if (key == KEY_WALK_SPEED_UP)
		return (gen->settings.walk_speed += WALK_SPEED_INCREMENT, SUCCESS);
	if (key == KEY_WALK_SPEED_DOWN)
		return (gen->settings.walk_speed -= WALK_SPEED_INCREMENT, SUCCESS);
	if (key == KEY_ROT_SPEED_UP)
		return (gen->settings.walk_speed += ROTATE_SPEED_KEY_INCREMENT,
			SUCCESS);
	if (key == KEY_ROT_SPEED_DOWN)
		return (gen->settings.walk_speed -= ROTATE_SPEED_KEY_INCREMENT,
			SUCCESS);
	if (key == KEY_FOV_UP)
		return (gen->settings.walk_speed += FOV_INCREMENT,
			to_angle_set_init(&gen->settings.fov, gen->settings.fov,
				gen->angles_set, gen->angle_correc), SUCCESS);
	if (key == KEY_FOV_DOWN)
		return (gen->settings.walk_speed -= FOV_INCREMENT,
			to_angle_set_init(&gen->settings.fov, gen->settings.fov,
				gen->angles_set, gen->angle_correc), SUCCESS);
	return (FAIL);
}

// static t_bool	_in_0_hooks_mouse(t_general *gen, int key)
// {
// 	return (FAIL);
// }

static int	_in_0_hooks_destroy(void *gen)
{
	end_destroy_exit((t_general *)gen, 0);
	return (0);
}
