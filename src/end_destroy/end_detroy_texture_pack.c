/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_detroy_texture_pack.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:17:29 by acardona          #+#    #+#             */
/*   Updated: 2023/09/23 01:42:45 by acardona         ###   ########.fr       */
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
	t_animated_texture	**textures;
	int					i;

	if (!pack)
		return ;
	textures = (t_animated_texture *[NUMBER_OF_TEXTURES]){pack->wall_n,
		pack->wall_s, pack->wall_e, pack->wall_w, pack->door_front,
		pack->door_side_r, pack->door_side_l};
	i = -1;
	while (++i < NUMBER_OF_TEXTURES && textures[i])
	{
		_end_textures_destroy_one_animated_texture(mlx, textures[i]);
		free(textures[i]);
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
	int	i;

	if (!target->frame_table)
		return ;
	i = 0;
	while (i < target->frame_number && target->frame_table[i].path)
	{
		_end_textures_destroy_one_static_texture(&target->frame_table[i], mlx);
		++i;
	}
	free(target->frame_table);
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
	if (target->data.addr)
		free(target->data.addr);//?
}
