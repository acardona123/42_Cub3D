/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2_texturepack_set_color.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 00:39:36 by acardona          #+#    #+#             */
/*   Updated: 2023/09/28 21:57:17 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static int	_in_2_set_color_get_end_component(char *str, int *dst);

/**
 * @brief extracts rgb components of a line (previously splited arround spaces)
 * 
 * @param dest_color points to the t_texture_pack color value (e.g: &color_f)
 * @param line_arg splitted line to check
 * @param already_done indicates if this elem of the texturepack has already
 *		been treated in a previous line
 * @return SUCCESS if color succesfully set (already_done updated)
 * @return FAIL if the line have a wrong format or redefine a variable
 *			(err msg displayed but no argument freed)
 */
t_bool	in_2_set_color(int *dest_color, char **line_arg,
	bool *already_done)
{
	int	start_idx;
	int	subcolor;

	if (*already_done)
		return (to_error_msg("Double definition of ceilling/floor color"),
			FAIL);
	if (ft_tablen(line_arg) != 2)
		return (to_error_msg("Wrong color format"), FAIL);
	*already_done = true;
	start_idx = _in_2_set_color_get_end_component(line_arg[1], dest_color);
	if (start_idx == -1 || line_arg[1][start_idx] != ',')
		return (to_error_msg("Wrong color format"), FAIL);
	line_arg[1][start_idx] = 0;
	start_idx = _in_2_set_color_get_end_component(line_arg[1], &subcolor);
	if (start_idx == -1 || line_arg[1][start_idx] != ',')
		return (to_error_msg("Wrong color format"), FAIL);
	*dest_color = *dest_color + (subcolor << 8);
	line_arg[1][start_idx] = 0;
	start_idx = _in_2_set_color_get_end_component(line_arg[1], &subcolor);
	if (start_idx != 0)
		return (to_error_msg("Wrong color format"), FAIL);
	*dest_color = *dest_color + (subcolor << 16);
	return (SUCCESS);
}

/**
 * @brief tries to extract the last rgb element of a string. this last rgb would
 *		be an number between 0 and 255, separated from the beggining of the
 *		string by a coma
 * 
 * @param str the string to study
 * @param dst_value destination where the 0-255 value will be stored if found 
 * @return int success: return the index in str where the coma preceding the
 *				value is, the value is stored in dst_value
 *				(e.g : str = "1,125" => return 1, *dst_value = 125)
 *			FAILLURE : if wrong format, then return -1. undifined behaviour for
 *				the *dst_value. (err msg displayed, no argument freed)
 */
static int	_in_2_set_color_get_end_component(char *str, int *dst_value)
{
	ssize_t	len;
	int		i_start;

	len = ft_strlen(str);
	if (!len)
		return (-1);
	i_start = len - 1;
	while (i_start >= 0 && ft_isdigit(str[i_start]))
		--i_start;
	if (i_start == -1)
	{
		++i_start;
		if (len > 3)
			return (-1);
	}
	else if (str[i_start] != ',' || i_start == len - 1
		|| ft_strlen(str + i_start + 1) > 3)
		return (-1);
	*dst_value = ft_atoi(str + i_start + (str[i_start] == ','));
	if (*dst_value > 255)
		return (-1);
	return (i_start);
}

/*
//test _in_2_set_color_get_end_component
int	main()
{
	char	**tabstr;
	ssize_t	start = 0;
	int		nb;
	int		idx_start;
	int		i;

	tabstr = (char *[10]){"1", "12", "123", "255", "256", "1,1", "1,255",
		"1,256", "1,", "1d"};
	i = 0;
	while (i < 10)
	{
		printf("\"%s\" :\n", tabstr[i]);
		idx_start = _in_2_set_color_get_end_component(tabstr[i] + start, &nb);
		if (idx_start >= 0)
			printf("  i_start=%d(%c) -> int=%d\n", idx_start,
				tabstr[i][idx_start], nb);
		else
			printf("Error format\n");
		++i;
	}
	return (0);
}
*/
/*
//test in_2_set_color
int	main( void)
{
	char	*tabstr[3];
	int		i;
	int		nb;
	bool	done;

	done = FAIL;
	tabstr[0] = ft_strdup("F");
	tabstr[1] = ft_strdup("255,1655,1");
	tabstr[2] = NULL;
	if (in_2_set_color(&nb, tabstr, &done) == true)
		printf("color:%x\n", nb);
	free(tabstr[0]);
	free(tabstr[1]);
	return (0);
}
*/