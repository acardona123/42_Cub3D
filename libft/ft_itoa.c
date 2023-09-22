/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:05:21 by acardona          #+#    #+#             */
/*   Updated: 2023/05/13 18:08:01 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_ft_itoa_count(int n);
static char	*_ft_itoa_min(void);

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	int		neg;

	if (n == -2147483648)
		return (_ft_itoa_min());
	len = _ft_itoa_count(n);
	neg = 0;
	if (n < 0)
		neg = 1;
	str = malloc((len + neg + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (neg)
	{
		n *= -1;
		str[0] = '-';
	}
	str[len + neg] = 0;
	while (len > 0)
	{
		str[len-- + neg - 1] = '0' + n % 10;
		n /= 10;
	}
	return (str);
}

static int	_ft_itoa_count(int n)
{
	int	i;

	i = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*_ft_itoa_min(void)
{
	char	*str;
	int		i;

	str = malloc(12 * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while ("-2147483648"[++i])
		str[i] = "-2147483648"[i];
	str[i] = '\0';
	return (str);
}
