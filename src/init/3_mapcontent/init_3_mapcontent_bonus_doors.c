/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_bonus_doors.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 00:48:21 by acardona          #+#    #+#             */
/*   Updated: 2023/11/26 02:52:17 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

/**
 * @brief fills the textures arrays of a door chunk to point to each of its
 *	faces' textures. If it is the first time that a door is found, checks if all
 *	doors textures are availables (ie defined in the map)
 * 
 * @param texturepack 
 * @param chunk door chunk
 * @return t_bool FAIL if texture missing in the map
 */
t_bool	in_3_mapcontent_doors_chunk_init(t_texture_pack *texturepack,
	t_chunk *chunk_door)
{
	static bool	check_texture_done = false;

	if (!check_texture_done && !texturepack->door_front.group_len)
		return (to_error_msg(MSG_TEXTURE_MISSING_DOOR_F), FAIL);
	if (!check_texture_done && (!texturepack->door_side_close.group_len
			|| !texturepack->door_side_open_opened.group_len
			|| !texturepack ->door_side_open_opening.group_len
			|| !texturepack->door_side_open_closed.group_len
			|| !texturepack->door_side_open_closing.group_len))
		return (to_error_msg(MSG_TEXTURE_MISSING_DOOR_S), FAIL);
	check_texture_done = true;
	init_chunk_set_texture(chunk_door, FACE_N, &texturepack->door_front, true);
	init_chunk_set_texture(chunk_door, FACE_S, &texturepack->door_front, true);
	init_chunk_set_texture(chunk_door, FACE_E, &texturepack->door_front, true);
	init_chunk_set_texture(chunk_door, FACE_W, &texturepack->door_front, true);
	return (SUCCESS);
}

/**
 * @brief Modifies the textures of the two opposit walls adjacent to the door
 * 
 * @param map 
 * @param textures 
 * @param door_x 
 * @param door_y 
 */
void	in_3_door_add_sides_textures(t_chunk **map,
	t_texture_pack *textures, int door_x, int door_y)
{
	if (ft_isinset(map[door_x - 1][door_y].type, CHARS_WALLS)
		&& ft_isinset(map[door_x + 1][door_y].type, CHARS_WALLS))
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

/**
 * @brief initializes the door as closed and defines its action (targets: the
 *		door itself and the adjacent wall toward wich the door slides (its
 *		texture will be updated)
 * 
 * @param map 
 * @param x 
 * @param y 
 * @return t_bool	FAIL if malloc error, error msg displayed
 *					SUCCESS otherwise
 */
t_bool	in_3_mapcontent_door_status_action_init(t_map *map, int x, int y)
{
	map->map[x][y].status = DOOR_CLOSED;
	map->map[x][y].action = ft_calloc(1, sizeof(t_action));
	if (!map->map[x][y].action)
		return (to_error_msg(MSG_BAD_ALLOC), FAIL);
	map->map[x][y].action->targets = ft_calloc(2, sizeof(t_chunk *));
	if (!map->map[x][y].action->targets)
		return (to_error_msg(MSG_BAD_ALLOC), free(map->map[x][y].action),
			map->map[x][y].action = NULL, FAIL);
	map->map[x][y].action->targets[TARGET_DOOR_ITSELF] = &map->map[x][y];
	if (ft_isinset(map->map[x - 1][y].type, CHARS_WALLS)
		&& ft_isinset(map->map[x + 1][y].type, CHARS_WALLS))
	{
		map->map[x][y].action->targets[TARGET_DOOR_SIDE] = &map->map[x + 1][y];
		map->map[x][y].action->active_faces = ACTIVE_N | ACTIVE_S;
		map->map[x][y].extra_data_i = 1 << DOOR_HORIZONTAL;
	}
	else
	{
		map->map[x][y].action->targets[TARGET_DOOR_SIDE] = &map->map[x][y + 1];
		map->map[x][y].action->active_faces = ACTIVE_E | ACTIVE_W;
		map->map[x][y].extra_data_i = 1 << DOOR_VERTICAL;
	}
	map->map[x][y].action->dist_range = ACTION_DOOR_DIST_RANGE;
	map->map[x][y].action->time_last_act = 0;
	return (map->map[x][y].action->execute = gp_action_doors, SUCCESS);
}

#endif