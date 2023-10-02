/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:30:16 by acardona          #+#    #+#             */
/*   Updated: 2023/10/02 02:18:52 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"

void	init_main(int ac, char **av, t_general	*gen)
{
	t_lists	init_lists;

	printf("Initialisation start.\n");
	*gen = (t_general){0};
	if (WIN_HEIGHT <= 0 || WIN_WIDTH <= 0 || DEFAULT_FOV <= 0
		|| DIST_WALL_MIN <= 0)
	{
		to_error_msg("Settings: defined settings are invalids \
(not strictly positiv)");
		exit(EXIT_INIT_0);
	}
	in_0_init_display(gen);
	init_lists = in_1_map_format_check(ac, av, gen);
	in_2_init_texture_pack(gen, &init_lists);
	in_3_map_content_init(gen, &init_lists);
	to_angle_set_init(&gen->fov, DEFAULT_FOV, gen->angles_set);
	printf("Initialisation done.\n");
}
