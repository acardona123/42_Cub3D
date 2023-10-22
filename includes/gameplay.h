/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:00:23 by acardona          #+#    #+#             */
/*   Updated: 2023/10/22 01:32:59 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEPLAY_H
# define GAMEPLAY_H

# include "shared.h"

void	gp_turn_head(t_general *gen, t_head_rotate direction, size_t delay);
void	gp_move_player(t_general *gen, float dir_x, float dir_y, size_t delay);
int		gp_looping(void *elem);

#endif