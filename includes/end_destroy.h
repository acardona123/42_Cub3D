/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_destroy.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:20:18 by acardona          #+#    #+#             */
/*   Updated: 2023/10/21 20:23:29 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef END_DESTROY_H
# define END_DESTROY_H

#include "shared.h"

// end_destroy_display.c
void	end_destroy_display(t_display *disp);
// end_destroy_map.c
void	end_destroy_map(t_map *map);
// end_destroy_texture_pack.c
void	end_destroy_texture_pack(void *mlx, t_texture_pack *pack);
// end_destroy_general.c
void	end_destroy_general(t_general *gen);
// end_destroy_exit
void	end_destroy_exit(t_general *gen, t_exit_values n);

#endif