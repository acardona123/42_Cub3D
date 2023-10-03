/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:35:01 by acardona          #+#    #+#             */
/*   Updated: 2023/10/03 19:16:22 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
// /*
int	main(int ac, char **av)
{
	t_general	gen;

	gen = (t_general){0};
	init_main(ac, av, &gen);

	if (1)
	{
		int i;
		
		i = 0;
		while (i < 360)
		{
			gen.player.p_angle = (float)i * M_PI / 180;
			// printf("\n\e[103mi_radian: %d\e[0m\n", i);
			// fflush(stdout);
			r_frame_construction(&gen, to_getime());
			mlx_put_image_to_window(gen.disp.mlx, gen.disp.win, gen.disp.buff->img, 0, 0);
			usleep(50000);
			i += 1;
		}

		sleep(5);
	}

	end_destroy_general(&gen);
	return (0);
}

// */