/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_static_texture.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 02:20:26 by acardona          #+#    #+#             */
/*   Updated: 2023/10/20 10:59:19 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static t_bool	_in_2_static_texture_init_one_check_path(char *path);

/**
 * @brief fills a t_static_texture based on a given path
 * 
 * @param mlx 
 * @param texture ptr to the texture to fill
 * @param path path of the img used as a texture
 * @return SUCCESS no arg freed, /!\ path not deepcopied
 * @return FAIL: err msg displayed, texture->path=NULL, no arg freed
 */
t_bool	in_2_static_texture_init_one(void *mlx, t_static_texture *texture,
	char *path)
{
	if (_in_2_static_texture_init_one_check_path(path) == FAIL)
		return (FAIL);
	if (texture->path != path)
		texture->path = path;
	texture->data.img = mlx_xpm_file_to_image(mlx, path, &texture->img_width,
			&texture->img_height);
	if (!texture->data.img)
	{
		to_error_msg(MSG_BAD_XPM_TO_IMG);
		texture->path = NULL;
		return (FAIL);
	}
	texture->data.addr = mlx_get_data_addr(texture->data.img,
			&texture->data.opp, &texture->data.line_len,
			&texture->data.endian);
	texture->data.opp /= 8;
	texture->data.pix_height = texture->img_height;
	texture->data.pix_width = texture->img_width;
	return (SUCCESS);
}

/**
 * @brief checks if the given path leads to a readable .xpm file
 * 
 * @param path 
 * @return SUCCESS
 * @return FAIL FAIL, err msg dixplay, no arg freed
 */
static t_bool	_in_2_static_texture_init_one_check_path(char *path)
{
	int	fd_tmp;

	if (ft_strlen(path) < 4 || ft_strcmp(path + ft_strlen(path) - 4, ".xpm"))
		return (to_error_msg(MSG_ACCEPT_ONLY_XPM), FAIL);
	fd_tmp = open(path, O_RDWR);
	if (fd_tmp == -1)
		return (to_error_msg(MSG_ERR_OPEN_TEXTURE), FAIL);
	close(fd_tmp);
	return (SUCCESS);
}
/*
int main(void)
{
	t_general			gen;
	char				*path = "textures/random_texture.xpm";
	t_static_texture	texture;

	gen = (t_general){0};
	in_0_init_display(&gen);
	texture = (t_static_texture){0};
	printf("init texture:\n");
	in_2_static_texture_init_one(gen.disp.mlx, &texture, path);
	printf("img:%p\n", texture.data.img);
	printf("addr:%p\n", texture.data.addr);
	printf("opp: %d\n", texture.data.opp);
	printf("line_len: %d\n", texture.data.line_len);
	printf("pix_w: %d\n", texture.data.pix_width);
	printf("pix_h: %d\n", texture.data.pix_height);
	printf("img_w: %d\n", texture.img_width);
	printf("img_h: %d\n", texture.img_height);
	mlx_put_image_to_window(gen.disp.mlx, gen.disp.win, texture.data.img, 0, 0);
	// mlx_loop(gen.disp.mlx);
	// printf("end_loop\n");
	
	mlx_destroy_image(gen.disp.mlx, texture.data.img);
	end_destroy_exit(&gen, 0);
	return 0;
}
*/
