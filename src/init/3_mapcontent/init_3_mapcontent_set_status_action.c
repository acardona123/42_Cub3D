/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_set_status_action.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:21:14 by acardona          #+#    #+#             */
/*   Updated: 2023/11/03 04:39:52 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

t_bool	_in_3_mapcontent_status_action_door(t_map *map, int x, int y);

/**
 * @brief goes through the map tp initialise the actions and status related to
 *		each chunk.
 * 
 * @param map 
 * @return t_bool	FAIL if malloc error, error msg displayed
 *					SUCCESS otherwise
 */
t_bool	in_3_mapcontent_status_action_init(t_map *map)
{
	int	x;
	int	y;

	x = -1;
	while (++x < map->width)
	{
		y = -1;
		while (++y < map->height)
		{
			if (map->map[x][y].type == DOOR
				&& _in_3_mapcontent_status_action_door(map, x, y) == FAIL)
				return (FAIL);
			else
				map->map[x][y].status = INACTIVE;
		}
	}
	return (SUCCESS);
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
t_bool	_in_3_mapcontent_status_action_door(t_map *map, int x, int y)
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
	if (map->map[x - 1][y].type == WALL && map->map[x + 1][y].type == WALL)
	{
		map->map[x][y].action->targets[TARGET_DOOR_SIDE] = &map->map[x + 1][y];
		map->map[x][y].action->active_faces = ACTIVE_N | ACTIVE_S;
		map->map[x][y].extra_data_i = DOOR_HORIZONTAL;
	}
	else
	{
		map->map[x][y].action->targets[TARGET_DOOR_SIDE] = &map->map[x][y + 1];
		map->map[x][y].action->active_faces = ACTIVE_E | ACTIVE_W;
		map->map[x][y].extra_data_i = DOOR_VERTICAL;
	}
	map->map[x][y].action->dist_range = DOOR_ACTION_DIST_RANGE;
	map->map[x][y].action->time_last_act = 0;
	map->map[x][y].action->execute = doors_action;
	return (SUCCESS);
}

#else

/**
 * @brief No action in the mandatory part
 * 
 * @param map 
 * @return t_bool SUCCESS allways
 */
t_bool	in_3_mapcontent_status_action_init(t_map *map)
{
	int	x;
	int	y;

	x = -1;
	while (++x < map->width)
	{
		y = -1;
		while (++y < map->height)
			map->map[x][y].status = INACTIVE;
	}
	return (SUCCESS);
}

#endif
