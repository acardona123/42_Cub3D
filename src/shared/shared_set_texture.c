/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_set_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:33:27 by acardona          #+#    #+#             */
/*   Updated: 2023/11/29 15:52:50 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shared.h"

#ifdef BONUS

/**
 * @brief insert animated texture pointer in the chunk textures tables[face].
 *	The texture is one of those present in the given texture_group, it will be
 *	selected based on the value of chunk->textures_idx[face]. If idx_seed is
 *	false the seed used to select the texture is the chunk->textures_idx[face],
 *	else chunk->textures_idx[face] is set to idx_seed
 * 
 * @param chunk 
 * @param face face which texture needs to be set
 * @param texture_group group of textures from wich the texture will be
 *			extracted
 * @param new_seed indicates if a new seed has to be generated for the
 *		designated texture.
 */
void	init_chunk_set_texture(t_chunk *chunk, t_chunk_face face,
	t_group_of_textures *texture_group, bool new_seed)
{
	if (new_seed)
		chunk->textures_idx[face] = (unsigned int)rand();
	chunk->textures[face]
		= texture_group->textures_array[chunk->textures_idx[face]
		% texture_group->group_len];
}

#else

/**
 * @brief insert animated texture pointer in the chunk textures tables[face].
 *	The texture is one of those present in the given texture_group, it will be
 *	selected based on the value of chunk->textures_idx[face]. If idx_seed is
 *	false the seed used to select the texture is the chunk->textures_idx[face],
 *	else chunk->textures_idx[face] is set to idx_seed
 * 
 * @param chunk 
 * @param face face which texture needs to be set
 * @param texture_group group of textures from wich the texture will be
 *			extracted
 * @param new_seed ignored in mandatoy part
 */
void	init_chunk_set_texture(t_chunk *chunk, t_chunk_face face,
	t_group_of_textures *texture_group, bool new_seed)
{
	(void)new_seed;
	chunk->textures[face] = texture_group->textures_array[0];
}

#endif
