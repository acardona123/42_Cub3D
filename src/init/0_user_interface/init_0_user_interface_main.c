/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0_user_interface_main.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 02:21:33 by acardona          #+#    #+#             */
/*   Updated: 2023/09/28 12:59:42 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static bool	_in_0_display_elements_init(t_display *disp);

/**
 * @brief initialize the t_display structure that corresponds to the ui
 *			(window + hooks)
 * 
 * @param gen 
 * @return EXIT on errors 
 */
void	in_0_init_display(t_general *gen)
{
	if (_in_0_display_elements_init(&gen->disp) == false)
		end_destroy_exit(gen, EXIT_INIT_1);
	in_0_hooks_init(gen);
}

/**
 * @brief initializes the t_display struct (mlx, window and empty buffer image)
 * 
 * @param disp genereal structure to init
 * @return true if the initialisation was successfull
 * @return false if init error: nothing allocated/freed and error msg displayed
 */
static bool	_in_0_display_elements_init(t_display *disp)
{
	disp->mlx = mlx_init();
	if (!disp->mlx)
	{
		to_error_msg("mlx_init faillure");
		return (false);
	}
	disp->win = mlx_new_window(disp->mlx, WIN_WIDTH, WIN_HIGHT, WIN_NAME);
	if (!disp->win)
	{
		to_error_msg("mlx_new_window faillure");
		mlx_destroy_display(disp->mlx);
		return (false);
	}
	disp->buff = mlx_new_image(disp->mlx, WIN_WIDTH, WIN_HIGHT);
	if (!disp->buff)
	{
		to_error_msg("mlx_new_image faillure");
		mlx_destroy_window(disp->mlx, disp->win);
		mlx_destroy_display(disp->mlx);
		return (false);
	}
	return (true);
}

/*
int main(void)
{
	t_static_texture	texture;
	t_general			gen;

	texture = (t_static_texture){0};
	gen = (t_general){0};
	in_0_init_display(&gen);
	printf("Disp init\n");
	mlx_loop(gen.disp.mlx);
	return 0;
}
*/