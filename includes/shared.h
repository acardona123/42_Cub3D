/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:44:59 by acardona          #+#    #+#             */
/*   Updated: 2023/12/02 20:35:46 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include "settings.h"
# include "tools.h"
# include "message.h"

/*


==== Textures ==== */

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

typedef struct s_group_of_textures
{
	unsigned int		group_len;
	t_animated_texture	**textures_array;
}	t_group_of_textures;

# ifdef BONUS

#  define NUMBER_OF_TEXTURES 15

typedef struct s_texture_pack
{
	t_group_of_textures	wall_n;
	t_group_of_textures	wall_s;
	t_group_of_textures	wall_e;
	t_group_of_textures	wall_w;
	t_group_of_textures	wall_leaks;
	t_group_of_textures	wall_crashes;
	t_group_of_textures	door_front;
	t_group_of_textures	door_side_close;
	t_group_of_textures	door_side_open_opened;
	t_group_of_textures	door_side_open_opening;
	t_group_of_textures	door_side_open_closed;
	t_group_of_textures	door_side_open_closing;
	t_group_of_textures	leaks;
	t_group_of_textures	crashes;
	t_group_of_textures	hologram;
	int					color_f;
	int					color_c;
}	t_texture_pack;

# else

#  define NUMBER_OF_TEXTURES 4

typedef struct s_texture_pack
{
	t_group_of_textures	wall_n;
	t_group_of_textures	wall_s;
	t_group_of_textures	wall_e;
	t_group_of_textures	wall_w;
	int					color_f;
	int					color_c;
}	t_texture_pack;

# endif

/* ---- End: Textures ----



==== Map datas ==== */

# define CHARS_PLAYER "NESW"

# ifdef BONUS

#  define CHARS_ALLOWED		"01 NESWdlkjhcvbxp"
#  define CHARS_LEAKS		"lkjh"
#  define CHARS_CRASHES		"cvbx"
#  define CHARS_WALLS		"1lkjhcvbxp"
#  define CHARS_OBSTACLE	"1lkjhcvbx "
#  define CHARS_TRANSPARENT " 0NSEW"
#  define CHARS_NUMBER 17

typedef enum e_chunk_type
{
	FLOOR		= '0',
	WALL		= '1',
	DOOR		= 'd',
	LEAKS_N		= 'l',
	LEAKS_E		= 'k',
	LEAKS_S		= 'j',
	LEAKS_W		= 'h',
	CRASHES_N	= 'c',
	CRASHES_E	= 'v',
	CRASHES_S	= 'b',
	CRASHES_W	= 'x',
	HOLOGRAM	= 'p',
	NOTHING		= ' ',
	PLAYER_N	= 'N',
	PLAYER_E	= 'E',
	PLAYER_S	= 'S',
	PLAYER_W	= 'W'
}	t_chunk_type;

# else

#  define CHARS_ALLOWED "01 NESW"
#  define CHARS_OBSTACLE "1 "
#  define CHARS_TRANSPARENT " 0NSEW"
#  define CHARS_NUMBER 7

typedef enum e_chunk_type
{
	FLOOR = '0',
	WALL = '1',
	NOTHING = ' ',
	PLAYER_N = 'N',
	PLAYER_E = 'E',
	PLAYER_S = 'S',
	PLAYER_W = 'W'
}	t_chunk_type;

# endif

typedef enum e_chunk_face
{
	FACE_N,
	FACE_E,
	FACE_S,
	FACE_W
}	t_chunk_face;

typedef enum e_default_status
{
	INACTIVE,
	ACTIVE
}	t_default_status;

typedef struct s_chunk
{
	t_coord_i			chunk_co;
	t_chunk_type		type;
	size_t				t0;
	char				status;
	float				extra_data_f;
	int					extra_data_i;
	struct s_action		*action;
	t_animated_texture	*textures[4];
	unsigned int		textures_idx[4];
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



==== Minimap ==== */

typedef enum e_map_type
{
	MINIMAP,
	BIGMAP
}	t_map_type;

typedef struct s_minimap
{
	t_data	world;
	t_data	bigmap;
	int		bigmap_size_ratio;
	int		bigmap_offset_x;
	int		bigmap_offset_y;
}	t_minimap;

/* ---- End: Minimap ----



==== Player ==== */

typedef struct s_player
{
	t_coord_f	p_co;
	t_coord_i	p_chunk;
	float		p_angle;
	float		p_angle_cos;
	float		p_angle_sin;
}	t_player;

typedef enum e_player_walk
{
	GO_FORWARD,
	GO_RIGHT,
	GO_BACK,
	GO_LEFT
}	t_player_walk;

typedef enum e_player_turn
{
	TURN_R,
	TURN_L
}	t_player_turn;

/* ---- End: Player ----



==== Settings ==== */

typedef struct s_settings
{
	float		walk_speed;
	float		key_turn_speed;
	float		fov;
	float		mouse_turn_sensibility;
	int			minimap_size;
	int			minimap_zoom;
	int			minimap_player_size;
	int			bigmap_player_size;
	int			bigmap_size;
	int			configuring;
}	t_settings;

/* ---- End: Settings ----



==== Display ==== */

typedef enum e_img_to_disp
{
	RENDER_BLACK,
	RENDER_BIG_MAP,
	RENDER_INGAME,
	RENDER_CRASHES,
	RENDER_LEAKES
	BLACK,
	BIG_MAP,
	INGAME,
	RENDER_HELP
}	t_img_to_disp;

typedef struct s_display
{
	void			*mlx;
	void			*win;
	t_img_to_disp	render_selec;
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
	bool				next_walk[4];
	bool				next_turn_key[2];
	float				next_turn_mouse;
	bool				sprint;
	t_minimap			minimap;
}	t_general;

/* ---- End: General ----




==== Ray caracterisation ====  */

typedef enum e_ray_type
{
	ray_raycasting,
	ray_walk,
	ray_action
}	t_ray_type;

typedef struct s_ray_params
{
	t_ray_type	ray_type;
	size_t		ray_time;
	t_coord_f	ray_start_point;
	float		ray_angle;
}	t_ray_params;

# ifdef BONUS

typedef enum e_ray_door_behaviour
{
	ray_pass_door_never,
	ray_pass_door_always,
	ray_pass_door_fully_open,
	ray_pass_door_no_touch
}	t_ray_door_behaviour;

#  define CHARS_OBSTACLE_RAYCASTING "1lkjhcvbxp "
#  define CHARS_OBSTACLE_WALK "1lkjhcvbx "
#  define CHARS_OBSTACLE_ACTION "1dlkjhcvbxp "

# else

#  define CHARS_OBSTACLE_RAYCASTING "1 "
#  define CHARS_OBSTACLE_WALK "1 "

# endif

/* ---- End: Ray caracterisation ----



*/

# ifdef BONUS

/*

==== Doors ==== */

typedef enum e_door_data
{
	DOOR_VERTICAL,
	DOOR_HORIZONTAL,
	DOOR_TEXTURE_NEED_UPDATE
}	t_door_data;

typedef enum e_door_status
{
	DOOR_CLOSED,
	DOOR_CLOSING,
	DOOR_OPEN,
	DOOR_OPENING
}	t_door_status;

typedef enum e_door_action_target
{
	TARGET_DOOR_ITSELF,
	TARGET_DOOR_SIDE
}	t_door_action_target;

/* ---- End: Doors ----



==== Actions ==== */

typedef enum e_activable_faces
{
	ACTIVE_NONE,
	ACTIVE_N = 1,
	ACTIVE_E = 1 << 1,
	ACTIVE_S = 1 << 2,
	ACTIVE_W = 1 << 3
}	t_activable_faces;

struct			s_action;
typedef void	(*t_execute)(struct s_general *gen, size_t time_now,
					t_hitpoint *hitpoint);

typedef struct s_action
{
	int				active_faces;
	float			dist_range;
	struct s_chunk	**targets;
	t_execute		execute;
	size_t			time_last_act;
}	t_action;

/* ---- End: Actions ----*/

# else

typedef struct s_action
{
}	t_action;

# endif

/*



==== Public functions prototypes ==== */

// end_destroy
void		end_destroy_display(t_display *disp);
void		end_destroy_map(t_map *map);
void		end_destroy_texture_pack(void *mlx, t_texture_pack *pack);
void		end_destroy_general(t_general *gen);
void		end_destroy_exit(t_general *gen, t_exit_values n);

// shared
void		sh_chunk_set_texture(t_chunk *chunk, t_chunk_face face,
				t_group_of_textures *texture_group, bool new_seed);

# ifdef BONUS

bool		sh_doors_update_status(t_general *gen, t_chunk *door, size_t time);
void		sh_doors_update_texture_main_side(t_texture_pack *texture_pack,
				t_chunk *door);

# endif

// init
void		init_main(int ac, char **av, t_general	*gen);
void		sh_chunk_set_texture(t_chunk *chunk, t_chunk_face face,
				t_group_of_textures *texture_group, bool new_seed);

// ray_collision
t_hitpoint	r_ray_hit(t_general *gen, t_ray_params params);

// raycasting
void		*rc_raycasting_frame_build(t_general *gen, size_t last_time);

// gameplay
int			gp_looping(void *void_gen);
void		gp_action_main(t_general *gen);
void		gp_action_doors(t_general *gen, size_t time_now,
				t_hitpoint *hit_pt);
void		gp_leak_crash_action(t_general *gen, size_t time_now,
				t_hitpoint *hit_pt);

# ifdef BONUS

//maps
void		maps_draw_minimap(t_general *gen);
void		maps_world_update_door(t_general *gen, t_chunk *door);
void		maps_bigmap_draw_chunk(t_minimap *minimap, int chunk_x,
				int chunk_y);
void		maps_bigmap_put_player_window(t_display *disp, t_minimap *minimap,
				t_settings *settings, t_player *player);

# endif

// tools
//all the tools header is usefull and therefore has been included

#endif