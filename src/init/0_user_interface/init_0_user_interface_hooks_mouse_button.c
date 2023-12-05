/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0_user_interface_hooks_mouse_button.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:29:30 by acardona          #+#    #+#             */
/*   Updated: 2023/12/06 00:42:20 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

static int	_in_0_hooks_mouse_default(t_general *gen);
static void	_in_0_hooks_scroll_up(t_general *gen);
static void	_in_0_hooks_scroll_down(t_general *gen);

int	in_0_hooks_mouse_button_press(int key, int x, int y, t_general *gen)
{
	(void)x;
	(void)y;
	if (key == MOUSE_LEFT_CLICK)
		return (gp_action_main(gen), 0);
	if (!gen->settings.configuring)
		return (0);
	if (key == MOUSE_MIDDLE_CLICK)
		return (_in_0_hooks_mouse_default(gen), 0);
	if (key == MOUSE_SCROLL_DOWN)
		return (_in_0_hooks_scroll_down(gen), 0);
	if (key == MOUSE_SCROLL_UP)
		return (_in_0_hooks_scroll_up(gen), 0);
	return (0);
}

int	in_0_hooks_mouse_button_release(int key, int x, int y, t_general *gen)
{
	(void)x;
	(void)y;
	if (key == MOUSE_LEFT_CLICK
		&& (gen->disp.render_selec == RENDER_LEAKES
			|| gen->disp.render_selec == RENDER_CRASHES))
			gen->disp.render_selec = RENDER_INGAME;
	return (0);
}

static int	_in_0_hooks_mouse_default(t_general *gen)
{
	if (gen->settings.configuring == CONFIG_WALK_SPEED)
		return (gen->settings.walk_speed = DEFAULT_WALK_SPEED, 0);
	if (gen->settings.configuring == CONFIG_MINI_ZOOM)
		return (gen->settings.minimap_zoom
			= ft_max(1, (int)(MINIMAP_ZOOM_DEFAULT
				* gen->settings.minimap_size)), 0);
	if (gen->settings.configuring == CONFIG_MOUSE_ROTATION_SPEED)
		return (gen->settings.mouse_turn_sensibility
			= M_PI / (6 * WIN_WIDTH), 0);
	if (gen->settings.configuring == CONFIG_KEY_ROTATION_SPEED)
		return (gen->settings.key_turn_speed = DEFAULT_ROTATE_SPEED_KEY, 0);
	if (gen->settings.configuring == CONFIG_FOV)
	{
		gen->settings.fov = DEFAULT_FOV;
		to_angle_set_init(&gen->settings.fov, gen->settings.fov,
			gen->angles_set, gen->angle_correc);
		return (0);
	}
	return (0);
}

static void	_in_0_hooks_scroll_down(t_general *gen)
{
	if (gen->settings.configuring == CONFIG_WALK_SPEED
		&& gen->settings.walk_speed - WALK_SPEED_INCREMENT > 0)
		gen->settings.walk_speed -= WALK_SPEED_INCREMENT;
	else if (gen->settings.configuring == CONFIG_MINI_ZOOM
		&& gen->settings.minimap_zoom - MINIMAP_ZOOM_INCREMENT > 0)
		gen->settings.minimap_zoom -= MINIMAP_ZOOM_INCREMENT;
	else if (gen->settings.configuring == CONFIG_MOUSE_ROTATION_SPEED
		&& gen->settings.mouse_turn_sensibility
		- ROTATE_SPEED_MOUSE_INCREMENT > 0)
		gen->settings.mouse_turn_sensibility -= ROTATE_SPEED_MOUSE_INCREMENT;
	else if (gen->settings.configuring == CONFIG_KEY_ROTATION_SPEED
		&& gen->settings.key_turn_speed - ROTATE_SPEED_KEY_INCREMENT > 0)
		gen->settings.key_turn_speed -= ROTATE_SPEED_KEY_INCREMENT;
	else if (gen->settings.configuring == CONFIG_FOV
		&& gen->settings.fov - FOV_INCREMENT > FOV_MIN)
	{
		gen->settings.fov -= FOV_INCREMENT;
		to_angle_set_init(&gen->settings.fov, gen->settings.fov,
			gen->angles_set, gen->angle_correc);
	}
}

static void	_in_0_hooks_scroll_up(t_general *gen)
{
	if (gen->settings.configuring == CONFIG_WALK_SPEED)
		gen->settings.walk_speed += WALK_SPEED_INCREMENT;
	else if (gen->settings.configuring == CONFIG_MINI_ZOOM)
		gen->settings.minimap_zoom += MINIMAP_ZOOM_INCREMENT;
	else if (gen->settings.configuring == CONFIG_MOUSE_ROTATION_SPEED)
		gen->settings.mouse_turn_sensibility += ROTATE_SPEED_MOUSE_INCREMENT;
	else if (gen->settings.configuring == CONFIG_KEY_ROTATION_SPEED)
		gen->settings.key_turn_speed += ROTATE_SPEED_KEY_INCREMENT;
	else if (gen->settings.configuring == CONFIG_FOV
		&& gen->settings.fov + FOV_INCREMENT < FOV_MAX)
	{
		gen->settings.fov += FOV_INCREMENT;
		to_angle_set_init(&gen->settings.fov, gen->settings.fov,
			gen->angles_set, gen->angle_correc);
	}
}

#endif
