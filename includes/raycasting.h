/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:32:02 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 20:36:24 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "shared.h"

//raycasting_frame_build.c
void				*rc_raycasting_frame_build(t_general *gen,
						size_t last_time);

// raycasting_use_texture.c
t_static_texture	*r_get_texture_of_column(t_map *map, t_hitpoint *hitpoint,
						size_t time_now);
int					r_get_pixel_color(t_chunk *chunk, t_hitpoint *hit_pt,
						long int height, t_static_texture *texture);

#endif