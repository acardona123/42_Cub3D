/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 02:44:40 by alexandm          #+#    #+#             */
/*   Updated: 2023/12/01 19:46:15 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"

/**
 * @brief function to properly exit the initialisation (with an optional error
 *		msg)
 * 
 * @param gen 
 * @param lst_init to free
 * @param err_msg error msg to display if not NULL
 */
void	in_init_destroy_lists_exit(t_general *gen, t_lists *lst_init,
	char *err_msg, int exit_value)
{
	if (err_msg)
		to_error_msg(err_msg);
	if (lst_init->lst_param)
		to_lstfree(&lst_init->lst_param);
	if (lst_init->lst_map)
		to_lstfree(&lst_init->lst_map);
	end_destroy_exit(gen, exit_value);
}
