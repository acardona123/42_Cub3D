/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_bonus_hologram.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:28:59 by acardona          #+#    #+#             */
/*   Updated: 2023/12/02 21:11:59 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

/**
 * @brief fills the textures arrays of a hologram chunk to point to each of its
 *	faces' textures. If it is the first time that a hologram is found, checks if
 *	the hologram texture is available (ie defined in the map)
 * 
 * @param texturepack 
 * @param chunk_holo hologram chunk
 * @return t_bool FAIL if texture missing in the map
 * @return t_bool SUCCESS otherwise
 */
t_bool	in_3_mapcontent_hologram_chunk_init_textures(
		t_texture_pack *texturepack, t_chunk *chunk_holo)
{
	static bool	already_checked = false;

	if (!already_checked && !texturepack->hologram.group_len)
		return (to_error_msg(MSG_TEXTURE_MISSING_HOLOGRAM), FAIL);
	already_checked = true;
	sh_chunk_set_texture(chunk_holo, FACE_N, &texturepack->hologram, true);
	sh_chunk_set_texture(chunk_holo, FACE_S, &texturepack->hologram, true);
	sh_chunk_set_texture(chunk_holo, FACE_E, &texturepack->hologram, true);
	sh_chunk_set_texture(chunk_holo, FACE_W, &texturepack->hologram, true);
	return (SUCCESS);
}

#endif