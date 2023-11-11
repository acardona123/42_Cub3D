/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:45:44 by acardona          #+#    #+#             */
/*   Updated: 2023/11/11 23:56:00 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map.h"

void	map_draw_minimap(t_general *gen)
{
	register int	x_map;
	register int	y_map;
	register char	*addr;
	register int	i;
	register int	j;

	x_map = -1;
	while (++x_map < gen->settings.minimap_size)
	{
		addr = gen->disp.buff->addr + x_map * gen->disp.buff->opp
			+ (WIN_HEIGHT - gen->settings.minimap_size - 1) * gen->disp.buff->line_len;
		y_map = -1;
		while (++y_map < gen->settings.minimap_size)
		{
			// printf("(x_map, y_map) = (%d, %d)\n", x_map, y_map);//
			addr += gen->disp.buff->line_len;
			*((int *)addr) = map_get_pixel_color(gen, x_map, y_map);
		}
	}
	x_map = (gen->settings.minimap_size - gen->settings.minimap_zoom) >> 1;
	y_map = WIN_HEIGHT - ((gen->settings.minimap_size + gen->settings.minimap_zoom) >> 1);
	i = -1;
	while (++i < gen->settings.minimap_zoom)
	{
		j = -1;
		while (++j < gen->settings.minimap_zoom)
			*(int *)(gen->disp.buff->addr + (x_map + i) * gen->disp.buff->opp
					+ (y_map + j) * gen->disp.buff->line_len)
				= MINIMAP_COLOR_PLAYER;
	}
}

void	map_draw_bigmap(t_general *gen)
{
	(void)gen;
}
