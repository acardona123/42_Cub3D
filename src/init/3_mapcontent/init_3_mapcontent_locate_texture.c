/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_locate_texture.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:55:56 by acardona          #+#    #+#             */
/*   Updated: 2023/11/02 22:17:34 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

static void	_in_3_set_texture(t_animated_texture **dest,
				t_animated_texture *to_insert);

/**
 * @brief fills the textures array of a chunk to point to each of its
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
t_bool	in_3_map_add_locate_textures(t_texture_pack *texturepack,
	t_animated_texture *chunk_textures_array[], char chunk_type)
{
	static bool	check_texture_done = false;

	if (chunk_type == WALL || chunk_type == NOTHING)
	{
		_in_3_set_texture(&chunk_textures_array[FACE_N], texturepack->wall_n);
		_in_3_set_texture(&chunk_textures_array[FACE_S], texturepack->wall_s);
		_in_3_set_texture(&chunk_textures_array[FACE_E], texturepack->wall_e);
		_in_3_set_texture(&chunk_textures_array[FACE_W], texturepack->wall_w);
	}
	else if (chunk_type == DOOR)
	{
		if (!check_texture_done && !texturepack->door_front)
			return (to_error_msg(MSG_TEXTURE_MISSING_DOOR_F), FAIL);
		if (!check_texture_done && (!texturepack->door_side_close
				|| !texturepack->door_side_open_opened || !texturepack
				->door_side_open_opening || !texturepack->door_side_open_closed
				|| !texturepack->door_side_open_closing))
			return (to_error_msg(MSG_TEXTURE_MISSING_DOOR_S), FAIL);
		check_texture_done = true;
		chunk_textures_array[FACE_N] = texturepack->door_front;
		chunk_textures_array[FACE_S] = texturepack->door_front;
		chunk_textures_array[FACE_E] = texturepack->door_front;
		chunk_textures_array[FACE_W] = texturepack->door_front;
	}
	return (SUCCESS);
}

/**
 * @brief Modifies the textures of the blocks adjacents to the door
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
		map[door_x - 1][door_y].textures[FACE_E] = textures->door_side_close;
		map[door_x + 1][door_y].textures[FACE_W]
			= textures->door_side_open_closed;
	}
	else
	{
		map[door_x][door_y - 1].textures[FACE_N] = textures->door_side_close;
		map[door_x][door_y + 1].textures[FACE_S]
			= textures->door_side_open_closed;
	}
}

/**
 * @brief ad to_insert animated texture pointer in *dest ONLY id*dest is NULL.
 *	Necessary as some chunks (as doors) can affect their surronding chunk
 *	texture, and therefore initiate a part of them before the chunk is fully
 *	initiated
 * 
 * @param to_insert 
 * @param dest 
 */
static void	_in_3_set_texture(t_animated_texture **dest,
	t_animated_texture *to_insert)
{
	if (*dest)
		return ;
	*dest = to_insert;
}

#else

/**
 * @brief fills the textures array of a chunk to point to each of its
 *	faces' textures
 * 
 * @param texturepack 
 * @param chunk_textures_array 
 * @param chunk_type 
 */
t_bool	in_3_map_add_locate_textures(t_texture_pack *texturepack,
	t_animated_texture *chunk_textures_array[], char chunk_type)
{
	if (chunk_type == WALL || chunk_type == NOTHING)
	{
		chunk_textures_array[FACE_N] = texturepack->wall_n;
		chunk_textures_array[FACE_S] = texturepack->wall_s;
		chunk_textures_array[FACE_E] = texturepack->wall_e;
		chunk_textures_array[FACE_W] = texturepack->wall_w;
	}
	return (SUCCESS);
}

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
