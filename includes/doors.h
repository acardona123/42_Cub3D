/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:36:00 by acardona          #+#    #+#             */
/*   Updated: 2023/10/30 02:18:20 by acardona         ###   ########.fr       */
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
float	doors_update_status(t_chunk *door, size_t time);

#endif