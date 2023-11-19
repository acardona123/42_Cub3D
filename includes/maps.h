/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:46:27 by acardona          #+#    #+#             */
/*   Updated: 2023/11/14 21:20:25 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H

# include "shared.h"

// maps_main.c
void	maps_draw_minimap(t_general *gen);

// maps_tools_minimap.c
int		maps_get_pixel_color_minimap(t_general *gen, int x_map, int y_map);

// maps_tools_bigmap.c
void	maps_bigmap_draw_chunk(t_minimap *minimap, int chunk_x, int chunk_y);
void	maps_bigmap_put_player_window(t_display *disp, t_minimap *minimap,
			t_settings *settings, t_player *player);

// maps_update_world.c
void	maps_world_update_door(t_general *gen, t_chunk *chunk);
int		maps_world_get_chunk_color(t_minimap *minimap, int map_height,
			int chunk_x, int chunk_y);

#endif