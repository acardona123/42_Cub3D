/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:10:26 by acardona          #+#    #+#             */
/*   Updated: 2023/09/23 02:00:53 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>
# include <X11/X.h>
# include <X11/keysym.h>


#include <stdio.h>

# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define FLOAT_EPSILON 0.000001

typedef enum e_exit_values
{
	EXIT_NORMAL,
	EXIT_INIT_0,
	EXIT_INIT_1,
	EXIT_INIT_2,
	EXIT_INIT_3
}	t_exit_values;



typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef t_coord	t_vector;

//tools_vectors
void	to_vector_print(t_vector v);
double	to_vector_norm(t_vector v0, t_vector v1);

//tools_error
void	to_error_msg(char *msg);

#endif