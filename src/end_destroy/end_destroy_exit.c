/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_destroy_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 01:56:11 by acardona          #+#    #+#             */
/*   Updated: 2023/09/23 02:05:22 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shared.h"

/**
 * @brief Destroys properly all t_genenal structure's elements and exit with
 *	the given exit value
 * 
 * @param gen 
 * @param n 
 */
void	end_destroy_exit(t_general *gen, t_exit_values n)
{
	end_destroy_general(gen);
	exit(n);
}
