/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:44:59 by acardona          #+#    #+#             */
/*   Updated: 2023/10/05 01:34:17 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include "settings.h"
# include "tools.h"

/*


==== Textures ==== */

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		opp;
	int		line_len;
	int		pix_width;
	int		pix_height;
	int		endian;
}	t_data;

typedef struct s_static_texture
{
	char	*path;
	int		img_width;
	int		img_height;
	float	h_ratio;
	t_data	data;
}	t_static_texture;

typedef struct s_animated_texture
{
	unsigned int		frame_number;
	unsigned int		frame_ms;//time between 2 consecutive frames without pause
	unsigned int		frame_pause_ms;
	unsigned int		frame_cycle_short;//time to display all frames without pause
	unsigned int		frame_cycle_long;//time of the complete cycle including pause
	t_static_texture	*frame_array;
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
	int					color_f;
	int					color_c;
}	t_texture_pack;

/* ---- End: Textures ----



==== Map datas ==== */

typedef enum e_chunk_type
{
	FLOOR = '0',
	DOOR = '2',
	WALL = '1',
	NOTHING = ' ',
	PLAYER_N = 'N',
	PLAYER_S = 'S',
	PLAYER_E = 'E',
	PLAYER_W = 'W',
}	t_chunk_type;

typedef enum e_chunk_face
{
	FACE_N ,
	FACE_E ,
	FACE_S ,
	FACE_W ,
}	t_chunk_face;

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
	size_t				t0;//ref time for the animations
	t_animated_texture	*textures[4];
}	t_chunk;

typedef struct s_map
{
	double	x_max;
	double	y_max;
	int		width;
	int		height;
	t_chunk	**map;
}	t_map;

typedef struct s_hitpoint
{
	t_coord_f			point_co;
	t_coord_i			chunk_co;
	// double				hit_dec; for future opti ?
	t_chunk_face		hit_face;
	double				dist;
}	t_hitpoint;

/* ---- End: Map data ----



==== Player ==== */

typedef struct s_player
{
	t_coord_f	p_co;
	float		p_angle;
}	t_player;

typedef enum e_head_rotate
{
	TURN_SIGN_R = 1,
	TURN_SIGN_L = -1
}	t_head_rotate;

typedef enum e_player_move
{
	GO_FORWARD,
	GO_RIGHT,
	GO_BACK,
	GO_LEFT,
	TURN_R,
	TURN_L
}	t_player_move;

/* ---- End: Player ----



==== Settings ==== */

typedef struct s_settings
{
	float		walk_speed;
	float		key_turn_speed;
	float		mouse_turn_speed;
	float		fov;
}	t_settings;

/* ---- End: Settings ----



==== Display ==== */

typedef struct s_display
{
	void			*mlx;
	void			*win;
	t_data			*buff;
}	t_display;

/* ---- End: Display ----




==== delay ==== */

typedef struct s_delay
{
	unsigned int	idx;
	float			delay_average;
	unsigned int	delay_array[DELAY_AVERAGE_AMPITUDE];
	size_t			last_time;
}	t_delay;

/* ---- End: delay ----




==== General ==== */

typedef struct s_general
{
	t_display			disp;
	t_texture_pack		textures;
	t_map				map;
	t_player			player;
	t_settings			settings;
	t_delay				delays;
	double				angles_set[WIN_WIDTH];
	double				angle_correc[WIN_WIDTH];
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
