/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:44:59 by acardona          #+#    #+#             */
/*   Updated: 2023/09/22 17:16:35 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include "tools.h"


// ==== Textures ====

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		pix_width;
	int		pix_height;
	int		endian;
}	t_data;

typedef struct s_static_texture
{
	char	*path;
	int		img_width;
	int		img_height;
	t_data	data;
}	t_static_texture;

typedef struct s_animated_textures
{
	unsigned int		frame_number;
	unsigned int		frame_ms;//time between 2 consecutive frames without pause
	unsigned int		frame_pause_ms;
	unsigned int		frame_cycle_short;//time to display all frames without pause
	unsigned int		frame_cycle_long;//time of the complete cycle including pause
	t_static_texture	*frame_table;
}	t_animated_textures;

// ---- End: Textures ----


// ==== Map datas ====

typedef enum e_chunk_type
{
	FLOOR = '0',
	DOOR = '2',
	WALL = '1',
	NOTHING = ' ',
}	t_chunk_type;

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
	unsigned int		t0;//ref time for the animations
	t_animated_textures	*textures;
}	t_chunk;

typedef struct s_map
{
	float	x_max;
	float	y_max;
	t_chunk	**map;
}	t_map;

// ---- End: Map data ----



// ==== Player ====

typedef	struct s_player
{
	t_coord		p_co;
	float		p_angle;
	float		p_speed;
}	t_player;

// ---- End: Player ----

typedef struct s_display
{
	void	*mlx;
	void	*win;
	t_data	*buff;
}	t_display;

typedef struct s_general
{
	t_map		map;
	t_player	player;
	t_display	disp;
	float		fov;
}	t_general;

#endif