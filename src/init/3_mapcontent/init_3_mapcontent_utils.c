/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 02:44:40 by alexandm          #+#    #+#             */
/*   Updated: 2023/09/30 20:38:44 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

/**
 * @brief allocate textures for wall
 * 
 * @param gen 
 * @param c 
 * @param x 
 * @param y 
 */
void	in_3_map_allocate_textures(t_texture_pack *texturepack, t_animated_texture **tex, char c)
{
	if (c == WALL)
	{
		tex[0] = texturepack->wall_n;
		tex[1] = texturepack->wall_s;
		tex[2] = texturepack->wall_e;
		tex[3] = texturepack->wall_w;
	}
	else if (c == DOOR)
		tex[0] = texturepack->door_front;
}

/**
 * @brief funxtion to properly exit the map init (with an optional error msg)
 * 
 * @param gen 
 * @param lst_init 
 * @param err_msg error msg to display if not NULL
 */
void	in_3_map_init_destroy(t_general *gen, t_lists *lst_init, char *err_msg)
{
	if (err_msg)
		to_error_msg(err_msg);
	to_lstfree(&lst_init->lst_param);
	to_lstfree(&lst_init->lst_map);
	end_destroy_exit(gen, EXIT_INIT_3);
}
