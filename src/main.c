/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:35:01 by acardona          #+#    #+#             */
/*   Updated: 2023/10/04 15:13:42 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
// /*
int	main(int ac, char **av)
{
	t_general	gen;

	gen = (t_general){0};
	init_main(ac, av, &gen);
	gen.player.p_angle = 0;
	gen.player.p_speed = 0.001;
	if (1)
	{
				
		int i;

		gen.player.p_co.y -= 4.;
		i = 0;
		while (i <120)
		{
			printf("i: %d : (x, y) = (%f, %f); angle = %fdeg\n", i, gen.player.p_co.x, gen.player.p_co.y, gen.player.p_angle * 180 / M_PI);
			game_move_player(&gen.player, &gen.map, (t_vector_f){0, 1.}, 50);
			r_frame_construction(&gen, to_getime());
			mlx_put_image_to_window(gen.disp.mlx, gen.disp.win, gen.disp.buff->img, 0, 0);
			usleep(50000);
			i += 1;
		}
		while (i > 100)
		{
			printf("i: %d : (x, y) = (%f, %f); angle = %fdeg\n", i, gen.player.p_co.x, gen.player.p_co.y, gen.player.p_angle * 180 / M_PI);
			game_turn_head(&gen.player.p_angle, 50, TURN_L);
			r_frame_construction(&gen, to_getime());
			mlx_put_image_to_window(gen.disp.mlx, gen.disp.win, gen.disp.buff->img, 0, 0);
			usleep(50000);
			--i;
		}
		while (i > -500)
		{
			printf("i: %d : (x, y) = (%f, %f); angle = %fdeg\n", i, gen.player.p_co.x, gen.player.p_co.y, gen.player.p_angle * 180 / M_PI);
			game_move_player(&gen.player, &gen.map, (t_vector_f){0, -1.}, 50);
			r_frame_construction(&gen, to_getime());
			mlx_put_image_to_window(gen.disp.mlx, gen.disp.win, gen.disp.buff->img, 0, 0);
			usleep(50000);
			i -= 1;
		}

		// sleep(1);
	}

	end_destroy_general(&gen);
	return (0);
}

// */