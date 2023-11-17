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
static void				r_frame_empty_column(t_data *buff, int idx_ray);

/**
 * @brief draws the buffer image using raycasting
 *		(floor, wall and ceilling only)
 * 
 * @param gen 
 * @param time used for getting the right animation
 */
void	*rc_raycasting_frame_build(t_general *gen, size_t time_frame)
{
	register int	idx_ray;
	register float	p_angle;
	t_hitpoint		hit_pt;
	t_coord_f		p_co;

	p_co = gen->player.p_co;
	p_angle = gen->player.p_angle;
	idx_ray = -1;
	while (++idx_ray < WIN_WIDTH)
	{
		hit_pt = r_ray_hit(gen, (t_ray_params){ray_raycasting, time_frame,
				p_co, p_angle + gen->angles_set[idx_ray]});
		if (hit_pt.pt_co.x <= 0.)
			r_frame_empty_column(gen->disp.buff, idx_ray);
		else
		{
			hit_pt.dist = to_vector_norm(hit_pt.pt_co, p_co);
			if (hit_pt.dist < DIST_WALL_MIN)
				hit_pt.dist = DIST_WALL_MIN;
			_r_frame_build_column(gen, idx_ray, hit_pt, time_frame);
		}
	}
	return (gen->disp.buff->img);
}

/**
 * @brief draw a gray column if no ostacle is found. This shouldn't happen
 *	(can only happend if outside the map boundaries, but in this case a black
 *	screen is displayed so rc_raycasting_frame_build isn't called)
 * 
 * @param buff 
 * @param idx_ray 
 * @param color_f 
 * @param color_c 
 */
static void	r_frame_empty_column(t_data *buff, int idx_ray)
{
	int				y;
	register char	*addr_x;

	addr_x = buff->addr + idx_ray * buff->opp;
	y = -1;
	while (++y < WIN_HEIGHT)
		*(int *)(addr_x + y * buff->line_len) = 0xa0a0a0;
}

/**
 * @brief draw a column of pixel form a texture into the buffer image
 * 
 * @param gen 
 * @param idx_ray index of the column to draw (between 0 and WINDOW_WIDTH)
 * @param hitpoint impact point between the ray sent for this column
 * @param time time when building the image (used for texture animation)
 */
static void	_r_frame_build_column(t_general *gen, int idx_ray,
	t_hitpoint hitpoint, size_t time)
{
	register long int	y;
	register long int	tmp_y;
	register long int	h_theoric;
	register char		*addr_x;
	t_static_texture	*texture;

	texture = r_get_texture_of_column(&gen->map, &hitpoint, time);
	h_theoric = 1 / (gen->angle_correc[idx_ray] * hitpoint.dist) * WIN_HEIGHT;
	addr_x = gen->disp.buff->addr + gen->disp.buff->opp * idx_ray;
	tmp_y = (WIN_HEIGHT - h_theoric) / 2;
	y = -1;
	while (++y < tmp_y)
		*(int *)(addr_x + y * gen->disp.buff->line_len) = gen->textures.color_c;
	tmp_y = (WIN_HEIGHT + h_theoric) >> 1;
	--y;
	r_get_pixel_color(NULL, NULL, 0, NULL);
	while (++y < tmp_y && y < WIN_HEIGHT)
		*(int *)(addr_x + y * gen->disp.buff->line_len) = r_get_pixel_color(\
			&gen->map.map[hitpoint.chunk_co_x][hitpoint.chunk_co_y], &hitpoint,
				h_theoric, texture);
	--y;
	while (++y < WIN_HEIGHT)
		*(int *)(addr_x + y * gen->disp.buff->line_len) = gen->textures.color_f;
}
