/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:35:01 by acardona          #+#    #+#             */
/*   Updated: 2023/10/15 22:22:17 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

int	main(int ac, char **av)
{
	t_general	gen;

	gen = (t_general){0};
	init_main(ac, av, &gen);
	
	// gen.player.p_co.x -= .5;
	// gen.player.p_co.y -= .5;

	// printf("Player : (%f, %f)\n", gen.player.p_co.x, gen.player.p_co.y);
	// t_hitpoint hitpt;
	// float angle = 0.;
	// while (angle <= 360.)
	// {
	// 	printf("\nangle %f:\n", angle);
	// 	hitpt = r_ray_hit(&gen.player.p_co, angle * M_PI / 180, &gen.map);
	// 	printf(" last hit:(%f, %f)->(%d, %d) face %d\n", hitpt.pt_co.x, hitpt.pt_co.y, hitpt.chunk_co.x, hitpt.chunk_co.y, hitpt.hit_face);
	// 	angle += 5.;
	// }
	
	// gen.player.p_angle = 0 * M_PI / 180;
	// r_frame_construction(&gen, to_getime() - 5);
	// mlx_put_image_to_window(gen.disp.mlx, gen.disp.win, gen.disp.buff->img, 0, 0);
	// sleep(3);
	
	mlx_loop_hook(gen.disp.mlx, game_looping, &gen);
	mlx_loop(gen.disp.mlx);
	end_destroy_general(&gen);
	return (0);
}

#else

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
