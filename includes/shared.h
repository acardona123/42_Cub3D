/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:44:59 by acardona          #+#    #+#             */
/*   Updated: 2023/09/23 16:17:55 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include "tools.h"

# define WIN_HIGHT 720
# define WIN_WIDTH 1280
# define WIN_NAME "Cub3D"

# define KEY_FORWARD XK_w
# define KEY_BACK XK_s
# define KEY_LEFT XK_a
# define KEY_RIGHT XK_d
# define KEY_ACT XK_space
# define KEY_LOOK_LEFT XK_Left
# define KEY_LOOK_RIGHT XK_Right

typedef enum e_chunk_type
{
	FLOOR = '0',
	DOOR = '2',
	WALL = '1',
	NOTHING = ' ',
}	t_chunk_type;

typedef enum e_chunk_face
{
	FACE_N ,
	FACE_E ,
	FACE_S ,
	FACE_O ,
}	t_chunk_face;

typedef struct s_hitpoint
{
	t_coord_f			impactpoint_coord;
	t_coord_i			chunk_coord;
	t_chunk_face		face;
}	t_hitpoint;


typedef struct s_data_map
{
	float	x_max;
	float	y_max;
	char	**map;
}	t_data_map;

// ---- End: Map data ----


==== Textures ==== */

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		opp;
	int		line_length;
	int		pix_width;
	int		pix_height;
	int		endian;
}	t_data;

typedef struct s_static_texture
{
	char	*path;
	int		img_width;
	int		img_height;
	t_data	data;
}	t_static_texture;

typedef struct s_animated_texture
{
	unsigned int		frame_number;
	unsigned int		frame_ms;//time between 2 consecutive frames without pause
	unsigned int		frame_pause_ms;
	unsigned int		frame_cycle_short;//time to display all frames without pause
	unsigned int		frame_cycle_long;//time of the complete cycle including pause
	t_static_texture	*frame_table;
}	t_animated_texture;

# define NUMBER_OF_TEXTURES 7

typedef struct s_texture_pack
{
	t_animated_texture	*wall_n;
	t_animated_texture	*wall_s;
	t_animated_texture	*wall_e;
	t_animated_texture	*wall_w;
	t_animated_texture	*door_front;
	t_animated_texture	*door_side_l;
	t_animated_texture	*door_side_r;
}	t_texture_pack;

/* ---- End: Textures ----



==== Map datas ==== */

typedef enum e_chunk_type
{
	FLOOR = '0',
	DOOR = '2',
	WALL = '1',
	NOTHING = ' ',
}	t_chunk_type;

typedef enum e_door_status
{
	DOOR_OPEN,
	DOOR_OPENING,
	DOOR_CLOSING,
	DOOR_CLOSED
}	t_door_status;

typedef struct s_chunk
{
	t_chunk_type		type;
	char				status;
	unsigned int		t0;//ref time for the animations
	t_animated_texture	*textures;
}	t_chunk;

typedef struct s_map
{
	double	x_max;
	double	y_max;
	int		widht;
	int		height;
	t_chunk	**map;
}	t_map;

/* ---- End: Map data ----



==== Player ==== */

typedef struct s_player
{
	t_coord		p_co;
	float		p_angle;
	float		p_speed;
}	t_player;

/* ---- End: Player ----



==== Display ==== */

typedef struct s_display
{
	void			*mlx;
	t_data			*buff;
	void			*win;
}	t_display;

/* ---- End: Display ----



==== General ==== */

typedef struct s_general
{
	t_display	disp;
	t_player			player;
	t_texture_pack		textures;
	t_map				map;
	float				fov;
}	t_general;

/* ---- End: General ----


==== end_destroy ==== */
//end_destroy_display_close.c
void	end_destroy_display(t_display *disp);

// end_destroy_map.c
void	end_destroy_map(t_map *map);

//end_detroy_texture_pack.c
void	end_destroy_texture_pack(void *mlx, t_texture_pack *pack);

//end_destroy_general.c
void	end_destroy_general(t_general *gen);

//end_destroy_exit.c
void	end_destroy_exit(t_general *gen, t_exit_values n);

#endif
