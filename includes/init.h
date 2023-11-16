/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:30:53 by acardona          #+#    #+#             */
/*   Updated: 2023/11/16 19:23:09 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "shared.h"

# include <sys/stat.h>
# include <fcntl.h>

# ifdef BONUS
#  include <sys/types.h>
#  include <dirent.h>
# endif

# define MSG_SETTINGS_ERROR "Initialisation: wrong settings in defines"
# define MSG_MAP_OPEN_FAIL "Map: cannot open the given map file"

//map parameters error messages
# define MSG_MAP_FILE_FORMAT "Map: format incorrect, requieres a .cub file"
# define MSG_WRONG_LINE_FORMAT "Map: wrong number of parameters in a texture \
definition"
# define MSG_WRONG_ACRONYME "Map: wrong acronym for a texture definition or \
wrong character in the top line of the map content"
# define MSG_OPENDIR_FORBIDDEN "Map: cannot open folder in the mandatory part"
# define MSG_OPENDIR_FAIL "Map: fail to open a texture directory"
# define MSG_NO_XPM_IN_FOLDER "Map: no .xpm file in a texture folder"
# define MSG_ACCEPT_ONLY_XPM "Map: to avoid mlx leaks this program can only \
handle .xpm images as textures, sorry"
# define MSG_ERR_OPEN_TEXTURE "Map: texture file not reachable/readable"
# define MSG_TEXTURE_MISSING_WALL_N "Map: missing texture for the walls' north \
face"
# define MSG_TEXTURE_MISSING_WALL_E "Map: missing texture for the walls' east \
face"
# define MSG_TEXTURE_MISSING_WALL_S "Map: missing texture for the walls' south \
face"
# define MSG_TEXTURE_MISSING_WALL_W "Map: missing texture for the walls' west \
face"
# define MSG_TEXTURE_MISSING_DOOR_F "Map: missing texture for the doors' front"
# define MSG_TEXTURE_MISSING_DOOR_S "Map: missing texture for the doors' sides"
# define MSG_TEXTURE_MULTIPLE_DEF "Map: Multiple definition of texture"
# define MSG_WRONG_COLOR_FORMAT "Map: wrong color format"
# define MSG_COLOR_MISSING_CEIL "Map: missing color for the ceilling"
# define MSG_COLOR_MISSING_FLOOR "Map: missing color for the floor"
# define MSG_COLOR_MULTIPLE_DEF "Map: Multiple definition of flor/ceil color"
# define MSG_WRONG_TIME "Map: wrong time argument in texture definition"

//map content error messages
# define MSG_NO_MAP_CONTENT "Map: map content under all the textures"
# define MSG_MAP_NOT_CLOSED "Map: not surrounded by walls"
# define MSG_INVALID_CHAR "Map: contains an invalid character"
# define MSG_MULTIPLE_PLAYER "Map: multiple player's position"
# define MSG_NO_PLAYER "Map: does not contain a player position"
# define MSG_DOOR_ISOLATED "Map: door not surrounded by at least two opposit\
 walls"
# define MSG_EMPTY_LINE "Map: empty line in the map content"

//big map warning
# define MSG_WARNING_BIG_MAP "Warning: map dimensions bigger than the window. \
You will not be abble to display a big global map\n"

typedef struct s_init_lists
{
	t_list			*lst_param;
	t_list			*lst_map;
	unsigned int	map_nb_lines;
	unsigned int	map_nb_col;
}	t_lists;

typedef enum e_texture_int_index
{
	IDX_FLOOR,
	IDX_CEIL
}	t_texture_int_index;

typedef enum e_mouse_keys
{
	MOUSE_LEFT_CLICK = 1,
	MOUSE_RIGHT_CLICK = 2,
	MOUSE_MIDDLE_CLICK = 3,
	MOUSE_SCROLL_UP = 4,
	MOUSE_SCROLL_DOWN = 5
}	t_mouse_keys;

void	init_main(int ac, char **av, t_general	*gen);

// init_3_utils.c
void	in_init_destroy_lists_exit(t_general *gen, t_lists *lst_init,
			char *err_msg, int exit_value);

/* =============== 0_mapformat/ =============== */
// init_0_mapformat_main.c
t_lists	in_1_map_format_check(int ac, char **av, t_general *gen);
// init_o_mapformat_utils.c
int		in_1_file_opening(char *file_name);
bool	in_1_line_is_parameter(char *line);
bool	in_1_line_is_empty(char *line);

/*

 =============== 1_user_interface/ =============== */
// init_1_user_interface_main.c
void	in_0_init_display(t_general *gen);
// in_0_init_display_hooks.c
void	in_0_hooks_init(t_general *gen);
// init_0_user_interface_hooks_keys;
int		in_0_hooks_keys_press(int key, t_general *gen);
int		in_0_hooks_keys_release(int key, t_general *gen);
// init_0_user_interface_hooks_mouse.c
int		in_0_hooks_mouse_move(int x, int y, t_general *gen);
int		in_0_hooks_mouse_button(int key, int x, int y, t_general *gen);

/*

=============== 2_texturepack/ =============== */
// init_2_texturepack_main.c
void	in_2_init_texture_pack(t_general *gen, t_lists *lst_init);
// init_2_texturepack_check_texture_defined.c
bool	in_2_are_all_mandatory_textures_init(t_texture_pack *texturepack,
			bool *colors_defined);
//init_2_texturepack_set_color.c
t_bool	in_2_set_color(int *dest_color, char **line_arg,
			bool *already_done);
//init_2_texturepack_animated_texture.c
t_bool	in_2_anim_textu_init(void *mlx, t_animated_texture **texture,
			char **line_arg);
//init_2_texturepack_static_texture.c
t_bool	in_2_static_texture_init_one(void *mlx, t_static_texture *texture,
			char *path);
//init_2_texturepack_tools.c
t_bool	in_2_tools_count_xpm_files_in_folder(char *dir_name,
			unsigned int *cpt);
void	in_2_tools_sort_anim_text_table(t_static_texture *frame_array,
			unsigned int frame_number);
/*

=============== 3_mapcontent/ =============== */
// init_3_mapcontent.c
void	in_3_mapcontent_init(t_general *gen, t_lists *lst_init);
// init_3_mapcontent_fill_chunk.c
bool	in_3_mapcontent_fill_chunk_ok(t_general *gen, int c_type, int x,
			int y);
// init_3_mapcontent_locate_texture.c
t_bool	in_3_map_add_locate_textures(t_texture_pack *texturepack,
			t_animated_texture **tex, char c);
void	in_3_map_add_door_sides_textures(t_chunk **map,
			t_texture_pack *textures, int door_x, int door_y);
// init_3_mapcontent_set_status_action.c
t_bool	in_3_mapcontent_status_action_init(t_map *map);
/*

=============== 4_minimap/ =============== */
void	in_4_minimap_init(t_general *gen);
void	in_4_bigmap_init(t_general *gen);

// init_4_maps_world.c
void	in_4_world_init(t_general *gen);
#endif