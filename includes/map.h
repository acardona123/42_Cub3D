/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:46:27 by acardona          #+#    #+#             */
/*   Updated: 2023/11/13 16:25:19 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "shared.h"

// map_main.c
void	map_draw_minimap(t_general *gen);
void	map_draw_bigmap(t_general *gen);

// map_get_pixel_color.c
int		map_get_pixel_color(t_general *gen, t_map_type type, int x_map,
			int y_map);

// map_update_world.c
void	map_update_world_door(t_general *gen, t_chunk *chunk);

#endif