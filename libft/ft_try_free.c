/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_try_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:37:23 by acardona          #+#    #+#             */
/*   Updated: 2023/11/02 17:39:46 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief given a pointer to a target to free, checks if this target is non NULL
 *		and if so frees it and reset it to NULL
 * 
 * @param to_free 
 */
void	ft_try_free(void **to_free)
{
	if (*to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
}
