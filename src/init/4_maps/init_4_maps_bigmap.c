/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_4_maps_bigmap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:45:33 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 15:24:45 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

static t_bool	_in_4_bigmap_get_ratio(t_minimap *minimap, t_map *map);
static void		_in_4_bigmap_fill(t_minimap *minimap, t_map *map);

void	in_4_bigmap_init(t_general *gen)
{
	if (to_mlx_new_empty_img(gen->disp.mlx, &gen->minimap.bigmap, WIN_WIDTH,
			WIN_HEIGHT) == FAIL)
		end_destroy_exit(gen, EXIT_INIT_4);
	if (_in_4_bigmap_get_ratio(&gen->minimap, &gen->map) == FAIL)
		return ;
	_in_4_bigmap_fill(&gen->minimap, &gen->map);
}

/**
 * @brief adjusts the big map offsets and size_ratio as big as possible in the
 *		window size
 * 
 * @param minimap 
 * @param map 
 * @return t_bool	FAIL if the map is widder or taller than the window
 *						dimensions
 *					SUCCESS otherwise
 */
static t_bool	_in_4_bigmap_get_ratio(t_minimap *minimap, t_map *map)
{
	int	ratio_width;
	int	ratio_height;

	ratio_width = WIN_WIDTH / map->width;
	ratio_height = WIN_HEIGHT / map->height;
	if (ratio_width == 0 || ratio_height == 0)
	{
		to_warning_msg(MSG_WARNING_BIG_MAP);
		return (minimap->bigmap_size_ratio = -1, FAIL);
	}
	if (ratio_width < ratio_height)
	{
		minimap->bigmap_size_ratio = ratio_width;
		minimap->bigmap_offset_x = (WIN_WIDTH % map->width) / 2;
		minimap->bigmap_offset_y = (WIN_HEIGHT
				- ratio_width * map->height) / 2;
	}
	else
	{
		minimap->bigmap_size_ratio = ratio_height;
		minimap->bigmap_offset_x = (WIN_WIDTH
				- ratio_height * map->width) / 2;
		minimap->bigmap_offset_y = (WIN_HEIGHT % map->height) / 2;
	}
	return (SUCCESS);
}

/**
 * @brief draws all the chunks in the bigmap image
 * 
 * @param minimap 
 * @param map 
 */
static void	_in_4_bigmap_fill(t_minimap *minimap, t_map *map)
{
	int	x_world;
	int	y_world;

	to_mlx_draw_rectangle(&minimap->bigmap, (t_coord_i){0, 0}, (t_coord_i)
	{WIN_WIDTH, WIN_HEIGHT}, MINIMAP_COLOR_NOTHING);
	y_world = -1;
	while (++y_world < map->height)
	{
		x_world = -1;
		while (++x_world < map->width)
			maps_bigmap_draw_chunk(minimap, x_world, y_world);
	}
}

#endif
