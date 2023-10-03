/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_frame_build.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:14:47 by acardona          #+#    #+#             */
/*   Updated: 2023/09/30 21:44:24 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

static void				_r_frame_build_column(t_general *gen, int idx_ray,
							register t_hitpoint hitpoint, size_t time);
static t_static_texture	*_r_get_column_texture(
							t_animated_texture*texture, size_t time, size_t t0);
static int				_r_get_pixel_color(
							double height, t_static_texture *texture,
							double ratio_col);

/**
 * @brief draws the buffer image using raycasting
 *		(floor, wall and ceilling only)
 * 
 * @param gen 
 * @param time used for getting the right animation
 */
void	r_frame_construction(t_general *gen, size_t time)
{
	register int		idx_ray;
	register t_hitpoint	hitpoint;
	register t_coord_f	p_co;
	register float		p_angle;

	p_co = gen->player.p_co;
	p_angle = gen->player.p_angle;
	idx_ray = -1;
	while (++idx_ray < WIN_WIDTH)
	{
		hitpoint = r_ray_collision(WALL, p_co,
				p_angle + gen->angles_set[idx_ray], &gen->map);
		hitpoint.dist = to_vector_norm(hitpoint.point_co, gen->player.p_co);
		if (hitpoint.dist < DIST_WALL_MIN)
			hitpoint.dist = DIST_WALL_MIN;
		_r_frame_build_column(gen, idx_ray, hitpoint, time);
	}
}

// static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_len + x * (data->opp));
// 	*(unsigned int*)dst = color;
// }

/**
 * @brief draw a column of pixel in the buffer image
 * 
 * @param gen 
 * @param idx_ray index of the column to draw (between 0 and WINDOW_WIDTH)
 * @param hitpoint impact point between the ray sent for this column
 * @param time time when building the image (used for texture animation)
 */
static void	_r_frame_build_column(t_general *gen, int idx_ray,
	register t_hitpoint hitpoint, size_t time)
{
	register long int	y;
	register long int	tmp_y;
	register long int	h_theoric;
	char				*addr_x;
	t_static_texture	*texture;

	texture = _r_get_column_texture(gen->map.map[hitpoint.chunk_co.x]
		[hitpoint.chunk_co.y].textures[hitpoint.hit_face], time,
			gen->map.map[hitpoint.chunk_co.x][hitpoint.chunk_co.y].t0);
	h_theoric = 1 / (gen->angle_correc[idx_ray] * hitpoint.dist) * WIN_HEIGHT;
	addr_x = gen->disp.buff->addr + idx_ray * gen->disp.buff->opp;
	tmp_y = (WIN_HEIGHT - h_theoric) / 2;
	y = -1;
	while (++y < tmp_y)
		*(int *)(addr_x + y * gen->disp.buff->line_len) = gen->textures.color_c;
	tmp_y = (WIN_HEIGHT + h_theoric) >> 1;
	--y;
	_r_get_pixel_color(0, NULL, 0);
	while (++y < tmp_y && y < WIN_HEIGHT)
		*(int *)(addr_x + y * gen->disp.buff->line_len) = _r_get_pixel_color(\
			h_theoric, texture, hitpoint.point_co.x - floor(hitpoint.point_co.x)
				+ hitpoint.point_co.y - floor(hitpoint.point_co.y));
	--y;
	while (++y < WIN_HEIGHT)
		*(int *)(addr_x + y * gen->disp.buff->line_len) = gen->textures.color_f;
}

/*
static void	_r_frame_build_column(t_general *gen, int idx_ray,
	register t_hitpoint hitpoint, size_t time)
{
	t_static_texture		*texture;
	double					h_theoric;

	texture = _r_get_column_texture(gen->map.map[hitpoint.chunk_co.x]
	[hitpoint.chunk_co.y].textures[hitpoint.hit_face], time, gen->map.map
	[hitpoint.chunk_co.x][hitpoint.chunk_co.y].t0);
	h_theoric = 1. / (hitpoint.height_corrector
	* to_vector_norm(hitpoint.point_co, gen->player.p_co) + DIST_REF)
	* WIN_HEIGHT;
	


}
*/

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
static t_static_texture	*_r_get_column_texture(t_animated_texture
*texture, size_t time, size_t t0)
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

/**
 * @brief gets the pixel corresponding to the given texture at a certain column
 *			and height.
 *			Before each change of column the functon need to be reset (static
 *			variable inside) by calling it with a NULL texture
 * 
 * @param height theorical hight of the texture img (can be > of WIN_HEIGHT)
 * @param texture 
 * @param ratio_col between 0. and 1. => the column to draw is this
 *			value * img_width
 * @return int the color of the searched pixel
 */
static int	_r_get_pixel_color(double height, t_static_texture *texture,
	double ratio_col)
{
	static unsigned int	y = 0;
	static double		ratio_height = 1.;

	if (!texture)
		return (y = 0, 0);
	if (!y && texture)
	{
		if (height > WIN_HEIGHT)
			y = (int)(height - WIN_HEIGHT) / 2;
		ratio_height = texture->img_height / height;
	}
	++y;
	return (*(int *)(texture->data.addr
		+ ((int)(ratio_col * texture->data.pix_width)) * texture->data.opp
		+ texture->data.line_len * (int)(y * ratio_height)));
}
