/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_bonus_leaks.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:02:12 by acardona          #+#    #+#             */
/*   Updated: 2023/11/26 05:51:17 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

/**
 * @brief initialize a bool[4] that indicates if a face of a leaks chunk is
*		active or not depending on its type
 * 
 * @param type ie character in the map .xpm file
 * @param active_faces flags about wich faces are activated (cf
 *		t_activable_faces)
 */
static	void	_in_3_mapcontent_leaks_get_active_faces(t_chunk_type type,
	int *active_faces)
{
	*active_faces = 0
		+ ACTIVE_N * (type == LEAKS_N)
		+ ACTIVE_E * (type == LEAKS_E)
		+ ACTIVE_S * (type == LEAKS_S)
		+ ACTIVE_W * (type == LEAKS_W);
}

/**
 * @brief fills the textures arrays of a leaks chunk to point to each of its
 *	faces' textures. If it is the first time that a leak chunk is found, checks
 *	if leaks textures are availables (ie defined in the map)
 * 
 * @param texturepack 
 * @param chunk door chunk
 * @return t_bool	FAIL if texture missing in the map, err msg displayed
 *					SUCCESS otherwise
 */
t_bool	in_3_mapcontent_leaks_chunk_init_textures(t_texture_pack *texturepack,
	t_chunk *chunk_leaks)
{
	static bool	check_texture_done = false;
	int			active_faces;
	int			i;

	if (!check_texture_done && (!texturepack->leaks.group_len
			|| !texturepack->wall_leaks.group_len))
		return (to_error_msg(MSG_TEXTURE_MISSING_LEAKS), FAIL);
	check_texture_done = true;
	_in_3_mapcontent_leaks_get_active_faces(chunk_leaks->type, &active_faces);
	if (!(active_faces & ACTIVE_N))
		init_chunk_set_texture(chunk_leaks, FACE_N, &texturepack->wall_n, true);
	if (!(active_faces & ACTIVE_E))
		init_chunk_set_texture(chunk_leaks, FACE_E, &texturepack->wall_e, true);
	if (!(active_faces & ACTIVE_S))
		init_chunk_set_texture(chunk_leaks, FACE_S, &texturepack->wall_s, true);
	if (!(active_faces & ACTIVE_W))
		init_chunk_set_texture(chunk_leaks, FACE_W, &texturepack->wall_w, true);
	i = -1;
	while (++i < 4)
		if (!chunk_leaks->textures[i])
			init_chunk_set_texture(chunk_leaks, i, &texturepack->wall_leaks,
				true);
	return (SUCCESS);
}

/**
 * @brief inits the action structure of leaks chunks
 * 
 * @param map 
 * @param x 
 * @param y 
 * @return t_bool	SUCCESS init done
 *					FAIL if memory allocation error, err msg displayed
 */
t_bool	in_3_mapcontent_leaks_action_init(t_map *map, int x, int y)
{
	t_chunk	*chunk_leaks;

	chunk_leaks = &map->map[x][y];
	chunk_leaks->action = ft_calloc(1, sizeof(t_action));
	if (!chunk_leaks->action)
		return (to_error_msg(MSG_BAD_ALLOC), FAIL);
	_in_3_mapcontent_leaks_get_active_faces(chunk_leaks->type,
		&chunk_leaks->action->active_faces);
	chunk_leaks->action->execute = gp_action_leaks_or_crashes;
	chunk_leaks->action->dist_range = ACTION_LEAKS_CRASHES_DIST_RANGE;
	return (SUCCESS);
}

#endif