/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:30:53 by acardona          #+#    #+#             */
/*   Updated: 2023/09/30 20:38:44 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "shared.h"

# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_init_lists
{
	t_list			*lst_param;
	t_list			*lst_map;
	unsigned int	map_max_y;
	unsigned int	map_max_x;
}	t_lists;

bool	init_main(int ac, char **av, t_general	*gen);

/* =============== 0_mapformat/ =============== */
// init_0_mapformat_main.c
t_lists	in_1_map_format_check(int ac, char **av, t_general *gen);
// init_o_mapformat_utils.c
int		in_1_file_opening(char *file_name);
bool	in_1_line_is_parameter(char *line);
bool	in_1_line_is_empty(char *line);

/*

 =============== 1_user_interface/ =============== */
// init_1_user_interface_main.c
void	in_0_init_display(t_general *gen);
// in_0_init_display_hooks.c
void	in_0_hooks_init(t_general *gen);

/*

=============== 2_texturepack/ =============== */
// init_2_texturepack_main.c
void	in_2_init_texture_pack(int ac, char **av, t_general *gen,
			t_lists *lst_init);

/*

=============== 3_mapcontent/ =============== */
// init_3_mapcontent.c
void	in_3_map_content_init(t_general *gen, t_lists *lst_init);
//init_3_mapcontent_utils.c
// void	in_3_map_allocate_textures(t_general *gen, char c, int x, int y);
void	in_3_map_allocate_textures(t_texture_pack *texturepack, t_animated_texture **tex, char c);
void	in_3_map_init_destroy(t_general *gen, t_lists *lst_init, char *err_msg);

#endif