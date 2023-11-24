/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_hide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 21:32:00 by acardona          #+#    #+#             */
/*   Updated: 2023/11/24 04:28:24 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include <unistd.h>
#include <stdlib.h>

//cc mlx_mouse_hide.c -Lmlx -lmlx -lXext -lX11

int	main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 10, 10, "");
	mlx_mouse_hide(mlx, win);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}
