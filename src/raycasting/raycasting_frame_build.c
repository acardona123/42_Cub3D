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

static const double	g_h_slop = WIN_HEIGHT / (2 * (DIST_WALL_MIN - DIST_REF));
static const double g_h_offset = WIN_HEIGHT - DIST_WALL_MIN * g_h_slop;

static void				_r_frame_build_column(t_general *gen, int idx_ray,
							register t_hitpoint hitpoint, size_t time);
static t_static_texture	*_r_get_column_texture(
							t_animated_texture*texture, size_t time, size_t t0);
static int				_r_get_pixel_color(
							double height, t_static_texture *texture,
							double ratio_col);

void	r_frame_construction(t_general *gen)
{
	register int		idx_ray;
	register t_hitpoint	hitpoint;
	register t_coord_f	p_co;
	register float		p_angle;
	size_t				time;

	p_co = gen->player.p_co;
	p_angle = gen->player.p_angle;
	time = to_getime();
	idx_ray = -1;
	while (++idx_ray < WIN_WIDTH)
	{
		hitpoint = r_ray_collision(WALL, p_co, p_angle + gen->angles_set[idx_ray], &gen->map);
		hitpoint.height_corrector = gen->angles_set[idx_ray];
		// printf("angle : %f\n", (p_angle + gen->angles_set[idx_ray]) * 180 / M_PI);//
		// printf("  hitpoint : x=%f, y=%f     face: %d\n", hitpoint.point_co.x, hitpoint.point_co.y, hitpoint.hit_face);
		// printf("\nhitpoint : (%f, %f)->(%d, %d); type : \'%c\'; face %d:\n", hitpoint.point_co.x, hitpoint.point_co.y, hitpoint.chunk_co.x, hitpoint.chunk_co.y, gen->map.map[hitpoint.chunk_co.x][hitpoint.chunk_co.y].type, hitpoint.hit_face);//

		_r_frame_build_column(gen, idx_ray, hitpoint, time);
	}
}

// static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_len + x * (data->opp));
// 	*(unsigned int*)dst = color;
// }

static void	_r_frame_build_column(t_general *gen, int idx_ray,
	register t_hitpoint hitpoint, size_t time)
{
	register unsigned int	height;
	register unsigned int	tmp_y;
	register unsigned int	y;
	char					*addr_x;
	t_static_texture		*texture;

	texture = _r_get_column_texture(gen->map.map[hitpoint.chunk_co.x][hitpoint.chunk_co.y].textures[hitpoint.hit_face], time, gen->map.map[hitpoint.chunk_co.x][hitpoint.chunk_co.y].t0);
	// mlx_put_image_to_window(gen->disp.mlx, gen->disp.win, texture->data.img, 0, 0);//

	height = fmax(g_h_offset + g_h_slop
			* cos(hitpoint.height_corrector) * to_vector_norm_sqrt(hitpoint.point_co, gen->player.p_co), 0) ;
		
	addr_x = gen->disp.buff->addr + idx_ray * gen->disp.buff->opp;
	tmp_y = (WIN_HEIGHT - height) >> 1; // * 0.5
	y = -1;
	while (++y < tmp_y)
		*(int *)(addr_x + y * gen->disp.buff->line_len) = gen->textures.color_c; //ici on peut opti l'invariant
	tmp_y = (WIN_HEIGHT + height) >> 1; // * 0.5
	--y;
	_r_get_pixel_color(0, NULL, 0);
	while (++y < tmp_y)
	{
		if (1)
		{
		*(int *)(addr_x + y * gen->disp.buff->line_len) = _r_get_pixel_color(height,
				texture, hitpoint.point_co.x - floor(hitpoint.point_co.x)
				+ hitpoint.point_co.y - floor(hitpoint.point_co.y));
		}
		else//
			*(int *)(addr_x + y * gen->disp.buff->line_len) = 255;//
	}
	--y;

	while (++y < WIN_HEIGHT)
		*(int *)(addr_x + y * gen->disp.buff->line_len) = gen->textures.color_f;
}

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

	// (void)time;
	// (void)t0;
	// return(&texture->frame_array[0]);
	// /*
	if (texture->frame_number == 1)
		return (&texture->frame_array[0]);
	else
	{
		time_in_cycle = (time - t0) % texture->frame_cycle_long;
		// printf("\e[32mFrame:\n num: %d\n t_frame: %d\n t_pause: %d\n t_short: %d\n t_long: %d\n time_in_cycle : %d =>  %d or %d\e[0m\n\n", texture->frame_number, texture->frame_ms, texture->frame_pause_ms, texture->frame_cycle_short, texture->frame_cycle_long, time_in_cycle, texture->frame_number - 1, time_in_cycle % texture->frame_ms);
		if (time_in_cycle >= texture->frame_cycle_short)
			return (&texture->frame_array[texture->frame_number - 1]);
		else
			return (&texture->frame_array[time_in_cycle / texture->frame_ms]);
	}
	// */
	return (NULL);
}

static int	_r_get_pixel_color(double height, t_static_texture *texture,
	double ratio_col)
{
	static unsigned int	y = 0;
	static double		ratio_height = 1.;

	if (!texture)
		return (y = 0, 0);
	if (!y && texture)
	{
		// fflush(stdout);
		// printf(" texture %s (height = %f; ratio_col = %f)\n", texture->path, height, ratio_col);
		// printf(" text_height : %d\n", texture->img_height);
		// printf(" height : %f\n", height);
		// printf(" text_img = %p\n", texture->data.img);
		// printf(" text_img_addr = %p\n", texture->data.addr);
		// fflush(stdout);
		ratio_height = texture->img_height / height;
	}
	++y;
	return (*(int*)(texture->data.addr
			+ ((int)(ratio_col * texture->data.pix_width)) * texture->data.opp
		+ texture->data.line_len * (int)(y * ratio_height)));
}
