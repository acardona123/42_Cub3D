/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:10:26 by acardona          #+#    #+#             */
/*   Updated: 2023/10/01 00:11:44 by acardona         ###   ########.fr       */
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
# include <stdio.h>

# include "../mlx/mlx.h"
# include "../libft/libft.h"

# include "settings.h"

typedef enum e_bool
{
	SUCCESS,
	FAIL
}	t_bool;

typedef enum e_exit_values
{
	EXIT_NORMAL,
	EXIT_INIT_0,
	EXIT_INIT_1,
	EXIT_INIT_2,
	EXIT_INIT_3
}	t_exit_values;

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

void			to_vector_print(t_vector_f v);
double			to_vector_norm(t_vector_f v0, t_vector_f v1);

//tools_error
void			to_error_msg(char *msg);

//tools_lst.c
void			to_lstfree(t_list **lst);

//tools_time.c
unsigned int	to_getime(void);

//tools_anglesset.c
void	to_angle_set_init(float *old_fov, float new_fov,
			float *angles_set);
#endif