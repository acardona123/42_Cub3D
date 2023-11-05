/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_hit_check_door.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:26:25 by acardona          #+#    #+#             */
/*   Updated: 2023/11/05 00:49:58 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray_collision.h"

#ifdef BONUS

static bool		_r_ray_hit_check_doors_h(t_chunk *door, t_hitpoint *hit_pt,
					t_coord_f real_hitpoint_co, t_ray_data *rdata);
static bool		_r_ray_hit_check_doors_v(t_chunk *door, t_hitpoint *hit_pt,
					t_coord_f real_hitpoint_co, t_ray_data *rdata);

/**
 * @brief checks if the ray that touched a door chunk on its primary axis really
 *	hit the door panel.
 * 
 * @param map 
 * @param hit_pt points toward the hitpoint with the door chunk border, is
 *		updated if the door is hit.
 * @param real_hitpoint_co real coordinates of the hitpoint with the chunk
 * @param rdata 
 * @return true if the door panel is hit, the the hitpoint is updated to this
 *		impact point and the door chunk extra data is updated to the position of
 *		the impact relativly to the door texture (between 0 and 1).
 * @return false if the ray doesn't hit the door panel, hitpoint untouched.
 */
bool	r_ray_hit_check_doors_prim(t_map *map, t_ray_data *rdata,
	t_hitpoint *hit_point, t_coord_f real_hitpoint_co)
{
	doors_update_status(&map->map[hit_point->chunk_co_x][hit_point->chunk_co_y],
		rdata->time_now);
	if (map->map[hit_point->chunk_co_x]
		[hit_point->chunk_co_y].status == DOOR_OPEN)
		return (false);
	if (rdata->shift)//ie the ray is used to check movement obstacle an not visual ones
		return (hit_point->pt_co = real_hitpoint_co, true);
	if (rdata->prim == PRIMARY_H)
		return (_r_ray_hit_check_doors_h(&map->map[hit_point->chunk_co_x]
				[hit_point->chunk_co_y], hit_point, real_hitpoint_co, rdata));
	return (_r_ray_hit_check_doors_v(&map->map[hit_point->chunk_co_x]
			[hit_point->chunk_co_y], hit_point, real_hitpoint_co, rdata));
}

/**
 * @brief checks if the ray that touched a door chunk on its secondary axis
 *	really hit the door panel.
 * 
 * @param map 
 * @param hit_pt points toward the hitpoint with the door chunk border, is
 *		updated if the door is hit.
 * @param real_hitpoint_co real coordinates of the hitpoint with the chunk
 * @param rdata 
 * @return true if the door panel is hit, the the hitpoint is updated to this
 *		impact point and the door chunk extra data is updated to the position of
 *		the impact relativly to the door texture (between 0 and 1).
 * @return false if the ray doesn't hit the door panel, hitpoint untouched.
 */
bool	r_ray_hit_check_doors_sec(t_map *map, t_ray_data *rdata,
	t_hitpoint *hit_point, t_coord_f real_hitpoint_co)
{
	doors_update_status(&map->map[hit_point->chunk_co_x][hit_point->chunk_co_y],
		rdata->time_now);
	if (map->map[hit_point->chunk_co_x]
		[hit_point->chunk_co_y].status == DOOR_OPEN)
		return (false);
	if (rdata->shift)//ie the ray is used to check movement obstacle an not visual ones
		return (hit_point->pt_co = real_hitpoint_co, true);
	if (rdata->prim == PRIMARY_H)
		return (_r_ray_hit_check_doors_v(&map->map[hit_point->chunk_co_x]
				[hit_point->chunk_co_y], hit_point, real_hitpoint_co, rdata));
	return (_r_ray_hit_check_doors_h(&map->map[hit_point->chunk_co_x]
			[hit_point->chunk_co_y], hit_point, real_hitpoint_co, rdata));
}

/**
 * @brief Same as _r_ray_hit_check_doors_v but for horizontal doors:
 *		checks if the ray hits the horizontal door which chunk it crosses.
 *		note: in this version the door is a one chunk large gliding panel,
 *		without any width, positioned at the middle of the chunk 
 * 
 * @param door chunk of the door
 * @param hit_pt points toward the hitpoint with the door chunk border, is
 *		updated if the door is hit.
 * @param real_hitpoint_co real coordinates of the hitpoint with the chunk
 * @param rdata 
 * @return true if the ray hit the door, in this case the hitpoint is updated 
 *		to this impact point and the door extra data is updated to the position
 *		of the impact relativly to the door texture (between 0 and 1).
 * @return false 
 */
static bool	_r_ray_hit_check_doors_h(t_chunk *door, t_hitpoint *hit_pt,
	t_coord_f real_hitpoint_co, t_ray_data *rdata)
{
	float	hit_door_x;
	float	inf_value;

	inf_value = floor(real_hitpoint_co.x);
	hit_door_x = real_hitpoint_co.x + 0.5 * rdata->delta_x;
	if (hit_door_x < inf_value + door->extra_data_f
		|| hit_door_x > inf_value + 1.)
		return (false);
	door->extra_data_f = hit_door_x - inf_value - door->extra_data_f;
	hit_pt->pt_co.x = hit_door_x;
	hit_pt->pt_co.y = real_hitpoint_co.y
		+ 0.5 * (1. - 2. * (rdata->dial >= E_SE && rdata->dial <= SW_W));
	return (true);
}

/**
 * @brief Same as _r_ray_hit_check_doors_h but for vertical doors:
 *		checks if the ray hits the vertical door which chunk it crosses.
 *		note: in this version the door is a one chunk large gliding panel,
 *		without any width, positioned at the middle of the chunk 
 * 
 * @param door chunk of the door
 * @param hit_pt points toward the hitpoint with the door chunk border, is
 *		updated if the door is hit.
 * @param real_hitpoint_co real coordinates of the hitpoint with the chunk
 * @param rdata 
 * @return true if the ray hit the door, in this case the hitpoint is updated 
 *		to this impact point and the door extra data is updated to the position
 *		of the impact relativly to the door texture (between 0 and 1).
 * @return false 
 */
static bool	_r_ray_hit_check_doors_v(t_chunk *door, t_hitpoint *hit_pt,
	t_coord_f real_hitpoint_co, t_ray_data *rdata)
{
	float	hit_door_y;
	float	inf_value;

	inf_value = floor(real_hitpoint_co.y);
	hit_door_y = real_hitpoint_co.y + 0.5 * rdata->delta_y;
	if (hit_door_y < inf_value + door->extra_data_f
		|| hit_door_y > inf_value + 1.)
		return (false);
	door->extra_data_f = hit_door_y - inf_value - door->extra_data_f;
	hit_pt->pt_co.x = real_hitpoint_co.x
		+ 0.5 * (1. - 2. * (rdata->dial >= S_SW));
	hit_pt->pt_co.y = hit_door_y;
	return (true);
}

#else

bool	r_ray_hit_check_doors(t_map *map, t_hitpoint *hitpoint,
	t_ray_data *rdata, t_coord_f real_hitpoint_co)
{
	(void)map;
	(void)hitpoint;
	(void)rdata;
	(void)real_hitpoint_co;
	return (hitpoint->pt_co = real_hitpoint_co, true);
}

#endif

/*
//tests 

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	printf("Tests have to be done on hit_check_door and doors_update\n");
	return (0);
}
*/