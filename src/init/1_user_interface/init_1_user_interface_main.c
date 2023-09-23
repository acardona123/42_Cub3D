/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1_user_interface_main.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 02:21:33 by acardona          #+#    #+#             */
/*   Updated: 2023/09/23 02:38:21 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static bool	_in_1_display_elements_init(t_display *disp);

/**
 * @brief initialize the t_display structure that corresponds to the ui
 *			(window + hooks)
 * 
 * @param gen 
 * @return EXIT on errors 
 */
void	in_1_init_display(t_general *gen)
{
	if (_in_1_display_elements_init(&gen->disp))
		end_destroy_exit(gen, EXIT_INIT_1);
	in_1_hooks_init(gen);
}

/**
 * @brief initializes the t_display struct (mlx, window and empty buffer image)
 * 
 * @param disp genereal structure to init
 * @return true if the initialisation was successfull
 * @return false if init error: nothing allocated/freed and error msg displayed
 */
static bool	_in_1_display_elements_init(t_display *disp)
{
	disp->mlx = mlx_init();
	if (!disp->mlx)
	{
		to_error_msg("mlx_init faillure");
		return (false);
	}
	disp->win = mlx_new_window(disp->win, 0, 0, WIN_NAME);
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

static void	in_1_keybinds(t_display *disp)
{
}
