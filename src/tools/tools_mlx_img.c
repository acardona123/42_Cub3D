/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_mlx_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:31:48 by acardona          #+#    #+#             */
/*   Updated: 2023/12/02 20:42:44 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

/**
 * @brief used to initialise an empty image of the given dimensions
 * 
 * @param mlx 
 * @param img_dst 
 * @param width 
 * @param height 
 * @return SUCCESS if success 
 * @return FAIL if faillure (err msg displayed)
 */
t_bool	to_mlx_new_empty_img(void *mlx, t_data *img_dst, int width, int height)
{
	img_dst->img = mlx_new_image(mlx, width, height);
	if (!img_dst->img)
		return (to_error_msg(MSG_MLX_NEW_IMG), FAIL);
	img_dst->addr = mlx_get_data_addr(img_dst->img, &img_dst->opp,
			&img_dst->line_len, &img_dst->endian);
	img_dst->opp /= 8;
	img_dst->pix_height = height;
	img_dst->pix_width = width;
	return (SUCCESS);
}

/**
 * @brief draws a monochrom rectangle on a given image, starting with its top
 *	left corner at the given position
 * 
 * @param data 
 * @param position 
 * @param dimensions 
 * @param color
 */
void	to_mlx_draw_rectangle(t_data *data, t_coord_i position,
	t_coord_i dimensions, int color)
{
	int		y;
	int		width;
	char	*addr;

	y = 0;
	while (dimensions.y)
	{
		addr = data->addr + (y + position.y) * data->line_len
			+ position.x * data->opp;
		width = dimensions.x + 1;
		while (--width)
		{
			*(int *)addr = color;
			addr += data->opp;
		}
		--dimensions.y;
		++y;
	}
}

/**
 * @brief draws a colored disc of a given radius arround the given center
 * 
 * @param data 
 * @param center 
 * @param radius 
 * @param color 
 */
void	to_mlx_draw_circle(t_data *data, t_coord_i center, int radius,
	int color)
{
	register int	x;
	register int	y;
	register int	radius_pow2;
	char			*addr;

	radius_pow2 = radius * radius;
	y = -radius - 1;
	while (++y <= radius)
	{
		if (center.y + y >= 0 && center.y + y < data->pix_height)
		{
			addr = data->addr + (y + center.y) * data->line_len
				+ (center.x - radius) * data->opp;
			x = -radius - 1;
			while (++x < radius)
			{
				if (center.x + x >= 0 && center.x + x < data->pix_width
					&& x * x + y * y <= radius_pow2)
					*(int *)addr = color;
				addr += data->opp;
			}
		}
	}
}

/**
 * @brief draw horizontal line
 * 
 * @param mlx 
 * @param win 
 * @param co 
 * @param len number of pixels 
 */
void	to_mlx_draw_line_h(void *mlx, void *win, t_coord_i co, int len)
{
	while (--len >= 0)
		mlx_pixel_put(mlx, win, co.x++, co.y, 0xff0000);
}

/**
 * @brief display on the mlx window a string if the function have mlx pointers
 * 
 * @param ptr 
 * @param co 
 */
void	to_mlx_str_put(void *ptr, int x, int y)
{
	static void	*mlx = 0;
	static void	*win = 0;

	if (!mlx)
	{
		mlx = ptr;
		return ;
	}
	if (!win)
	{
		win = ptr;
		return ;
	}
	mlx_string_put(mlx, win, x, y, 0xFFFFFF, (char *)ptr);
}
