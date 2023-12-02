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
	return (FAIL);
}

//==================
// Settings
//==================

static t_bool	_in_0_hooks_keys_press_settings(t_general *gen, int key)
{
	if (key == KEY_WALK_SPEED)
		return (gen->settings.configuring = CONFIG_WALK_SPEED);
	if (key == KEY_MINI_ZOOM)
		return (gen->settings.configuring = CONFIG_MINI_ZOOM);
	if (key == KEY_ROT_SPEED_MOUSE)
		return (gen->settings.configuring = CONFIG_MOUSE_ROTATION_SPEED,
			SUCCESS);
	if (key == KEY_ROT_SPEED_KEY)
		return (gen->settings.configuring = CONFIG_KEY_ROTATION_SPEED,
			SUCCESS);
	if (key == KEY_FOV)
		return (gen->settings.configuring = CONFIG_FOV, SUCCESS);
	if (key == KEY_HELP && WIN_WIDTH > HELP_MSG_WIDTH
		&& WIN_HEIGHT > HELP_MSG_HEIGHT)
		return (gen->disp.img_select = RENDER_HELP,
			in_0_settings_help_msg(gen), SUCCESS);
	if (key == KEY_BIG_MAP)
		return (gen->disp.img_select = BIG_MAP, SUCCESS);
	return (FAIL);
}
