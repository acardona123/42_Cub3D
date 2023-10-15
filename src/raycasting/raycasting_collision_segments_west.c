/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_collision_segments_west.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:17:29 by acardona          #+#    #+#             */
/*   Updated: 2023/10/15 23:51:14 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

/**
 * @brief ray projection for angles between M_PI and 5 * M_PI / 4
 * 
 * @param map 
 * @param last 
 * @param rdata 
 * @return t_hitpoint 
 */
t_hitpoint	r_ray_hit_s_sw(t_map *map, t_hitpoint last,
	t_ray_data rdata)
{
	if (rdata.first == FIRST_IS_V && r_ray_hit_check_basic(map, &last, &rdata))
		return (last);
	last.pt_co = rdata.last_h;
	last.hit_face = FACE_N;
	rdata.last_v.x += (rdata.first == FIRST_IS_H && rdata.check_v);
	rdata.last_v.y -= rdata.delta_y * (rdata.first == FIRST_IS_H
			&& rdata.check_v);
	last.chunk_co = (t_coord_i){(int)last.pt_co.x, (int)(++last.pt_co.y - 1)};//simplifiable en last.pt_co.y++
	while (--last.pt_co.y >= 1.)
	{
		--last.chunk_co.y;
		if (r_ray_hit_check_basic(map, &last, &rdata))
			return (last);
		last.pt_co.x += rdata.delta_x;
		if (rdata.check_v && ceil(last.pt_co.x) != rdata.last_v.x)
		{
			if (--rdata.last_v.x < 1.)
				return (last.pt_co.x = -1., last);
			--last.chunk_co.x;
			rdata.last_v.y += rdata.delta_y;
			if (r_ray_hit_check_extra_co(map, &last, &rdata, rdata.last_v))
				return (last.hit_face = FACE_E, last);
		}
	}
	return (last.pt_co.x = -1., last);
}

/**
 * @brief ray projection for angles between 5 * M_PI / 4 and 3 * M_PI / 2
 * 
 * @param map 
 * @param last 
 * @param rdata 
 * @return t_hitpoint 
 */
t_hitpoint	r_ray_hit_sw_w(t_map *map, t_hitpoint last,
	t_ray_data rdata)
{
	if (rdata.first == FIRST_IS_H && r_ray_hit_check_basic(map, &last, &rdata))
		return (last);
	last.pt_co = rdata.last_v;
	last.hit_face = FACE_E;
	rdata.last_h.x -= rdata.delta_x * (rdata.first == FIRST_IS_V
			&& rdata.check_h);
	rdata.last_h.y += (rdata.first == FIRST_IS_V && rdata.check_h);
	last.chunk_co = (t_coord_i){(int)(++last.pt_co.x) - 1, (int)last.pt_co.y};//simplifiable
	while (--last.pt_co.x >= 1.)
	{
		--last.chunk_co.x;
		if (r_ray_hit_check_basic(map, &last, &rdata))
			return (last);
		last.pt_co.y += rdata.delta_y;
		if (rdata.check_h && ceil(last.pt_co.y) != rdata.last_h.y)
		{
			if (--rdata.last_h.y < 1.)
				return (last.pt_co.x = -1., last);
			--last.chunk_co.y;
			rdata.last_h.x += rdata.delta_x;
			if (r_ray_hit_check_extra_co(map, &last, &rdata, rdata.last_h))
				return (last.hit_face = FACE_N, last);
		}
	}
	return (last.pt_co.x = -1., last);
}

/**
 * @brief ray projection for angles between 3 * M_PI / 4 and 7 * M_PI / 4
 * 
 * @param map 
 * @param last 
 * @param rdata 
 * @return t_hitpoint 
 */
t_hitpoint	r_ray_hit_w_nw(t_map *map, t_hitpoint last,
	t_ray_data rdata)
{
	if (rdata.first == FIRST_IS_H && r_ray_hit_check_basic(map, &last, &rdata))
		return (last);
	last.pt_co = rdata.last_v;
	last.hit_face = FACE_E;
	rdata.last_h.x -= rdata.delta_x * (rdata.first == FIRST_IS_V
			&& rdata.check_h);
	rdata.last_h.y -= (rdata.first == FIRST_IS_V && rdata.check_h);
	last.chunk_co = (t_coord_i){(int)(++last.pt_co.x) - 1, (int)last.pt_co.y};//simplifiable
	while (--last.pt_co.x >= 1.)
	{
		--last.chunk_co.x;
		if (r_ray_hit_check_basic(map, &last, &rdata))
			return (last);
		last.pt_co.y += rdata.delta_y;
		if (rdata.check_h && floor(last.pt_co.y) != rdata.last_h.y)
		{
			if (++rdata.last_h.y > map->y_max - 1.)
				return (last.pt_co.x = -1., last);
			++last.chunk_co.y;
			rdata.last_h.x += rdata.delta_x;
			if (r_ray_hit_check_extra_co(map, &last, &rdata, rdata.last_h))
				return (last.hit_face = FACE_S, last);
		}
	}
	return (last.pt_co.x = -1., last);
}

/**
 * @brief ray projection for angles between 7 * M_PI / 4 and 2 * M_PI
 * 
 * @param map 
 * @param last 
 * @param rdata 
 * @return t_hitpoint 
 */
t_hitpoint	r_ray_hit_nw_n(t_map *map, t_hitpoint last,
	t_ray_data rdata)
{
	if (rdata.first == FIRST_IS_V && r_ray_hit_check_basic(map, &last, &rdata))
		return (last);
	last.pt_co = rdata.last_h;
	last.hit_face = FACE_S;
	rdata.last_v.x += (rdata.first == FIRST_IS_H && rdata.check_v);
	rdata.last_v.y -= rdata.delta_y * (rdata.first == FIRST_IS_H
			&& rdata.check_v);
	last.chunk_co = (t_coord_i){(int)last.pt_co.x, (int)(--last.pt_co.y)};
	while (++last.pt_co.y <= map->y_max - 1.)
	{
		++last.chunk_co.y;
		if (r_ray_hit_check_basic(map, &last, &rdata))
			return (last);
		last.pt_co.x += rdata.delta_x;
		if (rdata.check_v && ceil(last.pt_co.x) != rdata.last_v.x)
		{
			if (--rdata.last_v.x < 1.)
				return (last.pt_co.x = -1., last);
			--last.chunk_co.x;
			rdata.last_v.y += rdata.delta_y;
			if (r_ray_hit_check_extra_co(map, &last, &rdata, rdata.last_v))
				return (last.hit_face = FACE_E, last);
		}
	}
	return (last.pt_co.x = -1., last);
}
