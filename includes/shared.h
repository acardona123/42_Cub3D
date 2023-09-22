/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:44:59 by acardona          #+#    #+#             */
/*   Updated: 2023/09/22 15:12:42 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include "tools.h"


// ==== Map datas ====

typedef enum e_bloc_type
{
	FLOOR = '0',
	DOOR = '2',
	WALL = '1',
	NOTHING = ' ',
}	t_bloc_type;

typedef struct s_data_map
{
	float	x_max;
	float	y_max;
	char	**map;
}	t_data_map;

// ---- End: Map data ----



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

typedef struct s_static_texture_tail
{
	char	*path;
	int		img_width;
	int		img_height;
	t_data	data;
}	t_static_texture_tail;

typedef struct s_animated_texture_tail
{
	unsigned int			frame_number;
	unsigned int			frame_t0;//ref time for the animations
	unsigned int			frame_ms;//time between 2 consecutive frames without pause
	unsigned int			frame_pause_ms;
	unsigned int			frame_cycle_short;//time to display all frames without pause
	unsigned int			frame_cycle_long;//time of the complete cycle including pause
	t_static_texture_tail	*frame_table;
}	t_animated_texture_tail;


// ---- End: Textures ----

#endif