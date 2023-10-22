/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:37:26 by acardona          #+#    #+#             */
/*   Updated: 2023/10/22 03:15:11 by acardona         ###   ########.fr       */
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
# define WIN_HEIGHT 900
# define WIN_WIDTH 1500
# define WIN_NAME "Cub3D"

//game default parameters
# define DEFAULT_FOV 1.4
# define DEFAULT_ROTATE_SPEED_KEY 0.0006
# define DEFAULT_ROTATE_SPEED_MOUSE 0.1
# define DEFAULT_WALK_SPEED 0.0016
# define DEFAULT_DELAY 1

//game settings
# define DIST_WALL_MIN 0.015625
# define ROTATE_SPEED_KEY_INCREMENT 0.001
# define ROTATE_SPEED_MOUSE_INCREMENT 0.001
# define WALK_SPEED_INCREMENT 0.05
# define FOV_INCREMENT 0.125
# define FOV_MIN 0.0125
# define FOV_MAX 3.14

# ifndef BONUS
#  define FIXED_DELAY 20
# endif

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