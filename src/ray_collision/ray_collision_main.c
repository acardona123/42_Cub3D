/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:14:53 by acardona          #+#    #+#             */
/*   Updated: 2023/10/23 04:10:10 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

static const t_collision_function	g_collision_function[8]
	= {r_ray_hit_n_ne, r_ray_hit_ne_e, r_ray_hit_e_se, r_ray_hit_se_s,
	r_ray_hit_s_sw, r_ray_hit_sw_w, r_ray_hit_w_nw, r_ray_hit_nw_n};

/**
 * @brief sendsd a ray from the player, in a certain direction and returns the
 *	impact point with the first obstacle found.
 *	(if no obstacle found the abscisse of the returned obstacle is set to -1.)
 * 
 * @param p_co player coordinates
 * @param angle_ray absolute angle of the ray (between -2 * M_PI and 4 * M_PI)
 *	rlatively to the north of the map
 * @param map 
 * @return t_hitpoint structure contining the datas oh the first bloc hitten and
 *		the imact point.
 */
t_hitpoint	r_ray_hit(t_coord_f *p_co, float angle_ray, t_map *map,
	bool obstacles_shift)
{
	t_hitpoint	last_hit;
	t_ray_data	rdata;

	while (angle_ray < 0)
		angle_ray += 2 * M_PI;
	while (angle_ray > 2 * M_PI)
		angle_ray -= 2 * M_PI;
	rdata = (t_ray_data){0};
	rdata.dial = (int)(angle_ray * 4 / M_PI);
	rdata.shift = obstacles_shift * DIST_WALL_MIN;
	last_hit = r_ray_init_rdata_hitpoint(p_co, angle_ray, map, &rdata);
	return (g_collision_function[rdata.dial](map, last_hit, rdata));
}

/*
#include "../../includes/cub3d.h"
int	main(int ac, char **av)
{
	t_general	gen;
	t_hitpoint	hitpoint;
	float 		angle_deg;
	

	gen = (t_general){0};
	
	init_main(ac, av, &gen);
	
	printf("player co: (%f, %f)\n", gen.player.p_co.x, gen.player.p_co.y);
	// gen.player.p_co.x = 18.;
	// gen.player.p_co.y = 9.5;
	angle_deg = 0.;
	while (angle_deg < 360.)
	{
		printf("\e[103mangle: %f (%f)\e[0m\n", angle_deg, angle_deg * M_PI / 180);
		hitpoint = r_ray_hit(&gen.player.p_co, angle_deg * M_PI / 180,
				&gen.map, false);
		printf(" last_hit : (%f, %f)\n", hitpoint.pt_co.x, hitpoint.pt_co.y);
		if (hitpoint.chunk_co_x >= 0.)
			printf(" chunk: (%d, %d) -> \'%c\'\n\n", hitpoint.chunk_co_x,
				hitpoint.chunk_co_y,
				gen.map.map[hitpoint.chunk_co_x][hitpoint.chunk_co_y].type);
		else
			printf("\e[33m chunk: no\e[0m\n");
		angle_deg += 5.;
	}
	return (0);
}
*/