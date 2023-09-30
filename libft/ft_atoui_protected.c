/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui_protected.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:01:46 by acardona          #+#    #+#             */
/*   Updated: 2023/09/28 21:05:35 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_ft_iswhitespace(char c)
{
	int	i;

	i = 0;
	while (" \f\n\r\t\v"[i])
		if (c == " \f\n\r\t\v"[i++])
			return (1);
	return (0);
}

int	ft_atoui_protected(char *nptr, unsigned int *dst)
{
	long long unsigned int	nb;

	*dst = 0;
	if (!nptr || !*nptr)
		return (1);
	while (*nptr && _ft_iswhitespace(*nptr))
		++nptr;
	if (!ft_isdigit(*nptr) && *nptr != '+')
		return (1);
	nptr += (*nptr == '+');
	if (ft_strlen(nptr) > 10)
		return (1);
	nb = 0;
	while (*nptr && ft_isdigit(*nptr))
		nb = nb * 10 + *nptr++ - '0';
	while (*nptr && _ft_iswhitespace(*nptr))
		++nptr;
	if (*nptr || nb > INT_MAX)
		return (1);
	*dst = (unsigned int)nb;
	return (0);
}

// #include <stdio.h>
// int main(int ac, char **av)
// {
// 	unsigned int n;

// 	printf("{%s} : %d, %u\n", av[1], ft_atoui_protected(av[1], &n), n);
// }
