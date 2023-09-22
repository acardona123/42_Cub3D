/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:09:05 by acardona          #+#    #+#             */
/*   Updated: 2023/05/13 18:09:06 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_ft_count_word(char const *str, char c);
static char	*_str_cpylim(char const *str, int n, char c);
static char	**_ft_split_free(char **liste, int i_tab);
static char	**_ft_subsplit(char **liste, char const *s, char c);

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**liste;

	if (!s)
		return (NULL);
	size = _ft_count_word(s, c);
	liste = malloc((size + 1) * sizeof(char *));
	if (!liste)
		return (NULL);
	liste[size] = NULL;
	return (_ft_subsplit(liste, s, c));
}

static char	**_ft_subsplit(char **liste, char const *s, char c)
{
	int		i;
	int		i_tab;

	i = 0;
	i_tab = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			liste[i_tab] = _str_cpylim(s, i, c);
			if (!liste[i_tab])
				return (_ft_split_free(liste, i_tab));
			i += ft_strlen(liste[i_tab++]);
		}
	}
	return (liste);
}

static int	_ft_count_word(char const *str, char c)
{
	int	new_word;
	int	i;
	int	counter;

	counter = 0;
	new_word = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			new_word = 1;
		else if (new_word == 1)
		{
			new_word = 0;
			counter++;
		}
		i++;
	}
	return (counter);
}

static char	*_str_cpylim(char const *str, int n, char c)
{
	int		j;
	int		len;
	char	*dest;

	len = 0;
	while (str[n + len] && str[n + len] != c)
		len++;
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	j = 0;
	while (j < len)
	{
		dest[j] = str[j + n];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

static char	**_ft_split_free(char **liste, int i_tab)
{
	while (i_tab >= 0)
		free(liste[i_tab--]);
	free(liste);
	return (NULL);
}
