/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:30:53 by acardona          #+#    #+#             */
/*   Updated: 2023/09/23 02:36:43 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "shared.h"

/* ===============0_ mapformat/ =============== */
// init_0_mapformat_main.c
void	in_0_map_format_check(int ac, char **av, t_general *gen);

/*

 =============== 1_user_interface/ =============== */
// init_1_user_interface_main.c
void	in_1_init_display(t_general *gen);
// in_1_init_display_hooks.c
void	in_1_hooks_init(t_general *gen);

/*

=============== 2_texturepack/ =============== */
// init_2_texturepack_main.c
void	in_2_init_texture_pack(int ac, char **av, t_general *gen);

/*

=============== 3_mapcontent/ =============== */
// init_3_mapcontent.c
void	in_3_map_content_init(int ac, char **av, t_general *gen);


#endif