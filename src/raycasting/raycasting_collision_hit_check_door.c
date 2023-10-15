/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_collision_hit_check_door.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:26:25 by acardona          #+#    #+#             */
/*   Updated: 2023/10/15 22:03:25 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

#ifdef BONUS

static const t_collision_function	g_collision_function[8]
	= {r_ray_hit_n_ne, r_ray_hit_ne_e, r_ray_hit_e_se, r_ray_hit_se_s,
	r_ray_hit_s_sw, r_ray_hit_sw_w, r_ray_hit_w_nw, r_ray_hit_nw_n};

bool	r_ray_hit_check_doors(t_map *map, t_hitpoint *hitpoint,
	t_ray_data *rdata, t_coord_f real_hitpoint_co)
{
	//todo
	(void)map;
	(void)hitpoint;
	(void)rdata;
	(void)real_hitpoint_co;
	(void)g_collision_function;
	return (false);
}

#else

bool	r_ray_hit_check_doors(t_map *map, t_hitpoint *hitpoint,
	t_ray_data *rdata, t_coord_f real_hitpoint_co)
{
	(void)map;
	(void)hitpoint;
	(void)rdata;
	(void)real_hitpoint_co;
	(void)g_collision_function;
	return (false);
}

#endif
