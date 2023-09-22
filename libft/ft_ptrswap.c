/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:50:23 by acardona          #+#    #+#             */
/*   Updated: 2023/09/22 18:40:37 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief free the pointer designated by *old_ptr and replace it by the
 * pointer new_ptr
 * 
 * @param old_ptr 
 * @param new_ptr 
 */
void	ft_ptrswap(void **old_ptr, void *new_ptr)
{
	void	*tmp;

	if (!old_ptr)
	{
		write(2, "Error:\nft_ptrswap with NULL pointer\n", 35);
		return ;
	}
	tmp = *old_ptr;
	*old_ptr = new_ptr;
	free(tmp);
}
