/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:37:26 by acardona          #+#    #+#             */
/*   Updated: 2023/10/04 00:45:41 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

//window parameters
# define WIN_HEIGHT 720
# define WIN_WIDTH 1080
# define WIN_NAME "Cub3D"

//game parameters
# define DEFAULT_FOV 1.
# define DIST_WALL_MIN 0.125
//rotation speed (rad/ms)
# define ROTATE_SPEED_KEY 0.002
//walk speed (m/ms)
# define WALK_SPEED 0.1

//controls :
# define KEY_FORWARD XK_w
# define KEY_BACK XK_s
# define KEY_LEFT XK_a
# define KEY_RIGHT XK_d
# define KEY_ACT XK_space
# define KEY_LOOK_LEFT XK_Left
# define KEY_LOOK_RIGHT XK_Right

// #define BONUS//

# define FLOAT_EPSILON 0.000001

#endif