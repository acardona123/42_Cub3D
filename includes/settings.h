/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:37:26 by acardona          #+#    #+#             */
/*   Updated: 2023/10/03 18:26:51 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

//window parameters
# define WIN_HEIGHT 1280
# define WIN_WIDTH 2000
# define WIN_NAME "Cub3D"

//game parameters
# define DEFAULT_FOV 1.
# define DIST_WALL_MIN 0.125

//controls :
# define KEY_FORWARD XK_w
# define KEY_BACK XK_s
# define KEY_LEFT XK_a
# define KEY_RIGHT XK_d
# define KEY_ACT XK_space
# define KEY_LOOK_LEFT XK_Left
# define KEY_LOOK_RIGHT XK_Right

#define BONUS//

# define FLOAT_EPSILON 0.000001

#endif