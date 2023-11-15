/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:36:00 by acardona          #+#    #+#             */
/*   Updated: 2023/11/11 23:56:17 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOORS_H
# define DOORS_H

# include "shared.h"

typedef struct s_door_last_update
{
	size_t	time;
	t_chunk	*chunk;
	float	data;
}	t_door_last_update;

//doors_update.c
bool	doors_update_status(t_general *gen, t_chunk *door, size_t time);
void	doors_update_texture_main_side(t_texture_pack *texture_pack,
			t_chunk *door);
//doors_action.c
void	doors_action(t_general *gen, size_t time_now, t_chunk *chunk,
			t_chunk_face face);

#endif