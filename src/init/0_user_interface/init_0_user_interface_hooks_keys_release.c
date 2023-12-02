/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0_user_interface_hooks_keys_release.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 20:01:14 by alexandm          #+#    #+#             */
/*   Updated: 2023/12/02 20:07:21 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static int		_in_0_hooks_keys_release_move(t_general *gen, int key);

#ifdef BONUS

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
	if (key == KEY_WALK_SPEED || key == KEY_ROT_SPEED_KEY
		|| key == KEY_ROT_SPEED_MOUSE || key == KEY_MINI_ZOOM)
		return (gen->settings.configuring = 0, SUCCESS);
	if (key == KEY_HELP && gen->disp.img_select == RENDER_HELP)
		return (gen->disp.img_select = INGAME, SUCCESS);
	return (0);
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
	if (key == KEY_BIG_MAP && gen->disp.img_select == BIG_MAP)
		return (gen->disp.img_select = INGAME, SUCCESS);
	if (key == KEY_SPRINT)
		return (gen->sprint = false, gen->settings.walk_speed /= 1.5, SUCCESS);
	return (FAIL);
}

#else

/**
 * @brief initializes all hooks associated to keybord keys release
 *
 * @param key
 * @param gen
 * @return int 0 anyway
 */
int	in_0_hooks_keys_release(int key, t_general *gen)
{
	_in_0_hooks_keys_release_move(gen, key);
	return (0);
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

#endif