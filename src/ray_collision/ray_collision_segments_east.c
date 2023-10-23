/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_segments_east.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:17:29 by acardona          #+#    #+#             */
/*   Updated: 2023/10/23 03:24:01 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

/**
 * @brief ray projection for angles between 0 and M_PI / 4
 * 
 * @param map 
 * @param last 
 * @param rdata 
 * @return t_hitpoint 
 */
t_hitpoint	r_ray_hit_n_ne(t_map *map, t_hitpoint last, t_ray_data rdata)
{
	rdata.prim = PRIMARY_H;
	if (rdata.first == FIRST_V && r_ray_hit_sec(map, &last, &rdata, last.pt_co))
		return (last);
	rdata.last_v.x -= (rdata.first == FIRST_H && rdata.check_v);
	rdata.last_v.y -= rdata.delta_y * (rdata.first == FIRST_H
			&& rdata.check_v);
	last = (t_hitpoint){rdata.last_h, (int)rdata.last_h.x,
		(int)(--rdata.last_h.y) + (rdata.shift != 0.), FACE_S, 0.};
	while (++last.pt_co.y <= map->y_max - 1. - rdata.shift)
	{
		++last.chunk_co_y;
		if (r_ray_hit_primary(map, &last, &rdata))
			return (last);
		last.pt_co.x += rdata.delta_x;
		if (rdata.check_v && last.pt_co.x - rdata.last_v.x >= 1.)
		{
			if (++rdata.last_v.x > map->x_max - 1. - rdata.shift)
				return (last.pt_co.x = -1., last);
			++last.chunk_co_x;
			rdata.last_v.y += rdata.delta_y;
			if (r_ray_hit_sec(map, &last, &rdata, rdata.last_v))
				return (last.hit_face = FACE_W, last);
		}
	}
	return (last.pt_co.x = -1., last);
}

/**
 * @brief ray projection for angles between M_PI / 4 and M_PI / 2
 * 
 * @param map 
 * @param last 
 * @param rdata 
 * @return t_hitpoint 
 */
t_hitpoint	r_ray_hit_ne_e(t_map *map, t_hitpoint last, t_ray_data rdata)
{
	rdata.prim = PRIMARY_V;
	if (rdata.first != FIRST_V && r_ray_hit_sec(map, &last, &rdata, last.pt_co))
		return (last);
	rdata.last_h.x -= rdata.delta_x * (rdata.first == FIRST_V
			&& rdata.check_h);
	rdata.last_h.y -= (rdata.first == FIRST_V && rdata.check_h);
	last = (t_hitpoint){rdata.last_v, (int)(--rdata.last_v.x
			+ (rdata.shift != 0.)), (int)rdata.last_v.y, FACE_W, 0.};
	while (++last.pt_co.x <= map->x_max - 1. - rdata.shift)
	{
		++last.chunk_co_x;
		if (r_ray_hit_primary(map, &last, &rdata))
			return (last);
		last.pt_co.y += rdata.delta_y;
		if (rdata.check_h && last.pt_co.y - rdata.last_h.y >= 1.)
		{
			if (++rdata.last_h.y > map->y_max - 1. - rdata.shift)
				return (last.pt_co.x = -1., last);
			++last.chunk_co_y;
			rdata.last_h.x += rdata.delta_x;
			if (r_ray_hit_sec(map, &last, &rdata, rdata.last_h))
				return (last.hit_face = FACE_S, last);
		}
	}
	return (last.pt_co.x = -1., last);
}

/**
 * @brief ray projection for angles between M_PI / 2 and 3 * M_PI / 4
 * 
 * @param map 
 * @param last 
 * @param rdata 
 * @return t_hitpoint 
 */
t_hitpoint	r_ray_hit_e_se(t_map *map, t_hitpoint last, t_ray_data rdata)
{
	rdata.prim = PRIMARY_V;
	if (rdata.first != FIRST_V && r_ray_hit_sec(map, &last, &rdata, last.pt_co))
		return (last);
	rdata.last_h.x -= rdata.delta_x * (rdata.first == FIRST_V
			&& rdata.check_h);
	rdata.last_h.y += (rdata.first == FIRST_V && rdata.check_h);
	last = (t_hitpoint){rdata.last_v, (int)(--rdata.last_v.x
			+ (rdata.shift != 0)), (int)rdata.last_v.y, FACE_W, 0.};
	while (++last.pt_co.x <= map->x_max - 1. - rdata.shift)
	{
		++last.chunk_co_x;
		if (r_ray_hit_primary(map, &last, &rdata))
			return (last);
		last.pt_co.y += rdata.delta_y;
		if (rdata.check_h && rdata.last_h.y - last.pt_co.y >= 1.)
		{
			if (--rdata.last_h.y < 1. + rdata.shift)
				return (last.pt_co.x = -1., last);
			--last.chunk_co_y;
			rdata.last_h.x += rdata.delta_x;
			if (r_ray_hit_sec(map, &last, &rdata, rdata.last_h))
				return (last.hit_face = FACE_N, last);
		}
	}
	return (last.pt_co.x = -1., last);
}

/**
 * @brief ray projection for angles between 3 * M_PI / 4 and M_PI
 * 
 * @param map 
 * @param last 
 * @param rdata 
 * @return t_hitpoint 
 */
t_hitpoint	r_ray_hit_se_s(t_map *map, t_hitpoint last, t_ray_data rdata)
{
	rdata.prim = PRIMARY_H;
	if (rdata.first != FIRST_H && r_ray_hit_sec(map, &last, &rdata, last.pt_co))
		return (last);
	rdata.last_v.x -= (rdata.first == FIRST_H && rdata.check_v);
	rdata.last_v.y -= rdata.delta_y * (rdata.first == FIRST_H
			&& rdata.check_v);
	last = (t_hitpoint){rdata.last_h, (int)rdata.last_h.x,
		(int)(++rdata.last_h.y) - 1, FACE_N, 0.};//simplifiable en last.pt_co.y++
	while (--last.pt_co.y >= 1. + rdata.shift)
	{
		--last.chunk_co_y;
		if (r_ray_hit_primary(map, &last, &rdata))
			return (last);
		last.pt_co.x += rdata.delta_x;
		if (rdata.check_v && last.pt_co.x - rdata.last_v.x >= 1.)
		{
			if (++rdata.last_v.x > map->x_max - 1 - rdata.shift)
				return (last.pt_co.x = -1., last);
			++last.chunk_co_x;
			rdata.last_v.y += rdata.delta_y;
			if (r_ray_hit_sec(map, &last, &rdata, rdata.last_v))
				return (last.hit_face = FACE_W, last);
		}
	}
	return (last.pt_co.x = -1., last);
}
