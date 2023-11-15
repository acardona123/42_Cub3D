/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_4_maps_world.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:15:23 by acardona          #+#    #+#             */
/*   Updated: 2023/11/15 15:02:18 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

static int			g_colors[MINIMAP_NUMBER_COLORS - 1] = {MINIMAP_COLOR_F,
	MINIMAP_COLOR_WALL, MINIMAP_COLOR_NOTHING, MINIMAP_COLOR_N,
	MINIMAP_COLOR_E, MINIMAP_COLOR_S, MINIMAP_COLOR_W, MINIMAP_COLOR_D_OPEN,
	MINIMAP_COLOR_D_CLOSED};

static t_chunk_type	g_type[CHARS_NUMBER] = {FLOOR, WALL, NOTHING, PLAYER_N,
	PLAYER_E, PLAYER_S, PLAYER_W, DOOR};

static int	_in_4_get_chunk_color_from_map(t_general *gen, int x, int y);

/**
 * @brief creates an image where each pixel corresponds to a chunk. this image
 *	named world is used to generate the minimap
 * 
 * @param gen 
 */
void	in_4_world_init(t_general *gen)
{
	int	x;
	int	y;

	if (to_mlx_new_empty_img(gen->disp.mlx, &gen->minimap.world, gen->map.width,
			gen->map.height) == FAIL)
		end_destroy_exit(gen, EXIT_INIT_4);
	x = -1;
	while (++x < gen->map.width)
	{
		y = -1;
		while (++y < gen->map.height)
			*(int *)(gen->minimap.world.addr + gen->minimap.world.line_len
					* (gen->map.height - y) + x * gen->minimap.world.opp)
				= _in_4_get_chunk_color_from_map(gen, x, y);
	}
}

/**
 * @brief get the color of the pixel corresponding to the chunk (x, y)
 *	in the world minimap image, the colors for each type are defined in
 *	the settings
 * 
 * @param gen 
 * @param x 
 * @param y 
 */
static int	_in_4_get_chunk_color_from_map(t_general *gen, int x, int y)
{
	int	i;
	int	color;

	i = -1;
	while (++i < CHARS_NUMBER)
	{
		if (g_type[i] == gen->map.map[x][y].type)
			break ;
	}
	if (gen->map.map[x][y].type == DOOR)
	{
		if (gen->map.map[x][y].status == DOOR_OPEN)
			color = MINIMAP_COLOR_D_OPEN;
		else
			color = MINIMAP_COLOR_D_CLOSED;
	}
	else
		color = g_colors[i];
	return (color);
}

#endif