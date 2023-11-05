/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:32:02 by acardona          #+#    #+#             */
/*   Updated: 2023/11/05 01:13:31 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "shared.h"

//raycasting_frame_build.c
void				*rc_raycasting_frame_build(t_general *gen,
						size_t last_time);

// raycasting_use_texture.c
void				r_update_texture(t_texture_pack *texture_pack,
						t_map *map, t_hitpoint *hit_point, size_t time);
t_static_texture	*r_get_column_texture(t_animated_texture *texture,
						size_t time, size_t t0);
int					r_get_pixel_color(t_chunk *chunk, t_hitpoint *hit_pt,
						long int height, t_static_texture *texture);

#endif