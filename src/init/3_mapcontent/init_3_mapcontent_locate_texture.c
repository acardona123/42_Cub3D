/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_locate_texture.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:55:56 by acardona          #+#    #+#             */
/*   Updated: 2023/10/02 16:12:33 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

/**
 * @brief fills the textures array of a chunk to point to each of its
 *	faces' textures
 * 
 * @param texturepack 
 * @param chunk_textures_array 
 * @param chunk_type 
 */
void	in_3_map_locate_textures(t_texture_pack *texturepack,
	t_animated_texture *chunk_textures_array[], char chunk_type)
{
	
	chunk_textures_array[FACE_N] = texturepack->wall_s;
	chunk_textures_array[FACE_S] = texturepack->wall_s;
	chunk_textures_array[FACE_E] = texturepack->wall_s;
	chunk_textures_array[FACE_W] = texturepack->wall_s;
	if (chunk_type == WALL)
	{
		chunk_textures_array[FACE_N] = texturepack->wall_n;
		chunk_textures_array[FACE_S] = texturepack->wall_s;
		chunk_textures_array[FACE_E] = texturepack->wall_e;
		chunk_textures_array[FACE_W] = texturepack->wall_w;
	}
	
	else if (chunk_type == DOOR)
		chunk_textures_array[FACE_N] = texturepack->door_front;
}
