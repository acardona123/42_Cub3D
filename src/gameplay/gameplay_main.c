/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:35:18 by acardona          #+#    #+#             */
/*   Updated: 2023/11/10 14:32:55 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

#ifdef BONUS

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
	void			*img;

	gen = gen_;
	now_time = to_getime();
	delay = now_time - last_time;
	last_time = now_time;
	gp_walk(gen,
		gen->next_moove[GO_RIGHT] - gen->next_moove[GO_LEFT],
		gen->next_moove[GO_FORWARD] - gen->next_moove[GO_BACK],
		delay);
	gp_turn_head(gen, gen->next_moove[TURN_R] - gen->next_moove[TURN_L],
		delay);
		printf("p_co: (%f, %f), angle: %f\n", gen->player.p_co.x, gen->player.p_co.y, gen->player.p_angle);//
	if (ft_isinset(gen->map.map[(int)gen->player.p_co.x]
			[(int)gen->player.p_co.y].type, CHARS_OBSTACLE))
		img = gen->disp.img_out_map->img;
	else
		img = rc_raycasting_frame_build(gen, now_time);
	mlx_put_image_to_window(gen->disp.mlx, gen->disp.win, img, 0, 0);
	return (0);
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
