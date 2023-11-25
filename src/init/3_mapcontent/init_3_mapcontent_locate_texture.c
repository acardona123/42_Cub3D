/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_locate_texture.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:55:56 by acardona          #+#    #+#             */
/*   Updated: 2023/11/23 19:41:25 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

/**
 * @brief fills the textures arrays of a chunk to point to each of its
 *	faces' textures. If it is the first time that a door is found, checks if all
 *	doors textures are availables (ie defined in the map)
 * 
 * @param texturepack 
 * @param chunk_textures_array 
 * @param chunk_type 
 * @return t_bool	SUCCESS if texture succesfully associated to each face
 *					FAIL if a requiered texture (of the bonus elements, here a
 *					door) is missing.
 */
t_bool	in_3_map_set_chunk_textures(t_texture_pack *texturepack,
	t_chunk *chunk)
{
	static bool	check_texture_done = false;

	if (chunk->type == WALL || chunk->type == NOTHING)
	{
		init_chunk_set_texture(chunk, FACE_N, &texturepack->wall_n, true);
		init_chunk_set_texture(chunk, FACE_S, &texturepack->wall_s, true);
		init_chunk_set_texture(chunk, FACE_E, &texturepack->wall_e, true);
		init_chunk_set_texture(chunk, FACE_W, &texturepack->wall_w, true);
	}
	else if (chunk->type == DOOR)
	{
		if (!check_texture_done && !texturepack->door_front.group_len)
			return (to_error_msg(MSG_TEXTURE_MISSING_DOOR_F), FAIL);
		if (!check_texture_done && (!texturepack->door_side_close.group_len
				|| !texturepack->door_side_open_opened.group_len
				|| !texturepack ->door_side_open_opening.group_len
				|| !texturepack->door_side_open_closed.group_len
				|| !texturepack->door_side_open_closing.group_len))
			return (to_error_msg(MSG_TEXTURE_MISSING_DOOR_S), FAIL);
		init_chunk_set_texture(chunk, FACE_N, &texturepack->door_front, true);
		init_chunk_set_texture(chunk, FACE_S, &texturepack->door_front, true);
		init_chunk_set_texture(chunk, FACE_E, &texturepack->door_front, true);
		init_chunk_set_texture(chunk, FACE_W, &texturepack->door_front, true);
	}
	return ((chunk->type == DOOR && (check_texture_done = true)), SUCCESS);
}

/**
 * @brief Modifies the textures of the two opposit walls adjacent to the door
 * 
 * @param map 
 * @param textures 
 * @param door_x 
 * @param door_y 
 */
void	in_3_map_add_door_sides_textures(t_chunk **map,
	t_texture_pack *textures, int door_x, int door_y)
{
	if (map[door_x - 1][door_y].type == WALL
		&& map[door_x + 1][door_y].type == WALL)
	{
		init_chunk_set_texture(&map[door_x - 1][door_y], FACE_E,
			&textures->door_side_close, 0);
		init_chunk_set_texture(&map[door_x + 1][door_y], FACE_W,
			&textures->door_side_open_closed, 0);
	}
	else
	{
		init_chunk_set_texture(&map[door_x][door_y - 1], FACE_N,
			&textures->door_side_close, 0);
		init_chunk_set_texture(&map[door_x][door_y + 1], FACE_S,
			&textures->door_side_open_closed, 0);
	}
}

#else

/**
 * @brief fills the textures arrays of a chunk to point to each of its
 *	faces' textures
 * 
 * @param texturepack 
 * @param chunk_textures_array 
 * @param chunk_type 
 */
t_bool	in_3_map_set_chunk_textures(t_texture_pack *texturepack,
	t_animated_texture *chunk_textures_array[], char chunk_type)
{
	if (chunk_type == WALL || chunk_type == NOTHING)
	{
		init_chunk_set_texture(chunk, FACE_N, &texturepack->wall_n, true);
		init_chunk_set_texture(chunk, FACE_S, &texturepack->wall_s, true);
		init_chunk_set_texture(chunk, FACE_E, &texturepack->wall_e, true);
		init_chunk_set_texture(chunk, FACE_W, &texturepack->wall_w, true);
	}
	return (SUCCESS);
}

#endif
