/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_destroy_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:51:16 by acardona          #+#    #+#             */
/*   Updated: 2023/11/03 04:16:43 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shared.h"

void	end_destroy_map(t_map *map)
{
	int	x;
	int	y;

	if (!map || !map->map)
		return ;
	x = -1;
	while (++x < map->width)
	{
		if (map->map[x])
		{
			y = -1;
			while (++y < map->height)
			{
				if (map->map[x][y].action)
				{
					ft_try_free((void **)&map->map[x][y].action->targets);
					free(map->map[x][y].action);
				}
			}
			free(map->map[x]);
		}
		else
			break ;
	}
	free(map->map);
}
