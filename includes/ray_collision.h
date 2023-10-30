/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:05:10 by acardona          #+#    #+#             */
/*   Updated: 2023/10/30 03:12:38 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_COLLISION_H
# define RAY_COLLISION_H

# include "shared.h"
# ifdef BONUS
#  include "doors.h"
# endif

typedef enum e_1st_type
{
	FIRST_H,
	FIRST_V,
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

typedef enum e_primary_axis
{
	PRIMARY_H,
	PRIMARY_V
}	t_primary_axis;

typedef struct s_ray_data
{
	size_t			time_now;
	t_dial			dial;
	t_primary_axis	prim;
	t_1st_type		first;
	bool			check_h;
	t_coord_f		last_h;
	bool			check_v;
	t_coord_f		last_v;
	float			delta_y;
	float			delta_x;
	float			shift;
}	t_ray_data;

typedef struct s_init_chunks
{
	int	init0_vx;
	int	init0_vy;
	int	init0_hx;
	int	init0_hy;
}	t_init_chunks;

typedef t_hitpoint	(*t_collision_function)(t_map*, t_hitpoint, t_ray_data);

//raycasting_collision.c
t_hitpoint	r_ray_hit_view(t_coord_f *p_co, float angle_ray, t_map *map,
				size_t time_now);
t_hitpoint	r_ray_hit_move(t_coord_f *p_co, float angle_ray, t_map *map,
				size_t time_now);

//raycasting_collision_init.c
t_hitpoint	r_ray_init_rdata_hitpoint(t_coord_f *p_co, float angle_ray,
				t_map *map, t_ray_data *rdata);

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
bool		r_ray_hit_primary(t_map *map, t_hitpoint *hit_pt,
				t_ray_data *rdata);
bool		r_ray_hit_sec(t_map *map, t_hitpoint *hit_pt,
				t_ray_data *rdata, t_vector_f real_hitpt_co);

//raycasting_collision_hit_check_door.c
bool		r_ray_hit_check_doors_prim(t_map *map, t_ray_data *rdata,
				t_hitpoint *hitpoint, t_coord_f real_hitpoint_co);
bool		r_ray_hit_check_doors_sec(t_map *map, t_ray_data *rdata,
				t_hitpoint *hitpoint, t_coord_f real_hitpoint_co);

//raycasting_tools.c
bool		r_point_outside_map(t_map *map, t_coord_f p_co);
bool		r_ray_hit_check_solid_chunk(t_chunk **map, int chunk_co_x,
				int chunk_co_y);

#endif