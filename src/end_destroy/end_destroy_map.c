/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_destroy_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:51:16 by acardona          #+#    #+#             */
/*   Updated: 2023/09/23 01:42:45 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shared.h"

void	end_destroy_map(t_map *map)
{
	int	x;

	x = 0;
	while (x < map->widht)
	{
		free(map->map[x]);
		x++;
	}
	free(map->map);
}