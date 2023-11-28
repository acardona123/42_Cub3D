/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:37:26 by acardona          #+#    #+#             */
/*   Updated: 2023/11/28 22:21:08 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include <X11/X.h>
# include <X11/keysym.h>

//force bonus mode:
// # ifndef BONUS
// #  define BONUS
// # endif

//window parameters
# define WIN_NAME		"Cub3D"
# define WIN_HEIGHT		900
# define WIN_WIDTH		1500

//game default parameters
# define DEFAULT_FOV					1.4
# define DEFAULT_DELAY					1
# define DEFAULT_WALK_SPEED				0.0016
# define DEFAULT_ROTATE_SPEED_KEY		0.0011
# ifdef BONUS
#  define DEFAULT_ROTATE_MOUSE_SENSIBILITY	0.001
# endif

//game settings
# define FOV_INCREMENT	0.125
# define FOV_MIN		0.0125
# define FOV_MAX		3.14

//movement settings
# define WALK_SPEED_INCREMENT			0.0001
# define ROTATE_SPEED_KEY_INCREMENT		0.001
# define DIST_WALL_MIN					0.25
// # define DIST_WALL_MIN 0.015625
# ifdef BONUS
#  define ROTATE_SPEED_MOUSE_INCREMENT	0.001
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
#  define MINIMAP_ZOOM_INCREMENT		.0625
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

# define LEAKS_CRASHES_BACKGROUND	0x696969

//controls :
# define NUMBER_KEY 12

typedef enum e_commands
{
	KEY_FORWARD			= XK_w,
	KEY_BACK			= XK_s,
	KEY_LEFT			= XK_a,
	KEY_RIGHT			= XK_d,
	KEY_LOOK_LEFT		= XK_Left,
	KEY_LOOK_RIGHT		= XK_Right,

	KEY_ACT				= XK_space,
	KEY_BIG_MAP			= XK_m,

	KEY_WALK_SPEED_UP	= XK_KP_8,//les kp ne marchent pas
	KEY_WALK_SPEED_DOWN	= XK_KP_2,
	KEY_ROT_SPEED_UP	= XK_KP_6,
	KEY_ROT_SPEED_DOWN	= XK_KP_4,
	KEY_FOV_UP			= XK_KP_Add,
	KEY_FOV_DOWN		= XK_KP_Subtract,
	KEY_ESCAPE			= XK_Escape
}	t_command;

//float_precision
# define EPSILON 0.000001

#endif