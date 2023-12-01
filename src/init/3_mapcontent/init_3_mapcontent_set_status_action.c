/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_set_status_action.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:21:14 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 19:35:30 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

/**
 * @brief goes through the map to initialise the actions and status related to
 *		specific chunks as doors, leaks, crashes.
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
				&& in_3_mapcontent_door_status_action_init(map, x, y) == FAIL)
				return (FAIL);
			else if (ft_isinset(map->map[x][y].type, CHARS_LEAKS)
				&& in_3_mapcontent_leaks_action_init(map, x, y))
				return (FAIL);
			if (ft_isinset(map->map[x][y].type, CHARS_CRASHES)
				&& in_3_mapcontent_crashes_action_init(map, x, y) == FAIL)
				return (FAIL);
		}
	}
	return (SUCCESS);
}

#endif
