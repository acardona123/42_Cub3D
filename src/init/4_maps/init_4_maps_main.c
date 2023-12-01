/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_4_maps_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:11:57 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 19:42:05 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

#ifdef BONUS

/**
 * @brief initialises the minimap and bigmap images
 * 
 * @param gen 
 * EXIT if faillure
 */
void	in_4_minimap_init(t_general *gen)
{
	in_4_world_init(gen);
	in_4_bigmap_init(gen);
}

#endif