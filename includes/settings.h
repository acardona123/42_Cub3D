/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:37:26 by acardona          #+#    #+#             */
/*   Updated: 2023/10/04 15:37:47 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include <X11/X.h>
# include <X11/keysym.h>

//window parameters
# define WIN_HEIGHT 720
# define WIN_WIDTH 1080
# define WIN_NAME "Cub3D"

//game parameters
# define DEFAULT_FOV 12
# define DIST_WALL_MIN 0.125
//rotation speed (rad/ms)
# define ROTATE_SPEED_KEY 0.002
//walk speed (m/ms)
# define WALK_SPEED 0.1

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
	KEY_WALK_SPEED_UP	= XK_KP_8,
	KEY_WALK_SPEED_DOWN	= XK_KP_2,
	KEY_ROT_SPEED_UP	= XK_KP_6,
	KEY_ROT_SPEED_DOWN	= XK_KP_4,
	KEY_ESCAPE			= XK_Escape
}	t_command;

//float_precision
# define FLOAT_EPSILON 0.000001

#endif