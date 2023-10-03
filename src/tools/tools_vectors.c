/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:09:01 by acardona          #+#    #+#             */
/*   Updated: 2023/10/03 18:31:05 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

void	to_vector_print(t_vector_f v)
{
	printf("vector(%f, %f)\n", v.x, v.y);
}

inline double	to_vector_norm(t_vector_f v0, t_vector_f v1)
{
	return (sqrt(pow(v1.x - v0.x, 2) + pow(v1.y - v0.y, 2)));
}