/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_bonus_crashes.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:02:12 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 19:27:40 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

/**
 * @brief initializes a bool[4] that indicates if a face of a crashes chunk is
*		active or not depending on its type
 * 
 * @param type ie character in the map .xpm file
 * @param active_faces flags about wich faces are activated (cf
 *		t_activable_faces)
 */
static	void	_in_3_mapcontent_crashes_get_active_faces(t_chunk_type type,
	int *active_faces)
{
	*active_faces = 0
		+ ACTIVE_N * (type == CRASHES_N)
		+ ACTIVE_E * (type == CRASHES_E)
		+ ACTIVE_S * (type == CRASHES_S)
		+ ACTIVE_W * (type == CRASHES_W);
}

/**
 * @brief fills the textures arrays of a crashes chunk to point to each of its
 *	faces' textures. If it is the first time that a crash chunk is found, checks
 *	if crashs textures are availables (ie defined in the map)
 * 
 * @param texturepack 
 * @param chunk crashes chunk
 * @return t_bool	FAIL if crashes textures are missing in the map,
 *						err msg displayed
 *					SUCCESS otherwise
 */
t_bool	in_3_mapcontent_crashes_chunk_init_textures(t_texture_pack *texturepack,
	t_chunk *chunk_crash)
{
	static bool	check_texture_done = false;
	int			active_faces;
	int			i;

	_in_3_mapcontent_crashes_get_active_faces(chunk_crash->type, &active_faces);
	if (!check_texture_done && (!texturepack->crashes.group_len
			|| !texturepack->wall_crashes.group_len))
		return (to_error_msg(MSG_TEXTURE_MISSING_CRASHES), FAIL);
	check_texture_done = true;
	if (!(active_faces & ACTIVE_N))
		sh_chunk_set_texture(chunk_crash, FACE_N, &texturepack->wall_n, true);
	if (!(active_faces & ACTIVE_E))
		sh_chunk_set_texture(chunk_crash, FACE_E, &texturepack->wall_e, true);
	if (!(active_faces & ACTIVE_S))
		sh_chunk_set_texture(chunk_crash, FACE_S, &texturepack->wall_s, true);
	if (!(active_faces & ACTIVE_W))
		sh_chunk_set_texture(chunk_crash, FACE_W, &texturepack->wall_w, true);
	i = -1;
	while (++i < 4)
		if (!chunk_crash->textures[i])
			sh_chunk_set_texture(chunk_crash, i, &texturepack->wall_crashes,
				true);
	return (SUCCESS);
}

/**
 * @brief inits the action structure of a crashes chunk
 * 
 * @param map 
 * @param x coordinate x of the chunk
 * @param y 
 * @return t_bool	SUCCESS init done
 *					FAIL if memory allocation error, err msg displayed
 */
t_bool	in_3_mapcontent_crashes_action_init(t_map *map, int x, int y)
{
	t_chunk	*chunk_crashes;

	chunk_crashes = &map->map[x][y];
	chunk_crashes->action = ft_calloc(1, sizeof(t_action));
	if (!chunk_crashes->action)
		return (to_error_msg(MSG_BAD_ALLOC), FAIL);
	_in_3_mapcontent_crashes_get_active_faces(chunk_crashes->type,
		&chunk_crashes->action->active_faces);
	chunk_crashes->action->execute = gp_leak_crash_action;
	chunk_crashes->action->dist_range = ACTION_LEAKS_CRASHES_DIST_RANGE;
	return (SUCCESS);
}

#endif