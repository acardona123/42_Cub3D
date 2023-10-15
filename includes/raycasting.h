/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:05:10 by acardona          #+#    #+#             */
/*   Updated: 2023/10/15 22:45:13 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "shared.h"

typedef enum e_1st_type
{
	FIRST_IS_H,
	FIRST_IS_V,
	FIRST_IS_ANY
}	t_1st_type;

typedef enum e_dial
{
	N_NE,
	NE_E,
	E_SE,
	SE_S,
	S_SW,
	SW_W,
	W_NW,
	NW_N
}	t_dial;

typedef struct s_ray_data
{
	t_dial		dial;
	t_1st_type	first;
	bool		check_h;
	t_coord_f	last_h;
	float		delta_x;
	bool		check_v;
	t_coord_f	last_v;
	float		delta_y;
}	t_ray_data;

typedef t_hitpoint	(*t_collision_function)(t_map*, t_hitpoint, t_ray_data);

//raycasting_frame_build.c
void		*r_frame_construction(t_general *gen, size_t last_time);

//raycasting_collision.c
t_hitpoint	r_ray_hit(t_coord_f *p_co, float angle_ray, t_map *map);

//raycasting_collision_init.c
t_hitpoint	r_ray_init_rdata_hitpoint(t_coord_f *p_co, float angle_ray,
				t_map *map, t_ray_data *rdata);
t_1st_type	r_ray_init_hitpoint(t_coord_f *p_co, t_ray_data *rdata,
				t_hitpoint *hitpoint);

//raycasting_collision_segment_right.c
t_hitpoint	r_ray_hit_n_ne(t_map *map, t_hitpoint last,
				t_ray_data rdata);
t_hitpoint	r_ray_hit_ne_e(t_map *map, t_hitpoint last,
				t_ray_data rdata);
t_hitpoint	r_ray_hit_e_se(t_map *map, t_hitpoint last,
				t_ray_data rdata);
t_hitpoint	r_ray_hit_se_s(t_map *map, t_hitpoint last,
				t_ray_data rdata);

//raycasting_collision_segment_left.c
t_hitpoint	r_ray_hit_s_sw(t_map *map, t_hitpoint last,
				t_ray_data rdata);
t_hitpoint	r_ray_hit_sw_w(t_map *map, t_hitpoint last,
				t_ray_data rdata);
t_hitpoint	r_ray_hit_w_nw(t_map *map, t_hitpoint last,
				t_ray_data rdata);
t_hitpoint	r_ray_hit_nw_n(t_map *map, t_hitpoint last,
				t_ray_data rdata);

//raycasting_collision_hit_check.c
bool		r_ray_hit_check_basic(t_map *map, t_hitpoint *hit_pt,
				t_ray_data *rdata);
bool		r_ray_hit_check_extra_co(t_map *map, t_hitpoint *hit_pt,
				t_ray_data *rdata, t_vector_f real_hitpt_co);

//raycasting_collision_hit_check_door.c
bool		r_ray_hit_check_doors(t_map *map, t_hitpoint *hitpoint,
				t_ray_data *rdata, t_coord_f real_hitpoint_co);

//raycasting_tools.c
bool		r_point_outside_map(t_map *map, t_coord_f p_co);
bool		r_is_obstacle_f(t_map *map, float x, float y);
bool		r_is_obstacle_i(t_map *map, int x, int y);


#endif