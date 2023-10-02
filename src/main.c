/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:35:01 by acardona          #+#    #+#             */
/*   Updated: 2023/10/02 20:09:04 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
// /*
int	main(int ac, char **av)
{
	t_general	gen;

	gen = (t_general){0};
	init_main(ac, av, &gen);

	gen.player.p_angle = 0.;
	
	// printf("mapsize : %f, %f\n\n", gen.map.x_max, gen.map.y_max);
	
	if (1)
	{
		int i;
		
		i = 0;
		while (i < 360)
		{
			gen.player.p_angle = (float)i * M_PI / 180;
			printf("\n\e[103mi_radian: %d\e[0m\n", i);
			fflush(stdout);
			r_frame_construction(&gen);
			mlx_put_image_to_window(gen.disp.mlx, gen.disp.win, gen.disp.buff->img, 0, 0);
			// sleep(5);
			i += 90;
		}
		sleep(100);
	}

	end_destroy_general(&gen);
	return (0);
}

// */