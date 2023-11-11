/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_4_minimap_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:11:57 by acardona          #+#    #+#             */
/*   Updated: 2023/11/11 22:26:21 by acardona         ###   ########.fr       */
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

static void	_in_4_minimap_set_chunk_pxl(t_general *gen, int x, int y);

void	in_4_minimap_init(t_general *gen)
{
	int	x;
	int	y;

	gen->minimap.world.img = mlx_new_image(gen->disp.mlx, gen->map.width,
			gen->map.height);
	if (!gen->minimap.world.img)
		end_destroy_exit(gen, EXIT_INIT_4);
	gen->minimap.world.addr = mlx_get_data_addr(gen->minimap.world.img,
			&gen->minimap.world.opp, &gen->minimap.world.line_len,
			&gen->minimap.world.endian);
	gen->minimap.world.opp /= 8;
	gen->minimap.world.pix_width = gen->map.width;
	gen->minimap.world.pix_height = gen->map.height;
	x = -1;
	while (++x < gen->map.width)
	{
		y = -1;
		while (++y < gen->map.height)
			_in_4_minimap_set_chunk_pxl(gen, x, y);
	}
}

/**
 * @brief set the pixel corresponding to the chunk (x, y) in the world minimap
 *	image, the colors for each type are defined in the settings
 * 
 * @param gen 
 * @param x 
 * @param y 
 */
static void	_in_4_minimap_set_chunk_pxl(t_general *gen, int x, int y)
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
	*(int *)(gen->minimap.world.addr + gen->minimap.world.line_len
			* (gen->map.height - y) + x * gen->minimap.world.opp) = color;
}

#endif