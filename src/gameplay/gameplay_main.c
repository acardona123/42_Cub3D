/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:35:18 by acardona          #+#    #+#             */
/*   Updated: 2023/10/05 01:36:06 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"
#include "../../includes/raycasting.h"

static void	_game_calulate_delay(t_general *gen);

int	game_looping(void *elem)
{
	t_general	*gen;

	gen = elem;

	_game_calulate_delay(gen);
	r_frame_construction(gen);
	mlx_put_image_to_window(gen->disp.mlx, gen->disp.win, gen->disp.buff->img,
		0, 0);
	return (0);
}

#ifdef BONUS

static void	_game_calulate_delay(t_general *gen)
{
	size_t		time;
	size_t		new_delay;

	time = to_getime();
	new_delay = time - gen->delays.last_time;
	gen->delays.last_time = time;
	gen->delays.delay_average += ((float)((long long int)new_delay - (long long int)gen->delays
			.delay_array[gen->delays.idx])) / DELAY_AVERAGE_AMPITUDE;
	gen->delays.delay_array[gen->delays.idx] = new_delay;
	++gen->delays.idx;
	if (gen->delays.idx == DELAY_AVERAGE_AMPITUDE)
		gen->delays.idx = 0;
}

#endif
#ifndef BONUS
static void	_game_calulate_delay(t_general *gen)
{
	(void)gen;
}
#endif

void	game_turn_head(t_general *gen, t_head_rotate direction)
{
	gen->player.p_angle += (float)direction
		* gen->settings. key_turn_speed / gen->delays.delay_average;
	printf("NEW_ANGLE:%f\n", gen->player.p_angle);
	while (gen->player.p_angle > 2 * M_PI)
		gen->player.p_angle -= 2 * M_PI;
	while (gen->player.p_angle < 0)
		gen->player.p_angle += 2 * M_PI;
}

void	game_move_player(t_general *gen, t_vector_f direction)
{
	gen->player.p_co.x += gen->settings.walk_speed / gen->delays.delay_average
		* (direction.x * cos(gen->player.p_angle)
			+ direction.y * sin(gen->player.p_angle));
	if (gen->player.p_co.x > gen->map.x_max - DIST_WALL_MIN)
		gen->player.p_co.x = gen->map.x_max - DIST_WALL_MIN;
	else if (gen->player.p_co.x < DIST_WALL_MIN)
		gen->player.p_co.x = DIST_WALL_MIN;
	gen->player.p_co.y += gen->settings.walk_speed / gen->delays.delay_average
		* (direction.y * cos(gen->player.p_angle)
			- direction.x * sin(gen->player.p_angle));
	if (gen->player.p_co.y > gen->map.y_max - DIST_WALL_MIN)
		gen->player.p_co.y = gen->map.y_max - DIST_WALL_MIN;
	else if (gen->player.p_co.y < DIST_WALL_MIN)
		gen->player.p_co.y = DIST_WALL_MIN;
}
