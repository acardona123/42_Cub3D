/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_check_texture_defined.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:59:44 by acardona          #+#    #+#             */
/*   Updated: 2023/11/02 19:32:50 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

/**
 * @brief checks if all the wall's faces textures and the floor and ceilling
 *		colors have been set
 * 
 * @param texturepack 
 * @param colors_defined 
 * @return true successfully set
 * @return false missing texture
 */
bool	in_2_are_all_mandatory_textures_init(t_texture_pack *texturepack,
	bool *colors_defined)
{
	if (!texturepack->wall_n)
		return (to_error_msg(MSG_TEXTURE_MISSING_WALL_N), false);
	if (!texturepack->wall_e)
		return (to_error_msg(MSG_TEXTURE_MISSING_WALL_E), false);
	if (!texturepack->wall_s)
		return (to_error_msg(MSG_TEXTURE_MISSING_WALL_S), false);
	if (!texturepack->wall_w)
		return (to_error_msg(MSG_TEXTURE_MISSING_WALL_W), false);
	if (!colors_defined[IDX_FLOOR])
		return (to_error_msg(MSG_COLOR_MISSING_FLOOR), false);
	if (!colors_defined[IDX_CEIL])
		return (to_error_msg(MSG_COLOR_MISSING_CEIL), false);
	return (true);
}
