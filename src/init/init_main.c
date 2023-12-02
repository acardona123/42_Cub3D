/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:30:16 by acardona          #+#    #+#             */
/*   Updated: 2023/12/02 19:46:01 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"

static void	_init_settings(t_general *gen);
static bool	_init_check_settings_define_ok(void);

#ifdef BONUS

static void	_init_settings_bonus(t_general *gen);

void	init_main(int ac, char **av, t_general	*gen)
{
	t_lists	init_lists;

	srand((unsigned int)to_getime());
	*gen = (t_general){0};
	_init_settings(gen);
	_init_settings_bonus(gen);
	in_0_init_display(gen);
	init_lists = in_1_map_format_check(ac, av, gen);
	in_2_init_texture_pack(gen, &init_lists);
	in_3_mapcontent_init(gen, &init_lists);
	in_4_minimap_init(gen);
}

#else

void	init_main(int ac, char **av, t_general	*gen)
{
	t_lists	init_lists;

	srand(0);
	*gen = (t_general){0};
	_init_settings(gen);
	in_0_init_display(gen);
	init_lists = in_1_map_format_check(ac, av, gen);
	in_2_init_texture_pack(gen, &init_lists);
	in_3_mapcontent_init(gen, &init_lists);
}

#endif

static void	_init_settings(t_general *gen)
{
	_init_check_settings_define_ok();
	gen->settings.walk_speed = DEFAULT_WALK_SPEED;
	gen->settings.key_turn_speed = DEFAULT_ROTATE_SPEED_KEY;
	gen->settings.fov = DEFAULT_FOV;
	to_angle_set_init(&gen->settings.fov, DEFAULT_FOV, gen->angles_set,
		gen->angle_correc);
}

static bool	_init_check_settings_define_ok(void)
{
	if (DEFAULT_WALK_SPEED < 0)
		return (to_error_msg(MSG_SETTINGS_WALK_SPEED), false);
	if (FOV_MIN > FOV_MAX)
		return (to_error_msg(MSG_SETTINGS_FOV_RANGE), false);
	if (DIST_WALL_MIN < 0 || DIST_WALL_MIN > 0.25)
		return (to_error_msg(MSG_SETTINGS_DIST_WALL_MIN), false);
	if (DEFAULT_ROTATE_SPEED_KEY < 0)
		return (to_error_msg(MSG_SETTINGS_ROTATE_SPEED), false);
	return (true);
}

#ifdef BONUS

static void	_init_settings_bonus(t_general *gen)
{
	gen->settings.mouse_turn_sensibility = M_PI / (2 * WIN_WIDTH);
	gen->settings.minimap_size
		= (int)(MINIMAP_SIZE_DEFAULT * ft_min(WIN_HEIGHT, WIN_WIDTH));
	gen->settings.minimap_zoom = ft_max(1, (int)(MINIMAP_ZOOM_DEFAULT
				* gen->settings.minimap_size));
	gen->settings.minimap_player_size = (int)(MINIMAP_PLAYER_SIZE_DEFAULT
			* gen->settings.minimap_size);
	gen->settings.bigmap_size = ft_min(WIN_HEIGHT, WIN_WIDTH);
	gen->settings.bigmap_player_size = BIGMAP_PLAYER_SIZE_DEFAULT
		* gen->settings.bigmap_size;
}

#endif