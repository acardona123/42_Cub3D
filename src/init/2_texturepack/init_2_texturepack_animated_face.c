/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_animated_face.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 01:53:53 by acardona          #+#    #+#             */
/*   Updated: 2023/09/27 03:16:34 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static bool	_in_2_anim_texture_init_file(void *mlx,
				t_animated_texture **texture, char **line_arg);
static bool	_in_2_anim_texture_init_folder(void *mlx,
				t_animated_texture **texture, char **line_arg);

/**
 * @brief initializes the t_animated_texture structure of a texture based on a
 *			fragmented line of the input file
 * 
 * @param texture 
 * @param line_arg 
 * @return true : SUCCESS (textures successfully loaded)
 * @return false : FAILURE (err msg displayed. no argument freed)
 */
bool	in_2_anim_texture_init(void *mlx, t_animated_texture **texture,
	char **line_arg)
{
	if (*texture)
		return (to_error_msg("Multiple definition of texture"), false);
	*texture = malloc(sizeof(t_animated_texture));
	if (!texture)
		return (to_error_msg("Mem alloc fail while textures init"), false);
	if ((ft_tablen(line_arg) == 2
			&& _in_2_anim_texture_init_file(mlx, texture, line_arg) == true)
		|| _in_2_anim_texture_init_folder(mlx, texture, line_arg) == true)
		return (true);
	free(*texture);
	texture = NULL;
	return (false);
}

/**
 * @brief generate the t_animated_texture in the case of only one path is given
 *		(without parametres for frame rates or so) => this path must be directly
 *		the xpm file path
 *	TODO: tests
 * 
 * @param mlx ptr to the mlx
 * @param texture struct to fill
 * @param line_arg splited line of the input file to import
 * @return true SUCCESS: texture successfully imported, no arg freed
 * @return false FAILLURE: err msg displayed, no arg freed
 */
static bool	_in_2_anim_texture_init_file(void *mlx,
	t_animated_texture **texture, char **line_arg)
{
	(*texture)->frame_array = malloc (sizeof(t_static_texture));
	if ((*texture)->frame_array)
		return (to_error_msg("Mem alloc fail while textures init"), false);
	(*texture)->frame_number = 1;
	(*texture)->frame_ms = INT_MAX / 2;
	(*texture)->frame_pause_ms = 0;
	(*texture)->frame_cycle_short = INT_MAX / 2;
	(*texture)->frame_cycle_long = INT_MAX / 2;
	(*texture)->frame_array[0] = (t_static_texture){line_arg[1], 0, 0,
		(t_data){0}};
	if (in_2_static_texture_init_one(mlx, &(*texture)->frame_array[0],
			line_arg[1]) == false)
	{
		free((*texture)->frame_array);
		return (false);
	}
	line_arg[1] = NULL;
	return (true);
}

/**
 * @brief fills t_animated_texture structure based on the line_arg elements:
 *	{surface_acronym, path to the folder containing the textures, frame_number,
 *	frame_ms, frame_pause_ms}
 * TODO: to do
 * @param mlx 
 * @param texture 
 * @param line_arg 
 * @return true SUCCESS: textures successfully imported, no arg freed
 * @return false : err msg displayed, no arg freed
 */
static bool	_in_2_anim_texture_init_folder(void *mlx,
	t_animated_texture **texture, char **line_arg)
{
	
}
