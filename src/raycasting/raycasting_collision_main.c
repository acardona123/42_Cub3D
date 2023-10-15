/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_collision_main.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:14:53 by acardona          #+#    #+#             */
/*   Updated: 2023/10/15 23:47:39 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

static const t_collision_function	g_collision_function[8]
	= {r_ray_hit_n_ne, r_ray_hit_ne_e, r_ray_hit_e_se, r_ray_hit_se_s,
	r_ray_hit_s_sw, r_ray_hit_sw_w, r_ray_hit_w_nw, r_ray_hit_nw_n};

/**
 * @brief sendsd a aray from the player, in a certain direction and returns the
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
t_hitpoint	r_ray_hit(t_coord_f *p_co, float angle_ray, t_map *map)
{
	t_hitpoint	last_hit;
	t_ray_data	rdata;

	if (angle_ray < 0)
		angle_ray += 2 * M_PI;
	else if (angle_ray > 2 * M_PI)
		angle_ray -= 2 * M_PI;
	last_hit = r_ray_init_rdata_hitpoint(p_co, angle_ray, map, &rdata);
	return (g_collision_function[rdata.dial](map, last_hit, rdata));
}

/*
int	main(int ac, char **av)
{
	
	t_chunk	*y9 = "1111111111";
	t_chunk	*y8 = "1000000001";
	t_chunk	*y7 = "1000000001";
	t_chunk	*y6 = "1001000101";
	t_chunk	*y5 = "1000000001";
	t_chunk	*y4 = "1000000001";
	t_chunk	*y3 = "1000000001";
	t_chunk	*y2 = "1001000101";
	t_chunk	*y1 = "1000000001";
	t_chunk	*y0 = "1111111111";
	t_chunk	*map[10] = {y0, y1, y2, y3, y4, y5, y6, y7, y8, y9};

	t_chunk *map_transposee[10];
	int	i = -1;
	while ( ++i < 10)
	{
		map_transposee[i] = malloc(10 * sizeof(t_chunk));
		for(int j = 0; j < 10; j++)
		{
			map_transposee[i][j].type = map[j][i].type;
		}
	}

	t_map	data = {10, 10, 10, 10, (t_chunk **)map_transposee};
	t_coord_f	co_p = {atof(av[1]), atof(av[2])};
	
	float		angle_ray = 0;
	t_hitpoint	hitpoint;
	while(angle_ray < 360)
	{
		printf("\nangle %.0f: ", angle_ray);
		hitpoint = r_ray_hit(WALL, co_p, angle_ray * M_PI / 180, &data);
		printf("point d'impact ");
		to_vector_print(hitpoint.pt_co);
		printf("chunck coordonne [%d][%d] hit_face %d\n", hitpoint.chunk_co.x,
			hitpoint.chunk_co.y, hitpoint.hit_face);
		angle_ray += 10;
	}

	while (--i >= 0)
		free(map_transposee[i]);
	
	return (0);
}
*/