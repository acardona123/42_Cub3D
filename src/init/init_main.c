/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:30:16 by acardona          #+#    #+#             */
/*   Updated: 2023/09/26 17:50:39 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"

bool	init_main(int ac, char **av, t_general	*gen)
{
	t_lists	init_lists;

	*gen = (t_general){0};
	init_lists = in_1_map_format_check(ac, av, gen);
	write(1, "===== MAP ====\n", 15);
	ft_lstprint(init_lists.lst_map);
	write(1, "\n===== PARAM ====\n", 18);
	ft_lstprint(init_lists.lst_param);
	printf("\n\nmaps_size:(%d, %d)\n", init_lists.map_max_x, init_lists.map_max_y);
	to_lstfree(&init_lists.lst_param);
	to_lstfree(&init_lists.lst_map);
	// in_0_init_display(gen);
	// in_2_init_texture_pack(ac, av, gen);
	// in_3_map_content_init(ac, av, gen);
	return (true);
}
