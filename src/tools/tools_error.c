/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:58:31 by acardona          #+#    #+#             */
/*   Updated: 2023/11/19 04:24:56 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

void	to_error_msg(char *msg)
{
	write(STDERR_FILENO, "\e[31;1m× Error:\e[31m\n", 23);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\e[0m\n", 6);
}

void	to_warning_msg(char *msg)
{
	write(STDERR_FILENO, "\e[33;1m⚠ Warning:\e[33m\n", 26);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\e[0m\n", 6);
}
