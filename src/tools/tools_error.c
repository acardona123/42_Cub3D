/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:58:31 by acardona          #+#    #+#             */
/*   Updated: 2023/09/22 18:31:20 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

void	to_error_msg(char *msg)
{
	write(STDERR_FILENO, "Error:\n", 7);
	write(STDERR_FILENO, msg, ft_strlen(msg));
}