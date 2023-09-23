/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 23:36:53 by acardona          #+#    #+#             */
/*   Updated: 2023/05/09 00:32:18 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_ft_itoa_simple_len(int n)
{
	int	i;

	i = 1;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_itoa_simple(char dst[11], int n)
{
	int				i;
	int				neg;
	unsigned int	ln;

	neg = (n < 0);
	i = _ft_itoa_simple_len(n) + neg;
	if (neg)
	{
		*dst = '-';
		ln = -n;
	}
	else
		ln = n;
	dst[i] = 0;
	while (--i >= neg)
	{
		dst[i] = '0' + ln % 10;
		ln /= 10;
	}
}
