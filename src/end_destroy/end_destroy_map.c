/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_destroy_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:51:16 by acardona          #+#    #+#             */
/*   Updated: 2023/11/01 19:15:22 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shared.h"

void	end_destroy_map(t_map *map)
{
	int	x;

	if (!map || !map->map)
		return ;
	x = 0;
	while (x < map->width)
	{
		if (map->map[x])
			free(map->map[x]);
		else
			break ;
		x++;
	}
	free(map->map);
}
