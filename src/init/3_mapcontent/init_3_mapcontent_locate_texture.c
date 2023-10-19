/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_locate_texture.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:55:56 by acardona          #+#    #+#             */
/*   Updated: 2023/10/20 01:04:02 by acardona         ###   ########.fr       */
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
t_bool	in_3_map_locate_textures(t_texture_pack *texturepack,
	t_animated_texture *chunk_textures_array[], char chunk_type)
{
	if (chunk_type == WALL)
	{
		chunk_textures_array[FACE_N] = texturepack->wall_n;
		chunk_textures_array[FACE_S] = texturepack->wall_s;
		chunk_textures_array[FACE_E] = texturepack->wall_e;
		chunk_textures_array[FACE_W] = texturepack->wall_w;
	}
	else if (chunk_type == DOOR)
	{
		if (!texturepack->door_front)
			return (to_error_msg(MSG_TEXTURE_MISSING_DOOR_F), FAIL);
		if (!texturepack->door_side)
			return (to_error_msg(MSG_TEXTURE_MISSING_DOOR_S), FAIL);
		chunk_textures_array[FACE_N] = texturepack->door_front;
		chunk_textures_array[FACE_S] = texturepack->door_front;
		chunk_textures_array[FACE_E] = texturepack->door_front;
		chunk_textures_array[FACE_W] = texturepack->door_front;
	}
	return (SUCCESS);
}

#ifdef BONUS

void	in_3_map_add_door_sides_textures(t_chunk **map,
	t_texture_pack *textures, int door_x, int door_y)
{
	if (map[door_x - 1][door_y].type == WALL
		&& map[door_x + 1][door_y].type == WALL)
	{
		map[door_x - 1][door_y].textures[FACE_E] = textures->door_side;
		map[door_x + 1][door_y].textures[FACE_W] = textures->door_side;
	}
	else
	{
		map[door_x][door_y - 1].textures[FACE_E] = textures->door_side;
		map[door_x][door_y + 1].textures[FACE_W] = textures->door_side;
	}
}

#else

void	in_3_map_add_door_sides_textures(t_chunk **map,
	t_texture_pack *textures, int door_x, int door_y)
{
	(void)map;
	(void)textures;
	(void)door_x;
	(void)door_y;
	return ;
}

#endif
