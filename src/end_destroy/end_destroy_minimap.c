/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_destroy_minimap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:11:12 by acardona          #+#    #+#             */
/*   Updated: 2023/11/15 14:21:34 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/end_destroy.h"

void	end_destroy_minimap(void *mlx, t_minimap *minimap)
{
	if (minimap->world.img)
		mlx_destroy_image(mlx, minimap->world.img);
	if (minimap->bigmap.img)
		mlx_destroy_image(mlx, minimap->bigmap.img);
	*minimap = (t_minimap){0};
}
