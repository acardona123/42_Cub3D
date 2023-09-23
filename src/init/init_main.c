/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:30:16 by acardona          #+#    #+#             */
/*   Updated: 2023/09/23 02:38:01 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"

bool	init_main(int ac, char **av, t_general	*gen)
{
	*gen = (t_general){0};
	in_0_map_format_check(ac, av, gen);
	in_1_init_display(gen);
	in_2_init_texture_pack(ac, av, gen);
	in_3_map_content_init(ac, av, gen);
	return (true);
}
