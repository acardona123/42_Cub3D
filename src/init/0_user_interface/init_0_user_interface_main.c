/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0_user_interface_main.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 02:21:33 by acardona          #+#    #+#             */
/*   Updated: 2023/12/06 02:38:29 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static t_bool	_in_0_display_elements_init(t_display *disp);
static bool		_in_0_check_screen_dimension_valid_ok(void *mlx);

#ifdef BONUS

/**
 * @brief initializes the t_display structure that corresponds to the ui
 *			(window + hooks + images + hooks)
 * 
 * @param gen 
 * @return EXIT on errors 
 */
void	in_0_init_display(t_general *gen)
{
	if (_in_0_display_elements_init(&gen->disp) == FAIL)
		end_destroy_exit(gen, EXIT_INIT_1);
	mlx_mouse_move(gen->disp.mlx, gen->disp.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	in_0_hooks_init(gen);
}

#else

/**
 * @brief initializes the t_display structure that corresponds to the ui
 *			(window + hooks + images + hooks)
 * 
 * @param gen 
 * @return EXIT on errors 
 */
void	in_0_init_display(t_general *gen)
{
	if (_in_0_display_elements_init(&gen->disp) == FAIL)
		end_destroy_exit(gen, EXIT_INIT_1);
	in_0_hooks_init(gen);
}

#endif

/**
 * @brief initializes the t_display struct (mlx, window and empty buffer image)
 * 
 * @param disp genereal structure to init
 * @return SUCCESS if the initialisation was successfull
 * @return FAIL if init error: nothing allocated/freed and error msg displayed
 */
static t_bool	_in_0_display_elements_init(t_display *disp)
{
	disp->mlx = mlx_init();
	if (!disp->mlx)
		return (to_error_msg(MSG_MLX_INIT), FAIL);
	if (_in_0_check_screen_dimension_valid_ok(disp->mlx) == false)
		return (to_error_msg(MSG_SETTINGS_DIMENSION), FAIL);
	mlx_do_key_autorepeatoff(disp->mlx);
	disp->win = mlx_new_window(disp->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (!disp->win)
		return (to_error_msg(MSG_MLX_NEW_IMG), FAIL);
	mlx_string_put(disp->mlx, disp->win, 5, 10, 0xFFFFFF,
		"Loading textures...");
	disp->buff = ft_calloc(1, sizeof(t_data));
	if (!disp->buff)
		return (to_error_msg(MSG_BAD_ALLOC), FAIL);
	if (to_mlx_new_empty_img(disp->mlx, disp->buff, WIN_WIDTH, WIN_HEIGHT)
		== FAIL)
		return (FAIL);
	disp->img_out_map = ft_calloc(1, sizeof(t_data));
	if (!disp->img_out_map)
		return (to_error_msg(MSG_BAD_ALLOC), FAIL);
	if (to_mlx_new_empty_img(disp->mlx, disp->img_out_map, WIN_WIDTH,
			WIN_HEIGHT) == FAIL)
		return (FAIL);
	disp->render_selec = RENDER_INGAME;
	return (SUCCESS);
}

static bool	_in_0_check_screen_dimension_valid_ok(void *mlx)
{
	int	x;
	int	y;

	mlx_get_screen_size(mlx, &x, &y);
	if (WIN_WIDTH < 1 || WIN_HEIGHT < 1 || WIN_WIDTH > x || WIN_HEIGHT > y)
		return (false);
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
