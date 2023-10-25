/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_hit_check_door.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:26:25 by acardona          #+#    #+#             */
/*   Updated: 2023/10/26 01:19:42 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

#ifdef BONUS

bool	r_ray_hit_check_doors_prim(t_map *map, t_hitpoint *hitpoint,
	t_ray_data *rdata, t_coord_f real_hitpoint_co)
{
	t_coord_f			hit_mid_shunck;
	float				inf_value;

	if (rdata->prim == PRIMARY_H)
	{
		inf_value = floor(hitpoint->pt_co.x);
		hit_mid_shunck.x = hitpoint->pt_co.x + 0.5 * rdata->delta_x;
		if (hit_mid_shunck.x <= inf_value || hit_mid_shunck.x >= inf_value + 1)
			return (false);
		//to do
	}
	else
	{
		//to do
	}
	return (false);
}

static void	_r_ray_update_door(t_chunk *chunk, size_t time_now)
{
	static size_t	time_last_update = 0;
	static t_chunk	*chunk_last_update = NULL;

	//to do
}

bool	r_ray_hit_check_doors_sec(t_map *map, t_hitpoint *hitpoint,
	t_ray_data *rdata, t_coord_f real_hitpoint_co)
{
	(void)map;
	(void)hitpoint;
	(void)rdata;
	(void)real_hitpoint_co;
	//to do
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
	//to do
	return (false);
}

#endif
