/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_fill_chunk.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:52:12 by acardona          #+#    #+#             */
/*   Updated: 2023/11/02 00:43:56 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static bool	_in_3_character_is_valid(t_general *gen, char letter, int x,
				int y);
static bool	_int_3_is_character_surrounding_ok(char c, t_map *map, int x,
				int y);

#ifdef BONUS

bool	in_3_map_content_fill_chunk_ok(t_general *gen, int c_type, int x, int y)
{
	if (!_in_3_character_is_valid(gen, c_type, x, y))
		return (false);
	gen->map.map[x][y].type = c_type;
	gen->map.map[x][y].t0 = to_getime() - rand() % 1000;
	if (in_3_map_locate_textures(&gen->textures, gen->map.map[x][y].textures,
		c_type) == FAIL)
		return (false);
	if (c_type == DOOR)
		gen->map.map[x][y].status = DOOR_CLOSED;
	else
		gen->map.map[x][y].status = INACTIVE;
	if (y < gen->map.y_max - 1 && gen->map.map[x][y + 1].type == DOOR)
		in_3_map_add_door_sides_textures(gen->map.map, &gen->textures,
			x, y + 1);
	return (true);
}

#else

bool	in_3_map_content_fill_chunk_ok(t_general *gen, int c_type, int x, int y)
{
	if (!_in_3_character_is_valid(gen, c_type, x, y))
		return (false);
	gen->map.map[x][y].type = c_type;
	gen->map.map[x][y].status = INACTIVE;
	gen->map.map[x][y].t0 = 0;
	in_3_map_locate_textures(&gen->textures, gen->map.map[x][y].textures,
		c_type);
	return (true);
}

#endif

/**
 * @brief checks if the character c is a valid one:
 *			- it is a symbole of a map element
 *			- it does not 'open' the map (any floor or player position chunk
 *				isn't in contact with a "nothing" chunk)
 *			- a door is at least surrounde by two opposit walls
 * @param type chunk type 
 * @return true if the character is properly placed
 * @return false if the character brokes any of the previous rules
 */
static bool	_in_3_character_is_valid(t_general *gen, char letter, int x,
	int y)
{
	static int	player_found = false;
	int			i;

	if (!ft_isinset(letter, CHARS_ALLOWED))
		return (to_error_msg(MSG_INVALID_CHAR), false);
	if (ft_isinset(letter, CHARS_PLAYER))
	{
		if (player_found == true)
			return (to_error_msg(MSG_MULTIPLE_PLAYER), false);
		i = -1;
		while (letter != CHARS_PLAYER[++i])
			gen->player.p_angle += M_PI / 2;
		gen->player.p_co.x = x + 0.5;
		gen->player.p_co.y = y + 0.5;
		player_found = true;
	}
	else if (x == gen->map.width - 1 && y == 0 && player_found == false)
		return (to_error_msg(MSG_NO_PLAYER), false);
	return (_int_3_is_character_surrounding_ok(letter, &gen->map, x, y));
}

#ifdef BONUS

/**
 * @brief check if necessary if the chunk is surrounded according to the subject
 *			(e.g : a floor/player can't be adjacent to a "nothing" chunk or door
 *				must be surrounded by at least 2 opposit wall).
 * 
 * @param gen 
 * @param x 
 * @param y 
 * @return true if the subject constraints are respected
 * @return false error msg displayed
 */
static bool	_int_3_is_character_surrounding_ok(char chunk_type, t_map *map,
	int x, int y)
{
	if (chunk_type == NOTHING)
	{
		if ((x != 0 && !ft_isinset(map->map[x - 1][y].type, CHARS_OBSTACLE))
			|| (y != map->height - 1 && !ft_isinset(map->map[x][y + 1].type,
			CHARS_OBSTACLE)))
			return (to_error_msg(MSG_MAP_NOT_CLOSED), false);
		return (true);
	}
	else if (chunk_type != WALL
		&& (x == 0 || x == map->width - 1 || y == 0 || y == map->height - 1 \
		|| map->map[x - 1][y].type == NOTHING
		|| map->map[x][y + 1].type == NOTHING))
		return (to_error_msg(MSG_MAP_NOT_CLOSED), false);
	else if (y < map->height - 1 && map->map[x][y + 1].type == DOOR
		&& !(map->map[x][y].type == WALL && map->map[x][y + 2].type == WALL)
		&& !(map->map[x + 1][y + 1].type == WALL
			&& map->map[x - 1][y + 1].type == WALL))
		return (to_error_msg(MSG_DOOR_ISOLATED), false);
	return (true);
}

#else

/**
 * @brief check if necessary if the chunk is surrounded according to the subject
 *			(e.g : a floor can't be adjacent to a "nothing" chunk).
 * 
 * @param gen 
 * @param x 
 * @param y 
 * @return SUCCESS if the subject constraints are respected
 * @return FAIL error msg displayed
 */
static bool	_int_3_is_character_surrounding_ok(char chunk_type, t_map *map,
	int x, int y)
{
	if (chunk_type == NOTHING)
	{
		if ((x != 0 && !ft_isinset(map->map[x - 1][y].type, CHARS_OBSTACLE))
			|| (y != map->height - 1 && !ft_isinset(map->map[x][y + 1].type,
			CHARS_OBSTACLE)))
			return (to_error_msg(MSG_MAP_NOT_CLOSED), false);
		return (true);
	}
	else if (chunk_type != WALL
		&& (x == 0 || x == map->width - 1 || y == 0 || y == map->height - 1 \
		|| map->map[x - 1][y].type == NOTHING
		|| map->map[x][y + 1].type == NOTHING))
		return (to_error_msg(MSG_MAP_NOT_CLOSED), false);
	return (true);
}

#endif