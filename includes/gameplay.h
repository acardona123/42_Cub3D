/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:00:23 by acardona          #+#    #+#             */
/*   Updated: 2023/10/04 14:17:56 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEPLAY_H
# define GAMEPLAY_H

# include "shared.h"

void	game_turn_head(float *player_angle, unsigned int delta_t,
	t_head_rotate direction);
void	game_move_player(t_player *P, t_map *map, t_vector_f direction, unsigned int delta_t);
#endif