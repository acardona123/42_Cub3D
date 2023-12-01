/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_action_leaks_crashes.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:41:43 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 15:30:38 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

#ifdef BONUS

static t_data	*_gp_action_get_img(t_general *gen,
					size_t now_time, t_hitpoint *hitpoint, bool reset_texture);
static void		gp_frame_leaks_or_craskes_fill_frame(t_data *buff,
					t_data *static_textu, float size_ratio, t_padding padding);

/**
 * @brief triggers the display of a leak IF the ray heat the crashes/leaks
 *	chunks in the activation area (between the ACTION_LEAKS_CRASHES_BORDER_INF
 *	and ACTION_LEAKS_CRASHES_BORDER_SUP). If triggered then initializes
 *	_gp_action_get_img to reset it to the right texture;
 * 
 * @param gen 
 * @param now_time 
 * @param hit_pt 
 */
void	gp_leak_crash_action(t_general *gen, size_t now_time,
	t_hitpoint *hit_pt)
{
	float	dec;
	t_chunk	*chunk;

	chunk = &gen->map.map[hit_pt->chunk_co_x][hit_pt->chunk_co_y];
	if ((hit_pt->hit_face == FACE_S && (chunk->action->active_faces & ACTIVE_S))
		|| (hit_pt->hit_face == FACE_N
			&& (chunk->action->active_faces & ACTIVE_N)))
		dec = hit_pt->pt_co.x - floor(hit_pt->pt_co.x);
	else if ((hit_pt->hit_face == FACE_E
			&& (chunk->action->active_faces & ACTIVE_E))
		|| (hit_pt->hit_face == FACE_W
			&& (chunk->action->active_faces & ACTIVE_W)))
		dec = hit_pt->pt_co.y - floor(hit_pt->pt_co.y);
	else
		return ;
	if (dec < ACTION_LEAKS_CRASHES_BORDER_INF
		|| dec > ACTION_LEAKS_CRASHES_BORDER_SUP)
		return ;
	if (ft_isinset(chunk->type, CHARS_LEAKS))
		gen->disp.render_selec = RENDER_LEAKES;
	else
		gen->disp.render_selec = RENDER_CRASHES;
	_gp_action_get_img(gen, now_time, hit_pt, true);
}

/**
 * @brief returns the t_data associated to the leaks/crashes animation at this
 *	time. When reset_texture is true the animated texture of reference is
 *	updated based the given hitpoint (and the animation starting time is reset
 *	to now_time so that the animation restart)
 * 
 * @param gen 
 * @param now_time 
 * @param hitpoint 
 * @param reset_texture 
 * @return t_data* the frame of the animation to display
 */
static t_data	*_gp_action_get_img( t_general *gen,
	size_t now_time, t_hitpoint *hitpoint, bool reset_texture)
{
	static t_animated_texture	*anim_textu = NULL;
	static size_t				time_start_animation = 0;
	size_t						time_in_cycle;
	t_chunk						*chunk;
	t_group_of_textures			*texture_group;

	if (reset_texture)
	{
		chunk = &gen->map.map[hitpoint->chunk_co_x][hitpoint->chunk_co_y];
		if (ft_isinset(chunk->type, CHARS_LEAKS))
			texture_group = &gen->textures.leaks;
		else
			texture_group = &gen->textures.crashes;
		anim_textu = texture_group->textures_array
		[chunk->textures_idx[hitpoint->hit_face] % texture_group->group_len];
		return (time_start_animation = now_time, NULL);
	}
	time_in_cycle = (now_time - time_start_animation)
		% anim_textu->frame_cycle_long;
	if (time_in_cycle >= anim_textu->frame_cycle_short)
		return (&anim_textu->frame_array [anim_textu->frame_number -1].data);
	else
		return (&anim_textu->frame_array
			[(time_in_cycle / anim_textu->frame_ms) % anim_textu->frame_number]
			.data);
}

/**
 * @brief builds the buffer image to display based on the time, the animation
 *	frames and the screen dimensions
 * 
 * @param gen 
 * @param now_time 
 * @return void
 */
void	gp_frame_leaks_or_craskes(t_general *gen,
	size_t	now_time)
{
	t_data		*static_textu;
	float		size_ratio;
	t_padding	padding;

	static_textu = _gp_action_get_img(gen, now_time, NULL, false);
	size_ratio = ft_minf((float)(WIN_HEIGHT) / static_textu->pix_height,
			(float)WIN_WIDTH / static_textu->pix_width);
	padding.pad_left = (WIN_WIDTH - size_ratio * static_textu->pix_width) / 2;
	padding.pad_right = padding.pad_left + size_ratio * static_textu->pix_width;
	padding.pad_top = (WIN_HEIGHT - size_ratio * static_textu->pix_height) / 2;
	padding.pad_bottom = padding.pad_top + size_ratio
		* static_textu->pix_height;
	gp_frame_leaks_or_craskes_fill_frame(gen->disp.buff, static_textu,
		size_ratio, padding);
	mlx_put_image_to_window(gen->disp.mlx, gen->disp.win, gen->disp.buff->img,
		0, 0);
}

static void	gp_frame_leaks_or_craskes_fill_frame(t_data *buff,
	t_data *static_textu, float size_ratio, t_padding padding)
{
	char		*addr;
	t_coord_i	buff_co;

	buff_co.y = -1;
	while (++buff_co.y < WIN_HEIGHT)
	{
		addr = buff->addr + buff_co.y * buff->line_len;
		buff_co.x = -1;
		while (++buff_co.x < WIN_WIDTH)
		{
			if (buff_co.y < padding.pad_top || buff_co.x < padding.pad_left
				|| buff_co.y > padding.pad_bottom
				|| buff_co.x > padding.pad_right)
				*(int *)addr = LEAKS_CRASHES_BACKGROUND;
			else
				*(int *)addr = *(int *)(static_textu->addr
						+ (int)((buff_co.x - padding.pad_left) / size_ratio)
						*static_textu->opp
						+ (int)((buff_co.y - padding.pad_top) / size_ratio)
						*static_textu->line_len);
			addr += buff->opp;
		}
	}
}

#endif