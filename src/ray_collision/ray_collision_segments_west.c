/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_segments_west.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:17:29 by acardona          #+#    #+#             */
/*   Updated: 2023/11/03 02:32:45 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

/**
 * @brief ray projection for angles between M_PI and 5 * M_PI / 4
 * 
 * @param map 
 * @param last 
 * @param rdata 
 * @return t_hitpoint 
 */
t_hitpoint	r_ray_hit_s_sw(t_general *gen, t_hitpoint last,
	t_ray_data rdata)
{
							//printf("  first: %c\n", "HVA"[rdata.first]);//
							//printf("- before: last: (%f, %f)\n", last.pt_co.x, last.pt_co.y);//
							//printf("  before: chunk_co: (%d, %d)\n", last.chunk_co_x, last.chunk_co_y);//;
	if (rdata.first == FIRST_V && r_ray_hit_sec(gen, &last, &rdata, last.pt_co))
		return (last.pt_co.x += EPSILON, last);
							//printf("- begin last: (%f, %f)\n", last.pt_co.x, last.pt_co.y);//
							//printf("  begin chunk_co: (%d, %d)\n", last.chunk_co_x, last.chunk_co_y);//
	rdata.last_v.x += (rdata.first == FIRST_H && rdata.check_v);
	rdata.last_v.y -= rdata.delta_y * (rdata.first == FIRST_H
			&& rdata.check_v);
	last = (t_hitpoint){(t_coord_f){rdata.last_h.x, rdata.last_h.y + 1}, last
		.chunk_co_x, ++last.chunk_co_y - (rdata.first == FIRST_V), FACE_N, 0.};
	while (--last.pt_co.y >= 1. + rdata.shift)
	{
		--last.chunk_co_y;
								//printf("- last: (%f, %f)\n", last.pt_co.x, last.pt_co.y);//
								//printf("  chunk_co: (%d, %d)\n", last.chunk_co_x, last.chunk_co_y);//
		if (r_ray_hit_primary(gen, &last, &rdata))
			return (last.pt_co.y += EPSILON, last);
		last.pt_co.x += rdata.delta_x;
		if (rdata.check_v && rdata.last_v.x - last.pt_co.x >= 1.)
		{
			if (--rdata.last_v.x < 1. + rdata.shift)
				return (last.pt_co.x = -1., last);
			--last.chunk_co_x;
			rdata.last_v.y += rdata.delta_y;
			if (r_ray_hit_sec(gen, &last, &rdata, rdata.last_v))
				return (last.pt_co.x += EPSILON, last.hit_face = FACE_E, last);
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
t_hitpoint	r_ray_hit_sw_w(t_general *gen, t_hitpoint last,
	t_ray_data rdata)
{
							//printf("  first: %c\n", "HVA"[rdata.first]);//
							//printf("- before: last: (%f, %f)\n", last.pt_co.x, last.pt_co.y);//
							//printf("  before: chunk_co: (%d, %d)\n", last.chunk_co_x, last.chunk_co_y);//
	if (rdata.first == FIRST_H && r_ray_hit_sec(gen, &last, &rdata, last.pt_co))
		return (last.pt_co.y += EPSILON, last);
							//printf("- begin last: (%f, %f)\n", last.pt_co.x, last.pt_co.y);//
							//printf("  begin chunk_co: (%d, %d)\n", last.chunk_co_x, last.chunk_co_y);//
	rdata.last_h.x -= rdata.delta_x * (rdata.first == FIRST_V
			&& rdata.check_h);
	rdata.last_h.y += (rdata.first == FIRST_V && rdata.check_h);
	last = (t_hitpoint){(t_coord_f){rdata.last_v.x + 1, rdata.last_v.y}, ++last
		.chunk_co_x - (rdata.first == FIRST_H), last.chunk_co_y, FACE_E, 0.};
	while (--last.pt_co.x >= 1. + rdata.shift)
	{
		--last.chunk_co_x;
								//printf("- last: (%f, %f)\n", last.pt_co.x, last.pt_co.y);//
								//printf("  chunk_co: (%d, %d)\n", last.chunk_co_x, last.chunk_co_y);//
		if (r_ray_hit_primary(gen, &last, &rdata))
			return (last.pt_co.x += EPSILON, last);
		last.pt_co.y += rdata.delta_y;
		if (rdata.check_h && rdata.last_h.y - last.pt_co.y >= 1.)
		{
			if (--rdata.last_h.y < 1. + rdata.shift)
				return (last.pt_co.x = -1., last);
			--last.chunk_co_y;
			rdata.last_h.x += rdata.delta_x;
			if (r_ray_hit_sec(gen, &last, &rdata, rdata.last_h))
				return (last.pt_co.y += EPSILON, last.hit_face = FACE_N, last);
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
t_hitpoint	r_ray_hit_w_nw(t_general *gen, t_hitpoint last,
	t_ray_data rdata)
{
							//printf("  first: %c\n", "HVA"[rdata.first]);//
							//printf("- before: last: (%f, %f)\n", last.pt_co.x, last.pt_co.y);//
							//printf("  before: chunk_co: (%d, %d)\n", last.chunk_co_x, last.chunk_co_y);//
	if (rdata.first == FIRST_H && r_ray_hit_sec(gen, &last, &rdata, last.pt_co))
		return (last.pt_co.y -= EPSILON, last);
							//printf("- begin last: (%f, %f)\n", last.pt_co.x, last.pt_co.y);//
							//printf("  begin chunk_co: (%d, %d)\n", last.chunk_co_x, last.chunk_co_y);//
	rdata.last_h.x -= rdata.delta_x * (rdata.first == FIRST_V
			&& rdata.check_h);
	rdata.last_h.y -= (rdata.first == FIRST_V && rdata.check_h);
	last = (t_hitpoint){(t_coord_f){rdata.last_v.x + 1, rdata.last_v.y}, ++last
		.chunk_co_x - (rdata.first == FIRST_H), last.chunk_co_y, FACE_E, 0.};
	while (--last.pt_co.x >= 1. + rdata.shift)
	{
		--last.chunk_co_x;
								//printf("- last: (%f, %f)\n", last.pt_co.x, last.pt_co.y);//
								//printf("  chunk_co: (%d, %d)\n", last.chunk_co_x, last.chunk_co_y);//
		if (r_ray_hit_primary(gen, &last, &rdata))
			return (last.pt_co.x += EPSILON, last);
		last.pt_co.y += rdata.delta_y;
		if (rdata.check_h && last.pt_co.y - rdata.last_h.y >= 1.)
		{
			if (++rdata.last_h.y > gen->map.y_max - 1. - rdata.shift)
				return (last.pt_co.x = -1., last);
			++last.chunk_co_y;
			rdata.last_h.x += rdata.delta_x;
			if (r_ray_hit_sec(gen, &last, &rdata, rdata.last_h))
				return (last.pt_co.y -= EPSILON, last.hit_face = FACE_S, last);
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
t_hitpoint	r_ray_hit_nw_n(t_general *gen, t_hitpoint last,
	t_ray_data rdata)
{
							//printf("  first: %c\n", "HVA"[rdata.first]);//
							//printf("- before: last: (%f, %f)\n", last.pt_co.x, last.pt_co.y);//
							//printf("  before: chunk_co: (%d, %d)\n", last.chunk_co_x, last.chunk_co_y);//;
	if (rdata.first == FIRST_V && r_ray_hit_sec(gen, &last, &rdata, last.pt_co))
		return (last.pt_co.x += EPSILON, last);
							//printf("- begin last: (%f, %f)\n", last.pt_co.x, last.pt_co.y);//
							//printf("  begin chunk_co: (%d, %d)\n", last.chunk_co_x, last.chunk_co_y);//
	rdata.last_v.x += (rdata.first == FIRST_H && rdata.check_v);
	rdata.last_v.y -= rdata.delta_y * (rdata.first == FIRST_H
			&& rdata.check_v);
	last = (t_hitpoint){(t_coord_f){rdata.last_h.x, rdata.last_h.y - 1}, last
		.chunk_co_x, --last.chunk_co_y + (rdata.first == FIRST_V), FACE_S, 0.};
	while (++last.pt_co.y <= gen->map.y_max - 1. - rdata.shift)
	{
		++last.chunk_co_y;
								//printf("- last: (%f, %f)\n", last.pt_co.x, last.pt_co.y);//
								//printf("  chunk_co: (%d, %d)\n", last.chunk_co_x, last.chunk_co_y);//
		if (r_ray_hit_primary(gen, &last, &rdata))
			return (last.pt_co.y -= EPSILON, last);
		last.pt_co.x += rdata.delta_x;
		if (rdata.check_v && rdata.last_v.x - last.pt_co.x >= 1.)
		{
			if (--rdata.last_v.x < 1. + rdata.shift)
				return (last.pt_co.x = -1., last);
			--last.chunk_co_x;
			rdata.last_v.y += rdata.delta_y;
			if (r_ray_hit_sec(gen, &last, &rdata, rdata.last_v))
				return (last.pt_co.x += EPSILON, last.hit_face = FACE_E, last);
		}
	}
	return (last.pt_co.x = -1., last);
}
