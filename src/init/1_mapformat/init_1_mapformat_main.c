/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1_mapformat_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:49:11 by acardona          #+#    #+#             */
/*   Updated: 2023/12/06 00:48:23 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static void	_in_1_map_params_check(t_general *gen, t_lists *lists, int fd_input,
				char **line);
static void	_in_1_map_mapcontent_check(t_general *gen, t_lists *lists,
				int fd_input, char **line);

/**
 * @brief checks if the map format is correct according to the subject,
 *		separates and saves the lines in two linked lists: the textures
 *		descriptions (called parameters) in one and the map content lines
 *		in the other one
 * @param ac 
 * @param av 
 * @param gen 
 * @return EXIT if error
 */
t_lists	in_1_map_format_check(int ac, char **av, t_general *gen)
{
	t_lists	lists;
	char	*line;
	int		fd_input;

	(void) ac;
	fd_input = in_1_file_opening(av[1]);
	if (fd_input == -1)
		end_destroy_exit(gen, EXIT_INIT_1);
	lists = (t_lists){0};
	line = 0;
	_in_1_map_params_check(gen, &lists, fd_input, &line);
	if (!line)
	{
		close(fd_input);
		in_init_destroy_lists_exit(gen, &lists, MSG_NO_MAP_CONTENT,
			EXIT_INIT_1);
	}
	_in_1_map_mapcontent_check(gen, &lists, fd_input, &line);
	to_get_next_line(-1, NULL);
	close(fd_input);
	return (lists);
}

/**
 * @brief stores parameters (string describing textures and ceil/floor color)
 *		in the linked list lst->param 
 * 
 * @param gen general structure to fill
 * @param lists two linked list constaining string : one for the texture's
 *		parameters lines in the map file, the other for the lines corresonding
 *		to the mapcontent elements -> will be updatedd to add a line
 * @param fd_input input file fd containing the parameters and the map
 * @param line pointer where the last read line will be stored (the last line
 *		will be used in the mapcontent_check later)
 * @return EXIT if error
 */
static void	_in_1_map_params_check(t_general *gen, t_lists *lists, int fd_input,
	char **line)
{
	int	i;

	if (to_get_next_line(fd_input, line))
		(close(fd_input),
			in_init_destroy_lists_exit(gen, lists, NULL, EXIT_INIT_1));
	while (*line && in_1_line_is_parameter(*line))
	{
		if (in_1_line_is_empty(*line))
			free(*line);
		else if (ft_lstnewaddback(&lists->lst_param, *line))
			(free(*line), close(fd_input), in_init_destroy_lists_exit(gen,
					lists, MSG_BAD_ALLOC, EXIT_INIT_1));
		if (to_get_next_line(fd_input, line))
			(close(fd_input),
				in_init_destroy_lists_exit(gen, lists, NULL, EXIT_INIT_1));
	}
	if (!(*line))
		(close(fd_input), in_init_destroy_lists_exit(gen, lists,
				MSG_NO_MAP_CONTENT, EXIT_INIT_1));
	i = -1;
	while ((*line)[++i])
		if (!ft_isinset((*line)[i], CHARS_ALLOWED))
			(close(fd_input), free(*line), in_init_destroy_lists_exit(gen,
					lists, MSG_WRONG_ACRONYME, EXIT_INIT_1));
}

/**
 * @brief stores the map in the linked list lst->map and checks if there is an
 *		empty line in the map  
 * 
 * @param gen idem _in_1_map_params_check
 * @param lists 
 * @param fd_input 
 * @param line 
 * @return EXIT if error
 */
static void	_in_1_map_mapcontent_check(t_general *gen, t_lists *lists,
	int fd_input, char **line)
{
	while (*line)
	{
		if (in_1_line_is_empty(*line))
		{
			free(*line);
			close(fd_input);
			in_init_destroy_lists_exit(gen, lists, MSG_EMPTY_LINE, EXIT_INIT_1);
		}
		if (ft_lstnewaddback(&lists->lst_map, *line))
		{
			free(*line);
			close(fd_input);
			in_init_destroy_lists_exit(gen, lists, MSG_BAD_ALLOC, EXIT_INIT_1);
		}
		lists->map_nb_lines++;
		if (ft_strlen(*line) > lists->map_nb_col)
			lists->map_nb_col = ft_strlen(*line);
		if (to_get_next_line(fd_input, line))
			(close(fd_input),
				in_init_destroy_lists_exit(gen, lists, NULL, EXIT_INIT_1));
	}
}
