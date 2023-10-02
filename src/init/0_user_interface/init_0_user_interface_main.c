/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0_user_interface_main.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 02:21:33 by acardona          #+#    #+#             */
/*   Updated: 2023/10/02 04:45:16 by acardona         ###   ########.fr       */
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

// static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_len + x * (data->opp));
// 	*(unsigned int*)dst = color;
// }

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
		return (to_error_msg("mlx_init faillure"), false);
	disp->win = mlx_new_window(disp->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (!disp->win)
		return (to_error_msg("mlx_new_window faillure"), false);
	disp->buff = calloc(1, sizeof(t_data));
	if (!disp->buff)
		return (to_error_msg("Mem allocation error in display init"), false);
	disp->buff->img = mlx_new_image(disp->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!disp->buff->img)
		return (to_error_msg("mlx_new_image faillure"), false);
	disp->buff->addr = mlx_get_data_addr(disp->buff->img, &disp->buff->opp,
			&disp->buff->line_len, &disp->buff->endian);
	disp->buff->opp /= 8;
	disp->buff->pix_height = WIN_HEIGHT;
	disp->buff->pix_width = WIN_WIDTH;
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