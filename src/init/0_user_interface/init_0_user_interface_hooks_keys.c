/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_0_user_interface_hooks_keys.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:24:43 by acardona          #+#    #+#             */
/*   Updated: 2023/11/16 18:37:24 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static int		_in_0_hooks_keys_release_move(t_general *gen, int key);
static t_bool	_in_0_hooks_keys_press_move(t_general *gen, int key);
static t_bool	_in_0_hooks_keys_press_settings(t_general *gen, int key);

/**
 * @brief initializes all hooks associated to keybord keys press
 *
 * @param key
 * @param gen
 * @return int 0 anyway
 */
int	in_0_hooks_keys_press(int key, t_general *gen)
{
	if (_in_0_hooks_keys_press_move(gen, key) == SUCCESS)
		return (0);
	if (_in_0_hooks_keys_press_settings(gen, key) == SUCCESS)
		return (0);
	if (key == KEY_ACT)
		return (gp_action_main(gen), 0);
	if (key == XK_Escape)
		end_destroy_exit(gen, 0);
	return (0);
}

/**
 * @brief initializes all hooks associated to keybord keys release
 *
 * @param key
 * @param gen
 * @return int 0 anyway
 */
int	in_0_hooks_keys_release(int key, t_general *gen)
{
	if (_in_0_hooks_keys_release_move(gen, key) == SUCCESS)
		return (0);

	if (key == KEY_BIG_MAP)
		return (gen->disp.render_selec = RENDER_INGAME, SUCCESS);
	if (key == KEY_ACT && (gen->disp.render_selec == RENDER_LEAKES
			|| gen->disp.render_selec == RENDER_CRASHES))
		return (gen->disp.render_selec = RENDER_INGAME, 0);
	return (0);
}

//==================
// movements
//==================

/**
 * @brief sets hooks activaed by pressing a key. Goal: move player
 *
 * @param gen
 * @param key
 * @return t_bool
 */
static t_bool	_in_0_hooks_keys_press_move(t_general *gen, int key)
{
	if (key == KEY_RIGHT)
		return (gen->next_walk[GO_RIGHT] = true, SUCCESS);
	if (key == KEY_LEFT)
		return (gen->next_walk[GO_LEFT] = true, SUCCESS);
	if (key == KEY_FORWARD)
		return (gen->next_walk[GO_FORWARD] = true, SUCCESS);
	if (key == KEY_BACK)
		return (gen->next_walk[GO_BACK] = true, SUCCESS);
	if (key == KEY_LOOK_LEFT)
		return (gen->next_turn_key[TURN_L] = true, SUCCESS);
	if (key == KEY_LOOK_RIGHT)
		return (gen->next_turn_key[TURN_R] = true, SUCCESS);
	if (key == KEY_BIG_MAP)
		return (gen->disp.render_selec = RENDER_BIG_MAP, SUCCESS);
	return (FAIL);
}

/**
 * @brief sets hooks activaed by releasing a key. Goal: stop player mouvement
 *
 * @param gen
 * @param key
 * @return t_bool
 */
static int	_in_0_hooks_keys_release_move(t_general *gen, int key)
{
	if (key == KEY_RIGHT)
		return (gen->next_walk[GO_RIGHT] = false, SUCCESS);
	if (key == KEY_LEFT)
		return (gen->next_walk[GO_LEFT] = false, SUCCESS);
	if (key == KEY_FORWARD)
		return (gen->next_walk[GO_FORWARD] = false, SUCCESS);
	if (key == KEY_BACK)
		return (gen->next_walk[GO_BACK] = false, SUCCESS);
	if (key == KEY_LOOK_LEFT)
		return (gen->next_turn_key[TURN_L] = false, SUCCESS);
	if (key == KEY_LOOK_RIGHT)
		return (gen->next_turn_key[TURN_R] = false, SUCCESS);
	return (FAIL);
}

//==================
// Settings
//==================

//protegerrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
static t_bool	_in_0_hooks_keys_press_settings(t_general *gen, int key)
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