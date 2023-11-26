/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_action_leaks_crashes.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:41:43 by acardona          #+#    #+#             */
/*   Updated: 2023/11/26 04:02:09 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

#ifdef BONUS

static t_data	*_gp_frame_leaks_crashes_get_img(t_general *gen,
					size_t now_time, t_hitpoint *hitpoint, bool reset_texture);

/**
 * @brief triggers the display of a leak IF the ray heat the crashes/leaks
 *	chunks in the activation area (between the ACTION_LEAKS_CRASHES_BORDER_INF
 *	and ACTION_LEAKS_CRASHES_BORDER_SUP). If triggered then initializes
 *	_gp_frame_leaks_crashes_get_img to reset it to the right texture;
 * 
 * @param gen 
 * @param now_time 
 * @param hit_pt 
 */
void	gp_action_leaks_or_crashes(t_general *gen, size_t now_time,
	t_hitpoint *hit_pt)
{
	float	dec;

	if (hit_pt->hit_face == FACE_S || hit_pt->hit_face == FACE_N)
		dec = hit_pt->pt_co.x - floor(hit_pt->pt_co.x);
	else
		dec = hit_pt->pt_co.y - floor(hit_pt->pt_co.y);
	if (dec < ACTION_LEAKS_CRASHES_BORDER_INF
		|| dec > ACTION_LEAKS_CRASHES_BORDER_SUP)
		return ;
	if (ft_isinset(gen->map.map[hit_pt->chunk_co_x][hit_pt->chunk_co_y].type,
		CHARS_LEAKS))
		gen->disp.render_selec = RENDER_LEAKES;
	else
		gen->disp.render_selec = RENDER_CRASHES;
	_gp_frame_leaks_crashes_get_img(gen, now_time, hit_pt, true);
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
static t_data	*_gp_frame_leaks_crashes_get_img( t_general *gen,
	size_t now_time, t_hitpoint *hitpoint, bool reset_texture)
{
	static t_animated_texture	*anim_texture = NULL;
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
		anim_texture = texture_group->textures_array
		[chunk->textures_idx[hitpoint->hit_face] % texture_group->group_len];
		return (time_start_animation = now_time, NULL);
	}
	time_in_cycle = (now_time - time_start_animation)
		% anim_texture->frame_cycle_long;
	if (time_in_cycle >= anim_texture->frame_cycle_short)
		return (&anim_texture->frame_array
			[anim_texture->frame_number -1].data);
	else
		return (&anim_texture->frame_array
			[time_in_cycle % (anim_texture->frame_number)].data);
}

/**
 * @brief builds the buffer image to display based on the time, the animation
 *	frames and the screen dimensions
 * 
 * @param gen 
 * @param now_time 
 * @return void
 */
void	gp_frames_leaks_or_crashes_build_frame(t_general *gen,
	size_t	now_time)
{
	t_data	*static_textu;

	static_textu = _gp_frame_leaks_crashes_get_img(gen, now_time, NULL, false);
	//ici dessiner l'image redimensionnee dans le buffer
	mlx_put_image_to_window(gen->disp.mlx, gen->disp.win, gen->disp.buff, 0, 0);
}

#endif