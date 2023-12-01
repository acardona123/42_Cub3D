/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_get_pixel_color.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:30:03 by alexandm          #+#    #+#             */
/*   Updated: 2023/12/01 20:34:31 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

#ifdef BONUS

inline static float	_r_get_pixel_color_door_ratio(t_chunk_face face,
						t_chunk *chunk);

/**
 * @brief gets the pixel corresponding to the given texture at a certain column
 *			and height.
 *			Before each change of column the functon need to be reset (static
 *			variable inside) by calling it with a NULL chunk
 *			(to recalculate the height for this new column texture)
 * 
 * @param  chunk chunk hit (need type and extra_data_f)
 * @param  hitpoint hitpoint data used to differentiate if it is a door (then
 *		the value used to find the column is in hit_pt->extra_data_f), or
 *		another obstacle (the value is the decimal value of the x or y hitpoint 
 *		coordinate depending on the orientation of the face hit)
 * @param height theorical height of the texture img (can be > of WIN_HEIGHT)
 * @param texture the texture to use
 * @return int the color of the searched pixel, starting from the bottom of the
 *		column and going up by one each call of this function
 */
int	r_get_pixel_color(t_chunk *chunk, t_hitpoint *hit_pt, long int height,
	t_static_texture *texture)
{
	static unsigned int	y = 0;
	static float		ratio_height = 1.;
	float				ratio_col;

	if (!chunk)
		return (y = 0, 0);
	if (!y)
	{
		if (height > WIN_HEIGHT)
			y = (int)(height - WIN_HEIGHT) / 2;
		ratio_height = (float)texture->img_height / height;
	}
	if (chunk->type == DOOR)
		ratio_col = _r_get_pixel_color_door_ratio(hit_pt->hit_face, chunk);
	else if (hit_pt->hit_face == FACE_S)
		ratio_col = hit_pt->pt_co.x - floor(hit_pt->pt_co.x);
	else if (hit_pt->hit_face == FACE_N)
		ratio_col = ceil(hit_pt->pt_co.x) - hit_pt->pt_co.x;
	else if (hit_pt->hit_face == FACE_E)
		ratio_col = hit_pt->pt_co.y - floor(hit_pt->pt_co.y);
	else
		ratio_col = ceil(hit_pt->pt_co.y) - hit_pt->pt_co.y;
	return (*(int *)(texture->data.addr
		+ ((int)(ratio_col * texture->data.pix_width)) * texture->data.opp
		+ texture->data.line_len * (int)(++y * ratio_height)));
}

inline static float	_r_get_pixel_color_door_ratio(t_chunk_face face,
	t_chunk *chunk)
{
	if (face == FACE_S || face == FACE_E)
		return (chunk->extra_data_f);
	return (1.f - chunk->extra_data_f);
}

#else

/**
 * @brief gets the pixel corresponding to the given texture at a certain column
 *			and height.
 *			Before each change of column the functon need to be reset (static
 *			variable inside) by calling it with a NULL chunk
 *			(to recalculate the height for this new column texture)
 * 
 * @param  chunk chunk hit (need type and extra_data_f)
 * @param  hitpoint hitpoint data used to get the texture column used
 *		(the value is the decimal value of the x or y coordinate depending
 *		on the orientation of the face hit)
 * @param height theorical height of the texture img (can be > of WIN_HEIGHT)
 * @param texture the texture to use
 * @return int the color of the searched pixel, starting from the bottom of the
 *		column and going up by one each call of this function
 */
int	r_get_pixel_color(t_chunk *chunk, t_hitpoint *hit_pt, long int height,
	t_static_texture *texture)
{
	static unsigned int	y = 0;
	static float		ratio_height = 1.;
	float				ratio_col;

	if (!chunk)
		return (y = 0, 0);
	if (!y)
	{
		if (height > WIN_HEIGHT)
			y = (int)(height - WIN_HEIGHT) / 2;
		ratio_height = (float)texture->img_height / height;
	}
	if (hit_pt->hit_face == FACE_S)
		ratio_col = hit_pt->pt_co.x - floor(hit_pt->pt_co.x);
	else if (hit_pt->hit_face == FACE_N)
		ratio_col = ceil(hit_pt->pt_co.x) - hit_pt->pt_co.x;
	else if (hit_pt->hit_face == FACE_E)
		ratio_col = hit_pt->pt_co.y - floor(hit_pt->pt_co.y);
	else
		ratio_col = ceil(hit_pt->pt_co.y) - hit_pt->pt_co.y;
	++y;
	return (*(int *)(texture->data.addr
		+ ((int)(ratio_col * texture->data.pix_width)) * texture->data.opp
		+ texture->data.line_len * (int)(y * ratio_height)));
}

#endif