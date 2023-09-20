/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:10:26 by acardona          #+#    #+#             */
/*   Updated: 2023/09/20 02:13:09 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>


#include <stdio.h>/////////////////////////



# include "../mlx/mlx.h"

# define FLOAT_EPSILON 0.000001

typedef enum e_type
{
	NOTHING = '0',
	WALL,
	DOOR
}	t_type;

typedef struct s_data_tmp
{
	float	x_max;
	float	y_max;
	char	**map;
}	t_data_tmp;



typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

#endif