/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_destroy_display.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:33:19 by acardona          #+#    #+#             */
/*   Updated: 2023/09/28 12:56:34 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shared.h"

/**
 * @brief distroys display elements (mlx, winndow and buffer image).
 *! /!\ BEFORE DESTROYING DISPLAY: ALL THE IMAGES, INCLUDING THE ONES IN THE
 *! TEXTURE PACK, MUST HAVE BEEN DESTROYED USING END_DESTROY_TEXTURE_PACK
 * 
 * @param disp pointer to the display structure containde by the t_global
 */
void	end_destroy_display(t_display *disp)
{
	if (disp->win)
		mlx_destroy_window(disp->mlx, disp->win);
	if (disp->buff)
		mlx_destroy_image(disp->mlx, disp->buff);
	if (disp->mlx)
	{
		mlx_destroy_display(disp->mlx);
		free(disp->mlx);
	}
	*disp = (t_display){0};
}
