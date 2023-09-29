/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_protectded.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:01:46 by acardona          #+#    #+#             */
/*   Updated: 2023/09/27 15:58:33 by acardona         ###   ########.fr       */
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

int	ft_atoi_protected(char *nptr, int *dst)
{
	long long int	nb;
	int				neg;

	*dst = 0;
	if (!nptr || !*nptr)
		return (1);
	while (*nptr && _ft_iswhitespace(*nptr))
		++nptr;
	neg = (*nptr == '-') * -1 + (*nptr != '-');
	nptr += (*nptr == '+' || *nptr == '-');
	if (ft_strlen(nptr) > 10)
		return (1);
	nb = 0;
	while (*nptr && ft_isdigit(*nptr))
		nb = nb * 10 + *nptr++ - '0';
	while (*nptr && _ft_iswhitespace(*nptr))
		++nptr;
	if (*nptr || neg * nb > INT_MAX || neg * nb < INT_MIN)
		return (1);
	*dst = neg * (int)nb;
	return (0);
}
