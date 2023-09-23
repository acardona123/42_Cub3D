/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:10:26 by acardona          #+#    #+#             */
/*   Updated: 2023/09/22 15:38:53 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>


#include <stdio.h>

# include "../mlx/mlx.h"

# define FLOAT_EPSILON 0.000001

typedef struct s_coord_f
{
	double	x;
	double	y;
}	t_coord_f;
typedef t_coord_f	t_vector_f;

typedef struct s_coord_i
{
	int	x;
	int	y;
}	t_coord_i;

void	to_vector_print(t_vector_f v);
double	to_vector_norm(t_vector_f v0, t_vector_f v1);

#endif