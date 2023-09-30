/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 02:44:40 by alexandm          #+#    #+#             */
/*   Updated: 2023/10/01 01:31:35 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

/**
 * @brief fills the textures array of a chunk to point to each of its
 *	faces' textures
 * 
 * @param texturepack 
 * @param chunk_textures_array 
 * @param chunk_type 
 */
void	in_3_map_locate_textures(t_texture_pack *texturepack,
	t_animated_texture **chunk_textures_array, char chunk_type)
{
	if (chunk_type == WALL)
	{
		chunk_textures_array[FACE_N] = texturepack->wall_n;
		chunk_textures_array[FACE_S] = texturepack->wall_s;
		chunk_textures_array[FACE_E] = texturepack->wall_e;
		chunk_textures_array[FACE_W] = texturepack->wall_w;
	}
	else if (chunk_type == DOOR)
		chunk_textures_array[FACE_N] = texturepack->door_front;
}

/**
 * @brief function to properly exit the map init (with an optional error msg)
 * 
 * @param gen 
 * @param lst_init 
 * @param err_msg error msg to display if not NULL
 */
void	in_3_map_init_destroy_exit(t_general *gen, t_lists *lst_init,
	char *err_msg)
{
	if (err_msg)
		to_error_msg(err_msg);
	if (lst_init->lst_param)
		to_lstfree(&lst_init->lst_param);
	if (lst_init->lst_map)
		to_lstfree(&lst_init->lst_map);
	end_destroy_exit(gen, EXIT_INIT_3);
}
