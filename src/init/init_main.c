/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:30:16 by acardona          #+#    #+#             */
/*   Updated: 2023/09/30 21:39:46 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"

void	init_main(int ac, char **av, t_general	*gen)
{
	t_lists	init_lists;

	*gen = (t_general){0};
	if (WIN_HIGHT <= 0 || WIN_WIDTH <= 0 || DEFAULT_FOV <= 0
		|| DIST_WALL_MIN <= 0)
	{
		to_error_msg("Settings: defined settings are invalids \
(not strictly positiv)");
		exit(EXIT_INIT_0);
	}
	init_lists = in_1_map_format_check(ac, av, gen);
		// write(1, "===== MAP ====\n", 15);
		// ft_lstprint(init_lists.lst_map);
		// write(1, "\n===== PARAM ====\n", 18);
		// ft_lstprint(init_lists.lst_param);
		// write(1, "\n===== TEXTURES ====\nok\n", 24);
	in_2_init_texture_pack(gen, &init_lists);
	//init de la  map ici;
	to_lstfree(&init_lists.lst_map);
	to_angle_set_init(&gen->fov, DEFAULT_FOV, gen->angles_set);
}
