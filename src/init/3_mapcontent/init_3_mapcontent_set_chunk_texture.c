/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_set_chunk_texture.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:55:56 by acardona          #+#    #+#             */
/*   Updated: 2023/12/02 17:41:32 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

/**
 * @brief fills the textures arrays of a chunk to point to each of its
 *	faces' textures. If it is the first time that a door is found, checks if all
 *	doors textures are availables (ie defined in the map)
 * 
 * @param texturepack 
 * @param chunk_textures_array 
 * @param chunk_type 
 * @return t_bool	SUCCESS if texture succesfully associated to each face
 *					FAIL if a requiered texture (of the bonus elements, here a
 *					door/leak/crash/...) is missing.
 */
t_bool	in_3_mapcontent_set_chunk_textures(t_texture_pack *texturepack,
	t_chunk *chunk)
{
	if (chunk->type == WALL || chunk->type == NOTHING)
	{
		sh_chunk_set_texture(chunk, FACE_N, &texturepack->wall_n, true);
		sh_chunk_set_texture(chunk, FACE_S, &texturepack->wall_s, true);
		sh_chunk_set_texture(chunk, FACE_E, &texturepack->wall_e, true);
		sh_chunk_set_texture(chunk, FACE_W, &texturepack->wall_w, true);
	}
	else if (chunk->type == DOOR)
		return (in_3_mapcontent_doors_chunk_init(texturepack, chunk));
	else if (ft_isinset(chunk->type, CHARS_LEAKS))
		return (in_3_mapcontent_leaks_chunk_init_textures(texturepack, chunk));
	else if (ft_isinset(chunk->type, CHARS_CRASHES))
		return (in_3_mapcontent_crashes_chunk_init_textures(texturepack,
				chunk));
	else if (chunk->type == HOLOGRAM)
		return (in_3_mapcontent_hologram_chunk_init_textures(texturepack,
				chunk));
	return (SUCCESS);
}

#else

/**
 * @brief fills the textures arrays of a chunk to point to each of its
 *	faces' textures
 * 
 * @param texturepack 
 * @param chunk
 * @return SUCCESS always
 */
t_bool	in_3_mapcontent_set_chunk_textures(t_texture_pack *texturepack,
	t_chunk *chunk)
{
	if (chunk->type == WALL || chunk->type == NOTHING)
	{
		sh_chunk_set_texture(chunk, FACE_N, &texturepack->wall_n, true);
		sh_chunk_set_texture(chunk, FACE_S, &texturepack->wall_s, true);
		sh_chunk_set_texture(chunk, FACE_E, &texturepack->wall_e, true);
		sh_chunk_set_texture(chunk, FACE_W, &texturepack->wall_w, true);
	}
	return (SUCCESS);
}

#endif
