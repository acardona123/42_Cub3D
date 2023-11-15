/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:35:18 by acardona          #+#    #+#             */
/*   Updated: 2023/11/15 15:00:44 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

#ifdef BONUS

static void	_gp_frame_ingame(t_general *gen, size_t delay, size_t now_time);
static void	_gp_frame_bigmap(t_general *gen);

/**
 * @brief function that loop to generate the frames according to the inputs
 * 
 * @param gen_ void * pointer to the t_general structure
 * @return int 0 anyway, necessary for the mlx
 */
int	gp_looping(void *gen_)
{
	t_general		*gen;
	static size_t	last_time = 0;
	size_t			now_time;
	size_t			delay;

	gen = gen_;
	now_time = to_getime();
	delay = now_time - last_time;
	last_time = now_time;
	if (gen->disp.img_select == INGAME)
		_gp_frame_ingame(gen, delay, now_time);
	else if (gen->disp.img_select == BIG_MAP)
		_gp_frame_bigmap(gen);
	return (0);
}

/**
 * @brief ingame rendering: movementsand raycasting done 
 * 
 * @param gen 
 * @param delay 
 * @param now_time 
 */
static void	_gp_frame_ingame(t_general *gen, size_t delay, size_t now_time)
{
	void	*img;

	gp_walk(gen,
		gen->next_moove[GO_RIGHT] - gen->next_moove[GO_LEFT],
		gen->next_moove[GO_FORWARD] - gen->next_moove[GO_BACK], delay);
	gen->player.p_chunk.x = (int)gen->player.p_co.x;
	gen->player.p_chunk.y = (int)gen->player.p_co.y;
	gp_turn_head(gen, gen->next_moove[TURN_R] - gen->next_moove[TURN_L],
		delay);
	if (ft_isinset(gen->map.map[(int)gen->player.p_co.x]
			[(int)gen->player.p_co.y].type, CHARS_OBSTACLE))
		img = gen->disp.img_out_map->img;
	else
		img = rc_raycasting_frame_build(gen, now_time);
	if (gen->minimap.bigmap_size_ratio >= 0)
		maps_draw_minimap(gen);
	mlx_put_image_to_window(gen->disp.mlx, gen->disp.win, img, 0, 0);
}

/**
 * @brief Only displays the big map on the entiere window
 * 
 * @param disp 
 * @param bigmap_img 
 */
static void	_gp_frame_bigmap(t_general *gen)
{
	mlx_put_image_to_window(gen->disp.mlx, gen->disp.win,
		gen->minimap.bigmap.img, 0, 0);
	if (gen->minimap.bigmap_size_ratio >= 0)
		maps_bigmap_put_player_window(&gen->disp, &gen->minimap, &gen->settings,
			&gen->player);
}

#else

int	gp_looping(void *gen_)
{
	static t_general		*gen;
	void					*img;

	gen = gen_;
	gp_walk(gen,
		(float)(gen->next_moove[GO_RIGHT] - gen->next_moove[GO_LEFT]),
		(float)(gen->next_moove[GO_FORWARD] - gen->next_moove[GO_BACK]),
		FIXED_DELAY);
	gp_turn_head(gen, gen->next_moove[TURN_R] - gen->next_moove[TURN_L],
		FIXED_DELAY);
	if (ft_isinset(gen->map.map[(int)gen->player.p_co.x]
			[(int)gen->player.p_co.y].type, CHARS_OBSTACLE))
		img = gen->disp.img_out_map->img;
	else
		img = rc_raycasting_frame_build(gen, 0);
	mlx_put_image_to_window(gen->disp.mlx, gen->disp.win, img,
		0, 0);
	return (0);
}
#endif
