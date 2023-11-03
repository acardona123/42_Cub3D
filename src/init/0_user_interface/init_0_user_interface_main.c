/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0_user_interface_main.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 02:21:33 by acardona          #+#    #+#             */
/*   Updated: 2023/11/03 04:14:04 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static t_bool	_in_0_display_elements_init(t_display *disp);
static t_bool	_in_0_display_empty_img_init(void *mlx, t_data **img_dst);

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
		return (to_error_msg("mlx_init faillure"), FAIL);
	disp->win = mlx_new_window(disp->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (!disp->win)
		return (to_error_msg("mlx_new_window faillure"), FAIL);
	if (_in_0_display_empty_img_init(disp->mlx, &disp->buff) == FAIL)
		return (FAIL);
	if (_in_0_display_empty_img_init(disp->mlx, &disp->img_out_map) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief used to initialise an empty image of the size of the window
 * 
 * @param mlx 
 * @return SUCCESS if success 
 * @return FAIL if faillure (err msg displayed)
 */
static t_bool	_in_0_display_empty_img_init(void *mlx, t_data **img_dst)
{
	*img_dst = ft_calloc(1, sizeof(t_data));
	if (!*img_dst)
		return (to_error_msg("Mem allocation error in display init"), FAIL);
	(*img_dst)->img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!(*img_dst)->img)
		return (to_error_msg("mlx_new_image faillure"), FAIL);
	(*img_dst)->addr = mlx_get_data_addr((*img_dst)->img, &(*img_dst)->opp,
			&(*img_dst)->line_len, &(*img_dst)->endian);
	(*img_dst)->opp /= 8;
	(*img_dst)->pix_height = WIN_HEIGHT;
	(*img_dst)->pix_width = WIN_WIDTH;
	return (SUCCESS);
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