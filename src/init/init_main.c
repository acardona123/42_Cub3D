/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:30:16 by acardona          #+#    #+#             */
/*   Updated: 2023/11/02 22:04:33 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"

static void	_init_settings_angleset(t_general *gen);

void	init_main(int ac, char **av, t_general	*gen)
{
	t_lists	init_lists;

	*gen = (t_general){0};
	if (WIN_HEIGHT <= 0 || WIN_WIDTH <= 0 || DEFAULT_FOV <= 0
		|| DIST_WALL_MIN <= 0)
	{
		to_error_msg("Settings: defined settings are invalid \
(not strictly positive)");
		exit(EXIT_INIT_0);
	}
	srand((unsigned int)to_getime());
	in_0_init_display(gen);
	init_lists = in_1_map_format_check(ac, av, gen);
	in_2_init_texture_pack(gen, &init_lists);
	in_3_mapcontent_init(gen, &init_lists);
	_init_settings_angleset(gen);
}

static void	_init_settings_angleset(t_general *gen)
{
	gen->settings = (t_settings){DEFAULT_WALK_SPEED, DEFAULT_ROTATE_SPEED_KEY,
		DEFAULT_ROTATE_SPEED_MOUSE, DEFAULT_FOV};
	to_angle_set_init(&gen->settings.fov, DEFAULT_FOV, gen->angles_set,
		gen->angle_correc);
}
