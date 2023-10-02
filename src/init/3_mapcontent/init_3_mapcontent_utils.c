/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3_mapcontent_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 02:44:40 by alexandm          #+#    #+#             */
/*   Updated: 2023/10/02 14:55:35 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

/**
 * @brief function to properly exit the map init (with an optional error msg)
 * 
 * @param gen 
 * @param lst_init 
 * @param err_msg error msg to display if not NULL
 */
void	in_3_map_init_destroy_exit(t_general *gen, t_lists *lst_init,
	char *err_msg)
{
	if (err_msg)
		to_error_msg(err_msg);
	if (lst_init->lst_param)
		to_lstfree(&lst_init->lst_param);
	if (lst_init->lst_map)
		to_lstfree(&lst_init->lst_map);
	end_destroy_exit(gen, EXIT_INIT_3);
}
