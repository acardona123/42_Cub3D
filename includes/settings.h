/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:37:26 by acardona          #+#    #+#             */
/*   Updated: 2023/12/06 00:51:48 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include <X11/X.h>
# include <X11/keysym.h>

// force bonus mode:
// # ifndef BONUS
// #  define BONUS
// # endif

//window parameters
# define WIN_NAME		"Cub3D"
# define WIN_HEIGHT		900
# define WIN_WIDTH		1900

//game default parameters
# define DEFAULT_FOV					1.4
# define DEFAULT_DELAY					1
# define DEFAULT_WALK_SPEED				0.0016
# define DEFAULT_ROTATE_SPEED_KEY		0.0011

//game settings
# define FOV_INCREMENT	0.125
# define FOV_MIN		0.2
# define FOV_MAX		3.

//movement settings
# define WALK_SPEED_INCREMENT			0.0001
# define ROTATE_SPEED_KEY_INCREMENT		0.001
# define DIST_WALL_MIN 0.0125
# ifdef BONUS
#  define ROTATE_SPEED_MOUSE_INCREMENT	0.00005
# else
#  define FIXED_DELAY	20
# endif

# ifdef BONUS

//textures settings
#  define TEXTURE_PARAMETERS_FILE_NAME "frames_data.txt"

//actions
#  define ACTION_DOOR_TIME					1000.
#  define ACTION_DOOR_DIST_RANGE 			100.
#  define ACTION_LEAKS_CRASHES_DIST_RANGE	10.
#  define ACTION_LEAKS_CRASHES_BORDER_INF	.40
#  define ACTION_LEAKS_CRASHES_BORDER_SUP	.60

//cursor

#  define CURSOR_SIZE_RATIO			.01f
#  define CURSOR_COLOR_BACKGROUND	0xFFFFFF
#  define CURSOR_COLOR_CROSS		0x202020
#  define CURSOR_CROSS_WIDTH_RATIO	0.25f

//map settings
#  define MINIMAP_SIZE_DEFAULT			.33
#  define MINIMAP_SIZE_INCREMENT		.125
#  define MINIMAP_ZOOM_DEFAULT			.0625
#  define MINIMAP_ZOOM_INCREMENT		1
#  define MINIMAP_PLAYER_SIZE_DEFAULT	.125
#  define BIGMAP_PLAYER_SIZE_DEFAULT	.05
#  define BIGIMAP_PLAYER_SIZE_INCREMENT	.1
# endif

//minimap colors
# define MINIMAP_COLOR_F		0xe0e0e0
# define MINIMAP_COLOR_WALL		0x424242
# define MINIMAP_COLOR_NOTHING	0x696969
# define MINIMAP_COLOR_N		0xe0e0e0
# define MINIMAP_COLOR_E		0xe0e0e0
# define MINIMAP_COLOR_S		0xe0e0e0
# define MINIMAP_COLOR_W		0xe0e0e0
# define MINIMAP_COLOR_D_OPEN	0x5AD000
# define MINIMAP_COLOR_D_CLOSED	0xD25E5E
# define MINIMAP_COLOR_PLAYER	0x80FF
# define MINIMAP_COLOR_LEAKS	0x353535
# define MINIMAP_COLOR_CRASHES	0x353535
# define MINIMAP_COLOR_HOLOGRAM	0xa0a0a0

# define LEAKS_CRASHES_BACKGROUND	0xFFFFFF

// HELP
# define HELP_DISP_OFFSET 140
# define HELP_MSG_WIDTH 350
# define HELP_MSG_HEIGHT 560

typedef enum e_commands
{
	KEY_FORWARD			= XK_w,
	KEY_BACK			= XK_s,
	KEY_LEFT			= XK_a,
	KEY_RIGHT			= XK_d,
	KEY_LOOK_LEFT		= XK_Left,
	KEY_LOOK_RIGHT		= XK_Right,
	KEY_SPRINT			= XK_Shift_L,
	KEY_ACT				= XK_space,
	KEY_BIG_MAP			= XK_m,
	KEY_HELP			= XK_h,
	KEY_RESET_DEFAULT	= XK_0,
	KEY_WALK_SPEED		= XK_1,
	KEY_ROT_SPEED_KEY	= XK_2,
	KEY_ROT_SPEED_MOUSE	= XK_3,
	KEY_FOV				= XK_4,
	KEY_MINI_ZOOM		= XK_5,
	KEY_ESCAPE			= XK_Escape
}	t_command;

// adjustable parameters array in t_settings
typedef enum e_configuring
{
	CONFIG_NOTHING = 0,
	CONFIG_WALK_SPEED,
	CONFIG_MINI_ZOOM,
	CONFIG_MOUSE_ROTATION_SPEED,
	CONFIG_KEY_ROTATION_SPEED,
	CONFIG_FOV
}	t_configuring;

//float_precision
# define EPSILON 0.000001

#endif