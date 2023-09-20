/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:25:53 by acardona          #+#    #+#             */
/*   Updated: 2023/09/18 19:19:38 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	looping(void *elem)
{
	char	c;

	(void)elem;
	c = 'a';
	read(STDIN_FILENO, &c, 1);
	write(1, &c, 1);
	return (0);
}

int	main( void )
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 200, 200, "toto");
	mlx_loop_hook(mlx, &looping, NULL);
	mlx_loop(mlx);
	return (0);
}
