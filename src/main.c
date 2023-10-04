/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:35:01 by acardona          #+#    #+#             */
/*   Updated: 2023/10/04 23:27:29 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


#ifdef BONUS

int	main(int ac, char **av)
{
	t_general	gen;

	gen = (t_general){0};
	init_main(ac, av, &gen);
	mlx_loop_hook(gen.disp.mlx, game_looping, &gen);
	gen.delays.last_time = to_getime() - DEFAULT_DELAY;
	mlx_loop(gen.disp.mlx);
	end_destroy_general(&gen);
	return (0);
}
#endif

#ifndef BONUS

int	main(int ac, char **av)
{
	t_general	gen;

	gen = (t_general){0};
	init_main(ac, av, &gen);
	mlx_loop_hook(gen.disp.mlx, game_looping, &gen);
	mlx_loop(gen.disp.mlx);
	end_destroy_general(&gen);
	return (0);
}

#endif

// */