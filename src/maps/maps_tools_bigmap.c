/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_tools_bigmap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:35:25 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 19:56:59 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/maps.h"

#ifdef BONUS

static void	_maps_bigmap_put_circle_window(t_display *disp, t_coord_i center,
				int radius, int color);

/**
 * @brief draws a chunk in the big map
 * 
 * @param minimap 
 * @param chunk 
 * @param x
 * @param y
 */
void	maps_bigmap_draw_chunk(t_minimap *minimap, int chunk_x, int chunk_y)
{
	int		x_in_chunk;
	int		y_in_chunk;
	int		color;
	char	*addr;

	color = maps_world_get_chunk_color(minimap, chunk_x, chunk_y);
	y_in_chunk = -1;
	while (++y_in_chunk < minimap->bigmap_size_ratio)
	{
		addr = minimap->bigmap.addr + (minimap->bigmap_offset_x
				+ minimap->bigmap_size_ratio * chunk_x)
			* minimap->bigmap.opp + (minimap->bigmap_offset_y
				+ minimap->bigmap_size_ratio * (minimap->world.pix_height - 1
					-chunk_y) + y_in_chunk)
			* minimap->bigmap.line_len;
		x_in_chunk = -1;
		while (++x_in_chunk < minimap->bigmap_size_ratio)
		{
			*(int *)addr = color;
			addr += minimap->bigmap.opp;
		}
	}
}

/**
 * @brief used when displaying the bigmap, puts a cicle on the window centered
 *		arround the player position
 * 
 * @param disp 
 * @param minimap 
 * @param settings 
 * @param player 
 */
void	maps_bigmap_put_player_window(t_display *disp, t_minimap *minimap,
	t_settings *settings, t_player *player)
{
	if (minimap->bigmap_size_ratio == -1)
		return ;
	_maps_bigmap_put_circle_window(disp,
		(t_coord_i){minimap->bigmap_offset_x + (int)(minimap->bigmap_size_ratio
			* player->p_co.x), minimap->bigmap_offset_y
		+ (int)(minimap->bigmap_size_ratio * (minimap->world.pix_height
				- player->p_co.y))}, settings->bigmap_player_size / 2,
		MINIMAP_COLOR_PLAYER);
}

/**
 * @brief draws a disc of a given radius arround the given center
 * 
 * @param data 
 * @param center 
 * @param radius 
 * @param color 
 */
static void	_maps_bigmap_put_circle_window(t_display *disp, t_coord_i center,
	int radius, int color)
{
	register int	x;
	register int	y;
	register int	radius_pow2;

	radius_pow2 = radius * radius;
	y = -radius - 1;
	while (++y <= radius)
	{
		if (center.y + y >= 0 && center.y + y < WIN_HEIGHT)
		{
			x = -radius - 1;
			while (++x < radius)
			{
				if (center.x + x >= 0 && center.x + x < WIN_WIDTH
					&& x * x + y * y <= radius_pow2)
					mlx_pixel_put(disp->mlx, disp->win, center.x + x,
						center.y + y, color);
			}
		}
	}
}

#endif