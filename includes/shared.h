/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:44:59 by acardona          #+#    #+#             */
/*   Updated: 2023/10/23 04:10:10 by acardona         ###   ########.fr       */
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
	unsigned int		frame_ms;
	unsigned int		frame_pause_ms;
	unsigned int		frame_cycle_short;
	unsigned int		frame_cycle_long;
	t_static_texture	*frame_array;
}	t_animated_texture;

# define NUMBER_OF_TEXTURES 6

typedef struct s_texture_pack
{
	t_animated_texture	*wall_n;
	t_animated_texture	*wall_s;
	t_animated_texture	*wall_e;
	t_animated_texture	*wall_w;
	t_animated_texture	*door_front;
	t_animated_texture	*door_side;
	int					color_f;
	int					color_c;
}	t_texture_pack;

/* ---- End: Textures ----



==== Map datas ==== */

# ifdef BONUS
#  define CHARS_ALLOWED "01d NESW"
# else
#  define CHARS_ALLOWED "01 NESW"
# endif
# define CHARS_PLAYER "NESW"
# define CHARS_MAP_BORDER "1 "
# define CHARS_TRANSPARENT " 0NSEW"

typedef enum e_chunk_type
{
	FLOOR = '0',
	WALL = '1',
	DOOR = 'd',
	NOTHING = ' ',
	PLAYER_N = 'N',
	PLAYER_E = 'E',
	PLAYER_S = 'S',
	PLAYER_W = 'W'
}	t_chunk_type;

typedef enum e_chunk_face
{
	FACE_N,
	FACE_E,
	FACE_S,
	FACE_W
}	t_chunk_face;

typedef enum e_door_status
{
	DOOR_OPEN,
	DOOR_OPENING,
	DOOR_CLOSING,
	DOOR_CLOSED
}	t_door_status;

typedef enum e_other_status
{
	INACTIVE,
	ACTIVE
}	t_other_status;

typedef struct s_chunk
{
	t_chunk_type		type;
	char				status;
	size_t				t0;
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
	t_coord_f			pt_co;
	int					chunk_co_x;
	int					chunk_co_y;
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
	t_data			*img_out_map;
}	t_display;

/* ---- End: Display ----




==== General ==== */

typedef struct s_general
{
	t_display			disp;
	t_texture_pack		textures;
	t_map				map;
	t_player			player;
	t_settings			settings;
	double				angles_set[WIN_WIDTH];
	double				angle_correc[WIN_WIDTH];
	bool				next_moove[6];
}	t_general;

/* ---- End: General ----


==== Public functions prototypes ==== */

// end_destroy
void		end_destroy_display(t_display *disp);
void		end_destroy_map(t_map *map);
void		end_destroy_texture_pack(void *mlx, t_texture_pack *pack);
void		end_destroy_general(t_general *gen);
void		end_destroy_exit(t_general *gen, t_exit_values n);

// init
void		init_main(int ac, char **av, t_general	*gen);

// ray_collision
t_hitpoint	r_ray_hit(t_coord_f *p_co, float angle_ray, t_map *map,
				bool obstacles_shift);

// raycasting
void		*rc_raycasting_frame_build(t_general *gen, size_t last_time);

// gameplay
int			gp_looping(void *void_gen);

// tools
//all the tools header is usefull and therefore has been included

#endif