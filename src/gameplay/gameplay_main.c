/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:35:18 by acardona          #+#    #+#             */
/*   Updated: 2023/11/20 19:24:14 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

#ifdef BONUS

static const int		g_min_win_size
	= (WIN_WIDTH < WIN_HEIGHT) * WIN_WIDTH
	+ (WIN_WIDTH >= WIN_HEIGHT) * WIN_HEIGHT;
static const int		g_cursor_ray
	= 3 * (3 > CURSOR_SIZE_RATIO * g_min_win_size)
	+ (3 <= CURSOR_SIZE_RATIO * g_min_win_size)
	* CURSOR_SIZE_RATIO * g_min_win_size;
static const int		g_cursor_ray_pow2
	= g_cursor_ray * g_cursor_ray;
static const int		g_cross
	= g_cursor_ray * CURSOR_CROSS_WIDTH_RATIO / 2
	* (1 < g_cursor_ray * CURSOR_CROSS_WIDTH_RATIO / 2)
	+ 1 * (1 >= g_cursor_ray * CURSOR_CROSS_WIDTH_RATIO / 2);
static const t_coord_i	g_center
	= {WIN_WIDTH / 2, WIN_HEIGHT / 2};

static void	_gp_frame_ingame(t_general *gen, size_t delay, size_t now_time);
static void	_gp_frame_bigmap(t_general *gen);
static void	_gp_frame_ingame_cursor(t_data *buff);

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
	// printf("p_co: (%f, %f), %f (%f deg)\n", gen->player.p_co.x, gen->player.p_co.y, gen->player.p_angle, gen->player.p_angle * 180/ M_PI);//
	// fflush(stdout);//
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
		gen->next_walk[GO_RIGHT] - gen->next_walk[GO_LEFT],
		gen->next_walk[GO_FORWARD] - gen->next_walk[GO_BACK], delay);
	gen->player.p_chunk.x = (int)gen->player.p_co.x;
	gen->player.p_chunk.y = (int)gen->player.p_co.y;
	gp_turn_head(gen, delay);
	if (ft_isinset(gen->map.map[(int)gen->player.p_co.x]
			[(int)gen->player.p_co.y].type, CHARS_OBSTACLE))
		img = gen->disp.img_out_map->img;
	else
		img = rc_raycasting_frame_build(gen, now_time);
	if (gen->minimap.bigmap_size_ratio >= 0)
		maps_draw_minimap(gen);
	_gp_frame_ingame_cursor(gen->disp.buff);
	mlx_put_image_to_window(gen->disp.mlx, gen->disp.win, img, 0, 0);
}

static void	_gp_frame_ingame_cursor(t_data *buff)
{
	register int	x;
	register int	y;
	char			*addr;
	bool			in_cross;

	y = -g_cursor_ray - 1;
	while (++y <= g_cursor_ray)
	{
		if (g_center.y + y >= 0 && g_center.y + y < buff->pix_height)
		{
			addr = buff->addr + (y + g_center.y) * buff->line_len
				+ (g_center.x - g_cursor_ray) * buff->opp;
			x = -g_cursor_ray - 1;
			while (++x < g_cursor_ray)
			{
				in_cross = ((x >= -g_cross && x <= g_cross)
						|| (y >= -g_cross && y <= g_cross));
				if (g_center.x + x >= 0 && g_center.x + x < WIN_WIDTH
					&& x * x + y * y <= g_cursor_ray_pow2)
					*(int *)addr = in_cross * CURSOR_COLOR_CROSS
						+ !in_cross * CURSOR_COLOR_BACKGROUND;
				addr += buff->opp;
			}
		}
	}
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
		(float)(gen->next_walk[GO_RIGHT] - gen->next_walk[GO_LEFT]),
		(float)(gen->next_walk[GO_FORWARD] - gen->next_walk[GO_BACK]),
		FIXED_DELAY);
	gp_turn_head(gen, FIXED_DELAY);
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
