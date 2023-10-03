/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:05:10 by acardona          #+#    #+#             */
/*   Updated: 2023/10/03 18:48:58 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "shared.h"


//raycasting_frame_build.c
void		r_frame_construction(t_general *gen, size_t time);

//raycasting_collision.c
t_hitpoint	r_ray_collision(t_chunk_type type, t_coord_f P, float angle_ray,
				t_map *data);

#endif