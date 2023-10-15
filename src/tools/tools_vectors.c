/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:09:01 by acardona          #+#    #+#             */
/*   Updated: 2023/10/12 20:47:36 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

/**
 * @brief prints a vector's coords (floats)
 * 
 * @param v 
 */
void	to_vector_print(t_vector_f v)
{
	printf("vector(%f, %f)\n", v.x, v.y);
}

/**
 * @brief returns the euclidian norm of the vector P0,P1
 * 
 * @param P0 
 * @param P1 
 * @return double 
 */
inline double	to_vector_norm(t_coord_f P0, t_coord_f P1)
{
	return (sqrt(pow(P1.x - P0.x, 2) + pow(P1.y - P0.y, 2)));
}

/**
 * @brief returns the square of the euclidian norm of the vector P0,P1 (to avoid
 *		the square root and optimize the code)
 * 
 * @param P0 
 * @param P1 
 * @return double 
 */
inline double	to_vector_norm_sqr(t_coord_f P0, t_coord_f P1)
{
	return (pow(P1.x - P0.x, 2) + pow(P1.y - P0.y, 2));
}
