/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:00:23 by acardona          #+#    #+#             */
/*   Updated: 2023/11/02 00:16:00 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEPLAY_H
# define GAMEPLAY_H

# include "shared.h"

// gameplay_main
int		gp_looping(void *elem);
// gameplay_turn_head.c
void	gp_turn_head(t_general *gen, t_head_rotate direction, size_t delay);
// gameplay_walk.c
void	gp_walk(t_general *gen, int dir_xp, int dir_yp, size_t delay);

#endif