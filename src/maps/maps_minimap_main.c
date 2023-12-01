/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_minimap_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:45:44 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 19:48:08 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/maps.h"

#ifdef BONUS

static void	_maps_draw_player_minimap(t_general *gen,
				int x_center_player, int y_center_player);

/**
 * @brief draws the minimap, centered on the player position and oriented toward
 *		the player angle
 * 
 * @param gen 
 */
void	maps_draw_minimap(t_general *gen)
{
	register int	x_map;
	register int	y_map;
	register char	*addr;
	static int		radius = 0;
	static int		radius_pow2 = 0;

	if (radius != gen->settings.minimap_size >> 1)
	{
		radius = gen->settings.minimap_size >> 1;
		radius_pow2 = radius * radius;
	}
	x_map = -1;
	while (++x_map < gen->settings.minimap_size)
	{
		addr = gen->disp.buff->addr + x_map * gen->disp.buff->opp + (WIN_HEIGHT
				- gen->settings.minimap_size - 1) * gen->disp.buff->line_len;
		y_map = -1;
		while (++y_map < gen->settings.minimap_size)
		{
			addr += gen->disp.buff->line_len;
			if (pow(x_map - radius, 2) + pow(y_map - radius, 2) <= radius_pow2)
				*(int *)addr = maps_get_pixel_color_minimap(gen, x_map, y_map);
		}
	}
	_maps_draw_player_minimap(gen, radius, WIN_HEIGHT - radius - 1);
}

/**
 * @brief draws the player symbole (an arrow) on the minimap image
 * 
 * @param gen 
 * @param x_center_player 
 * @param y_center_player 
 */
static void	_maps_draw_player_minimap(t_general *gen,
	register int x_center_player, register int y_center_player)
{
	register int	x;
	register int	y;

	x_center_player -= gen->settings.minimap_player_size >> 1;
	y_center_player -= gen->settings.minimap_player_size >> 1;
	x = -1;
	while (++x < gen->settings.minimap_player_size)
	{
		y = -1;
		while (++y < gen->settings.minimap_player_size)
		{
			if ((x <= gen->settings.minimap_player_size / 2
					&& y >= 2 * gen->settings.minimap_player_size - 4 * x)
				|| (x > gen->settings.minimap_player_size / 2
					&& y >= -2 * gen->settings.minimap_player_size + 4 * x))
				*(int *)(gen->disp.buff->addr
						+ (x_center_player + x) * gen->disp.buff->opp
						+ (y_center_player + y) * gen->disp.buff->line_len)
					= MINIMAP_COLOR_PLAYER;
		}
	}
}

#endif