/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_bonus_wall1.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:20:02 by acardona          #+#    #+#             */
/*   Updated: 2023/12/04 22:22:58 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

/**
 * @brief fills the textures arrays of a wall1 chunk to point to each of its
 *	faces' textures. If it is the first time that a wall1 is found, checks if
 *	the wall1 texture is available (ie defined in the map)
 * 
 * @param texturepack 
 * @param chunk_wall1 wall1 chunk
 * @return t_bool FAIL if texture missing in the map
 * @return t_bool SUCCESS otherwise
 */
t_bool	in_3_mapcontent_wall1_chunk_init_textures(
		t_texture_pack *texturepack, t_chunk *chunk_wall1)
{
	static bool	already_checked = false;

	if (!already_checked && (!texturepack->wall1_n.group_len
			|| !texturepack->wall1_e.group_len
			|| !texturepack->wall1_s.group_len
			|| !texturepack->wall1_w.group_len))
		return (to_error_msg(MSG_TEXTURE_MISSING_HOLOGRAM), FAIL);
	already_checked = true;
	sh_chunk_set_texture(chunk_wall1, FACE_N, &texturepack->wall1_n, true);
	sh_chunk_set_texture(chunk_wall1, FACE_S, &texturepack->wall1_e, true);
	sh_chunk_set_texture(chunk_wall1, FACE_E, &texturepack->wall1_s, true);
	sh_chunk_set_texture(chunk_wall1, FACE_W, &texturepack->wall1_w, true);
	return (SUCCESS);
}

#endif