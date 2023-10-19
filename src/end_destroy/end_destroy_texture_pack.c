/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_destroy_texture_pack.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:17:29 by acardona          #+#    #+#             */
/*   Updated: 2023/10/19 18:13:40 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shared.h"

static void	_end_textures_destroy_one_animated_texture(void *mlx,
				t_animated_texture *target);
static void	_end_textures_destroy_one_static_texture(void *mlx,
				t_static_texture *target);

/**
 * @brief frees and destroys all the texture elements of the texture pack.
 *			Can be used on a partially unitiallysed texture pack wich
 *			initialisation have been stoped due to an error
 * 
 * @param mlx pointer to the mlx
 * @param pack pointer toward general->textures
 */
void	end_destroy_texture_pack(void *mlx, t_texture_pack *pack)
{
	t_animated_texture	***textures;
	int					i;

	if (!pack)
		return ;
	textures = (t_animated_texture **[NUMBER_OF_TEXTURES]){&pack->wall_n,
		&pack->wall_s, &pack->wall_e, &pack->wall_w, &pack->door_front,
		&pack->door_side};
	i = -1;
	while (++i < NUMBER_OF_TEXTURES)
	{
		if (*textures[i])
		{
			_end_textures_destroy_one_animated_texture(mlx, *textures[i]);
			free(*textures[i]);
			*textures[i] = NULL;
		}
	}
}

/**
 * @brief destroys an animated texture with all its static textures use for
 *			animation
 * 
 * @param mlx 
 * @param target 
 */
static void	_end_textures_destroy_one_animated_texture(void *mlx,
	t_animated_texture *target)
{
	unsigned int	i;

	if (!target || !target->frame_array)
		return ;
	i = 0;
	while (target->frame_array && i < target->frame_number
		&& target->frame_array[i].path)
	{
		_end_textures_destroy_one_static_texture(mlx, &target->frame_array[i]);
		++i;
	}
	free(target->frame_array);
}

/**
 * @brief destroys a static texture <=> it's path, image and image address
 * 
 * @param mlx 
 * @param target 
 */
static void	_end_textures_destroy_one_static_texture(void *mlx,
	t_static_texture *target)
{
	if (!target)
		return ;
	free(target->path);
	if (target->data.img)
		mlx_destroy_image(mlx, target->data.img);
}

/*
#include "../../includes/init.h"
int main(void)
{
	t_general			gen;
	char				*path = ft_strdup("textures/random_texture.xpm");
	t_static_texture	texture;

	gen = (t_general){0};
	in_0_init_display(&gen);
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
	
	printf("avant\n");
	_end_textures_destroy_one_static_texture(gen.disp.mlx, &texture);
	printf("apres\n");
	// mlx_destroy_image(gen.disp.mlx, texture.data.img);
	end_destroy_exit(&gen, 0);
	return 0;
}
*/