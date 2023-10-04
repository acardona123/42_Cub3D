/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:00:23 by acardona          #+#    #+#             */
/*   Updated: 2023/10/04 23:38:13 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEPLAY_H
# define GAMEPLAY_H

# include "shared.h"

void	game_turn_head(t_general *gen, t_head_rotate direction);
void	game_move_player(t_general *gen, t_vector_f direction);
int		game_looping(void *elem);
#endif