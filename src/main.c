/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:35:01 by acardona          #+#    #+#             */
/*   Updated: 2023/10/04 00:45:14 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
// /*
int	main(int ac, char **av)
{
	t_general	gen;

	gen = (t_general){0};
	init_main(ac, av, &gen);
	gen.player.p_angle = 2;
	if (1)
	{
		int i;

		i = 0;
		while (i <50)
		{
			// game_turn_head(&gen.player.p_angle, 50, TURN_L);
			game_move_player(&gen.player, &gen.map, (t_vector_f){1., 0});
			r_frame_construction(&gen, to_getime());
			mlx_put_image_to_window(gen.disp.mlx, gen.disp.win, gen.disp.buff->img, 0, 0);
			usleep(50000);
			i += 1;
		}

		sleep(1);
	}

	end_destroy_general(&gen);
	return (0);
}

// */