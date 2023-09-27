/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_static_texture.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 02:20:26 by acardona          #+#    #+#             */
/*   Updated: 2023/09/27 03:01:15 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static bool	_in_2_static_texture_init_one_check_path(char *path);

bool	in_2_static_texture_init_one(void *mlx, t_static_texture *texture,
	char *path)
{
	if (_in_2_static_texture_init_one_check_path(path) == false)
		return (false);
	texture->path = path;
	texture->data.img = mlx_xpm_file_to_image(mlx, path, &texture->img_width,
			&texture->img_height);
	if (!texture->data.img)
		return (to_error_msg("mlx .xpm conversion fail"), false);
	texture->data.addr = mlx_get_data_addr(texture->data.img,
			&texture->data.opp, &texture->data.line_length,
			&texture->data.endian);
	texture->data.opp /= 8;
	texture->data.pix_height = texture->img_height;
	texture->data.pix_width = texture->img_width;
	return (true);
}

/**
 * @brief checks if the given path leads to a readable .xpm file
 * 
 * @param path 
 * @return true SUCCESS
 * @return false FAIL, err msg dixplay, no arg freed
 */
static bool	_in_2_static_texture_init_one_check_path(char *path)
{
	int	fd_tmp;

	if (ft_strlen(path) < 4 || ft_strcmp(path + ft_strlen(path) - 4, ".xpm"))
		return (to_error_msg("To avoid mlx leaks this program can only \
handle .xpm images as textures, sorry"), false);
	fd_tmp = open(path, O_RDWR);
	if (fd_tmp == -1)
		return (to_error_msg("Texture file not reachable/readable"), false);
	close(fd_tmp);
	return (true);
}
