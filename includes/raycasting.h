/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:05:10 by acardona          #+#    #+#             */
/*   Updated: 2023/09/22 14:47:20 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

#include "shared.h"

typedef int v2si	__attribute__ ((vector_size (8)));

typedef enum e_collision_history
{
	COL_FIRST,
	COL_LAST,
	COL_TOO_OLD
}	t_collision_history;

#endif