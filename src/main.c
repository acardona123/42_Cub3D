/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:35:01 by acardona          #+#    #+#             */
/*   Updated: 2023/11/21 13:52:19 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_general	gen;

	gen = (t_general){0};
	init_main(ac, av, &gen);
	// gen.player.p_co.x = 6.837041;
	// gen.player.p_co.y = 4.544216;
	// gen.player.p_angle = 4.454997;
	mlx_loop_hook(gen.disp.mlx, gp_looping, &gen);
	mlx_loop(gen.disp.mlx);
	end_destroy_general(&gen);
	return (0);
}
