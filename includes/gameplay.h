/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:00:23 by acardona          #+#    #+#             */
/*   Updated: 2023/11/26 01:44:01 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEPLAY_H
# define GAMEPLAY_H

# include "shared.h"

// gameplay_main
int		gp_looping(void *elem);
// gameplay_turn_head.c
void	gp_turn_head(t_general *gen, size_t delay);
// gameplay_walk.c
void	gp_walk(t_general *gen, int dir_xp, int dir_yp, size_t delay);
// gameplay_action_main.c
void	gp_action_main(t_general *gen);
// gameplay_action_doors.c
void	gp_action_doors(t_general *gen, size_t time_now,
			t_hitpoint *hit_pt);
// gameplay_action_leaks_crashes.c
void	gp_action_leaks_or_crashes(t_general *gen, size_t time_now,
			t_hitpoint *hit_pt);

#endif