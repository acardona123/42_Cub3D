/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_destroy_texture_pack.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:17:29 by acardona          #+#    #+#             */
/*   Updated: 2023/12/04 21:53:42 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shared.h"

static void	_end_textures_destroy_group_of_texture(void *mlx,
				t_group_of_textures *group);
static void	_end_textures_destroy_one_animated_texture(void *mlx,
				t_animated_texture *textu_anim);
static void	_end_textures_destroy_one_static_texture(void *mlx,
				t_static_texture *textu_static);

#ifdef BONUS

/**
 * @brief frees and destroys all the elements of the texture pack.
 *			Can be used on a partially unitiallysed texture pack wich
 *			initialisation have been stoped due to an error
 * 
 * @param mlx pointer to the mlx
 * @param pack pointer toward general->textures
 */
void	end_destroy_texture_pack(void *mlx, t_texture_pack *pack)
{
	t_group_of_textures	**groups;
	int					i_group;

	if (!pack)
		return ;
	groups = (t_group_of_textures *[NUMBER_OF_TEXTURES]){
		&pack->wall_n, &pack->wall_s, &pack->wall_e, &pack->wall_w,
		&pack->wall1_n, &pack->wall1_s, &pack->wall1_e, &pack->wall1_w,
		&pack->door_front,
		&pack->door_side_close,
		&pack->door_side_open_opened, &pack->door_side_open_opening,
		&pack->door_side_open_closed, &pack->door_side_open_closing,
		&pack->wall_crashes, &pack->crashes,
		&pack->wall_leaks, &pack->leaks,
		&pack->hologram};
	i_group = -1;
	while (++i_group < NUMBER_OF_TEXTURES)
		_end_textures_destroy_group_of_texture(mlx, groups[i_group]);
}

#else

/**
 * @brief frees and destroys all the texture groups of the texture pack.
 *			Can be used on a partially unitiallysed texture pack wich
 *			initialisation have been stoped due to an error
 * 
 * @param mlx pointer to the mlx
 * @param pack pointer toward general->textures
 */
void	end_destroy_texture_pack(void *mlx, t_texture_pack *pack)
{
	t_group_of_textures	**groups;
	int					i_group;

	if (!pack)
		return ;
	groups = (t_group_of_textures *[NUMBER_OF_TEXTURES]){&pack->wall_n,
		&pack->wall_s, &pack->wall_e, &pack->wall_w};
	i_group = -1;
	while (++i_group < NUMBER_OF_TEXTURES)
		_end_textures_destroy_group_of_texture(mlx, groups[i_group]);
}

#endif

/**
 * @brief destroys the textures group content (array of animated texture with
 *		all the animated textures it contains). 
 * 
 * @param mlx 
 * @param group 
 */
static void	_end_textures_destroy_group_of_texture(void *mlx,
	t_group_of_textures *group)
{
	size_t				i_anim_textu;

	if (!group || !group->group_len)
		return ;
	i_anim_textu = 0;
	while (group->textures_array[i_anim_textu])
	{
		_end_textures_destroy_one_animated_texture(mlx, group->textures_array
		[i_anim_textu]);
		free(group->textures_array[i_anim_textu]);
		++i_anim_textu;
	}
	free(group->textures_array);
	group->group_len = 0;
}

/**
 * @brief destroys an animated texture with all its static textures used for
 *			animation
 * 
 * @param mlx 
 * @param anim pointer to a t_animated_texture pointer which content must be
 *	destroyed
 */
static void	_end_textures_destroy_one_animated_texture(void *mlx,
	t_animated_texture *textu_anim)
{
	unsigned int	i;

	if (!textu_anim || !textu_anim->frame_array)
		return ;
	i = 0;
	while (i < textu_anim->frame_number
		&& textu_anim->frame_array[i].path)
	{
		_end_textures_destroy_one_static_texture(mlx,
			&textu_anim->frame_array[i]);
		++i;
	}
	free(textu_anim->frame_array);
}

/**
 * @brief destroys a static texture content <=> it's path, image
 * 
 * @param mlx 
 * @param textu_static pointer untouched but value destroyed
 */
static void	_end_textures_destroy_one_static_texture(void *mlx,
	t_static_texture *textu_static)
{
	if (!textu_static)
		return ;
	free(textu_static->path);
	if (textu_static->data.img)
		mlx_destroy_image(mlx, textu_static->data.img);
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