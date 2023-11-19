/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_destroy_general.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:25:18 by acardona          #+#    #+#             */
/*   Updated: 2023/11/15 14:22:44 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/end_destroy.h"

void	end_destroy_general(t_general *gen)
{
	end_destroy_map(&gen->map);
	end_destroy_minimap(gen->disp.mlx, &gen->minimap);
	end_destroy_texture_pack(gen->disp.mlx, &gen->textures);
	end_destroy_display(&gen->disp);
}
