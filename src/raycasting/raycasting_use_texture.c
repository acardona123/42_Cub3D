/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_use_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 00:32:31 by acardona          #+#    #+#             */
/*   Updated: 2023/11/07 17:28:08 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

#ifdef BONUS

/**
 * @brief checks if the bloc hit by the ray need a texture update before being
 *	casted
 *	note: for the current frame this texture update will not affect the colums
 *	of pixels already generated fr the raycasting (ie the one on the left side
 *	of the current column)
 * @param texture_pack 
 * @param map 
 * @param hit_point 
 * @param time time when the ray was seent
 */
void	r_update_texture(t_texture_pack *texture_pack, t_map *map,
	t_hitpoint *hit_point, size_t time)
{
	static size_t	last_time;
	static t_chunk	*last_chunk;

	if (time == last_time && &map->map[hit_point->chunk_co_x]
		[hit_point->chunk_co_y] == last_chunk)
		return ;
	last_time = time;
	last_chunk = &map->map[hit_point->chunk_co_x][hit_point->chunk_co_y];
	if (last_chunk->type == DOOR
		&& last_chunk->extra_data_i & 1 << DOOR_TEXTURE_NEED_UPDATE)
		doors_update_texture_main_side(texture_pack, last_chunk);
}

#else

void	r_update_texture(t_texture_pack *texture_pack, t_map *map,
	t_hitpoint *hit_point, size_t time)
{
	(void)texture_pack;
	(void)map;
	(void)hit_point;
	(void)time;
}

#endif

/**
 * @brief given a certain animated texture, a reference time t0 and a current
 *		time, this function calculates the static texture associated to the
 *		animated texture at this moment.
 * 
 * @param texture pointer to the animated texture
 * @param time current time (in ms)
 * @param t0 reference time for the animated texture, corresponding to the one
 *				of the chunk (in ms)
 * @return t_static_texture* returns the static texture
 */
t_static_texture	*r_get_column_texture(t_animated_texture *texture,
	size_t time, size_t t0)
{
	register unsigned int	time_in_cycle;

	if (texture->frame_number == 1)
		return (&texture->frame_array[0]);
	else
	{
		time_in_cycle = (time - t0) % texture->frame_cycle_long;
		if (time_in_cycle >= texture->frame_cycle_short)
			return (&texture->frame_array[texture->frame_number - 1]);
		else
			return (&texture->frame_array[time_in_cycle / texture->frame_ms]);
	}
	return (NULL);
}

# ifdef BONUS

/**
 * @brief gets the pixel corresponding to the given texture at a certain column
 *			and height.
 *			Before each change of column the functon need to be reset (static
 *			variable inside) by calling it with a NULL chunk
 * 
 * @param  chunk chunk hit (need type and extra_data_f)
 * @param  hitpoint hitpoint data usedd to differentiate if it is a door (then
 *		the value used to find the column is in hit_pt->extra_data_f), or a wall
 *		(the the value is the decimal value of the x or y coordinate depending
 *		on the orientation of the face hitted)
 * @param height theorical hight of the texture img (can be > of WIN_HEIGHT)
 * @param texture the texture to use
 * @return int the color of the searched pixel
 */
int	r_get_pixel_color(t_chunk *chunk, t_hitpoint *hit_pt, long int height,
	t_static_texture *texture)
{
	static unsigned int	y = 0;
	static float		ratio_height = 1.;
	float				ratio_col; //between 0. and 1. => the column to draw is this value * img_width

	if (!chunk)
		return (y = 0, 0);
	if (!y)
	{
		if (height > WIN_HEIGHT)
			y = (int)(height - WIN_HEIGHT) / 2;
		ratio_height = (float)texture->img_height / height;
	}
	if (chunk->type == DOOR)
		ratio_col = chunk->extra_data_f;
	else if (hit_pt->hit_face == FACE_N || hit_pt->hit_face == FACE_S)
		ratio_col = hit_pt->pt_co.x - floor(hit_pt->pt_co.x);
	else
		ratio_col = hit_pt->pt_co.y - floor(hit_pt->pt_co.y);
	++y;
	return (*(int *)(texture->data.addr
		+ ((int)(ratio_col * texture->data.pix_width)) * texture->data.opp
		+ texture->data.line_len * (int)(y * ratio_height)));
}

#else

/**
 * @brief gets the pixel corresponding to the given texture at a certain column
 *			and height.
 *			Before each change of column the functon need to be reset (static
 *			variable inside) by calling it with a NULL chunk
 * 
 * @param  chunk chunk hit (need type and extra_data_f)
 * @param  hitpoint hitpoint data usedd to differentiate if it is a door (then
 *		the value used to find the column is in hit_pt->extra_data_f), or a wall
 *		(the the value is the decimal value of the x or y coordinate depending
 *		on the orientation of the face hitted)
 * @param height theorical hight of the texture img (can be > of WIN_HEIGHT)
 * @param texture the texture to use
 * @return int the color of the searched pixel
 */
int	r_get_pixel_color(t_chunk *chunk, t_hitpoint *hit_pt, long int height,
	t_static_texture *texture)
{
	static unsigned int	y = 0;
	static float		ratio_height = 1.;
	float				ratio_col; //between 0. and 1. => the column to draw is this value * img_width

	if (!chunk)
		return (y = 0, 0);
	if (!y)
	{
		if (height > WIN_HEIGHT)
			y = (int)(height - WIN_HEIGHT) / 2;
		ratio_height = (float)texture->img_height / height;
	}
	if (hit_pt->hit_face == FACE_N || hit_pt->hit_face == FACE_S)
		ratio_col = hit_pt->pt_co.x - floor(hit_pt->pt_co.x);
	else
		ratio_col = hit_pt->pt_co.y - floor(hit_pt->pt_co.y);
	++y;
	return (*(int *)(texture->data.addr
		+ ((int)(ratio_col * texture->data.pix_width)) * texture->data.opp
		+ texture->data.line_len * (int)(y * ratio_height)));
}

#endif