/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:10:26 by acardona          #+#    #+#             */
/*   Updated: 2023/11/26 00:38:30 by acardona         ###   ########.fr       */
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
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>

# include "../mlx/mlx.h"
# include "../libft/libft.h"

# include "settings.h"

# define MSG_BAD_ALLOC "memory allocation error"
//mlx error
# define MSG_MLX_INIT "mlx: fail of mlx_init"
# define MSG_MLX_NEW_IMG "mlx: fail to create a new image"
# define MSG_MLX_NEW_WINDOW "mlx: fail to create a new window"
# define MSG_MLX_XPM_TO_IMG "mlx: .xpm to image conversion failed"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		opp;
	int		line_len;
	int		pix_width;
	int		pix_height;
	int		endian;
}	t_data;

typedef enum e_bool
{
	SUCCESS,
	FAIL
}	t_bool;

typedef enum e_exit_values
{
	EXIT_NORMAL,
	EXIT_INIT_SETTINGS,
	EXIT_INIT_0,
	EXIT_INIT_1,
	EXIT_INIT_2,
	EXIT_INIT_3,
	EXIT_INIT_4
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

typedef enum e_type_of_file
{
	TYPE_IS_FILE,
	TYPE_IS_DIRECTORY,
	TYPE_IS_UNKNOWN
}	t_type_of_file;

//tools_tvectors
void	to_vector_print(t_vector_f v);
double	to_vector_norm(t_coord_f P0, t_coord_f P1);
double	to_vector_norm_sqr(t_coord_f P0, t_coord_f P1);

//tools_error
void	to_error_msg(char *msg);
void	to_warning_msg(char *msg);

//tools_file.c
char	*to_file_build_path(char *name0, char *name1, char *name2, char *name3);

//tools_lst.c
void	to_lstfree(t_list **lst);

//tools_time.c
size_t	to_getime(void);

//tools_anglesset.c
void	to_angle_set_init(float *old_fov, float new_fov, double *angles_set,
			double *angle_correc);

//tools_mlx_image.c
t_bool	to_mlx_new_empty_img(void *mlx, t_data *img_dst, int width,
			int height);
void	to_mlx_draw_rectangle(t_data *data, t_coord_i position,
			t_coord_i dimensions, int color);
void	to_mlx_draw_circle(t_data *data, t_coord_i center, int radius,
			int color);
#endif