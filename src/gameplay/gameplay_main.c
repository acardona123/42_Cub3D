/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:35:18 by acardona          #+#    #+#             */
/*   Updated: 2023/10/04 15:41:05 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

int	game_looping(void *elem)
{
	(void)elem;
	return 0;
}

void	game_turn_head(float *player_angle, unsigned int delta_t,
	t_head_rotate direction)
{
	*player_angle += (float)direction * delta_t * ROTATE_SPEED_KEY;
	while (*player_angle > 2 * M_PI)
		*player_angle -= 2 * M_PI;
	while (*player_angle < 0)
		*player_angle += 2 * M_PI;
}

#ifndef BONUS

void	game_move_player(t_player *P, t_map *map, t_vector_f direction, unsigned int delta_t)
{
	P->p_co.x += P->p_speed * delta_t
		* (direction.x * cos(P->p_angle) + direction.y * sin(P->p_angle));
	if (P->p_co.x > map->x_max - DIST_WALL_MIN)
		P->p_co.x = map->x_max - DIST_WALL_MIN;
	else if (P->p_co.x < DIST_WALL_MIN)
		P->p_co.x = DIST_WALL_MIN;
	P->p_co.y += P->p_speed * delta_t
		* (direction.y * cos(P->p_angle) - direction.x * sin(P->p_angle));
	if (P->p_co.y > map->y_max - DIST_WALL_MIN)
		P->p_co.y = map->y_max - DIST_WALL_MIN;
	else if (P->p_co.y < DIST_WALL_MIN)
		P->p_co.y = DIST_WALL_MIN;
}
#endif

#ifdef BONUS

void	game_move_player(t_general *gen, void *direction)
{
	
	gen->player.p_co.x += gen->player.p_speed * delta_t
		* (direction.x * cos(gen->player.p_angle) + direction.y * sin(gen->player.p_angle));
	if (gen->player.p_co.x > map->x_max - DIST_WALL_MIN)
		gen->player.p_co.x = map->x_max - DIST_WALL_MIN;
	else if (gen->player.p_co.x < DIST_WALL_MIN)
		gen->player.p_co.x = DIST_WALL_MIN;
	gen->player.p_co.y += gen->player.p_speed * delta_t
		* (direction.y * cos(gen->player.p_angle) - direction.x * sin(gen->player.p_angle));
	if (gen->player.p_co.y > map->y_max - DIST_WALL_MIN)
		gen->player.p_co.y = map->y_max - DIST_WALL_MIN;
	else if (gen->player.p_co.y < DIST_WALL_MIN)
		gen->player.p_co.y = DIST_WALL_MIN;
}

#endif