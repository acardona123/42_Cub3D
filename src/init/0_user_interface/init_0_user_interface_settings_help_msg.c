/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0_user_interface_settings_help_msg.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandm <alexandm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 21:06:28 by alexandm          #+#    #+#             */
/*   Updated: 2023/12/02 21:07:37 by alexandm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/init.h"

static const int	g_nl = 20;
static const int	g_offx = WIN_WIDTH / 2 - (HELP_MSG_WIDTH / 2);
static const int	g_offy = WIN_HEIGHT / 2 - (HELP_MSG_HEIGHT / 2);

static void	_in_0_help_disp_to_win(t_display *disp, int x, int y,
				char **tab);
static void	_in_0_settings_help_msg_display(t_display *disp);
static void	_in_0_settings_help_msg_display_custom_settings(t_display *disp,
				int *line);
static void	_in_0_settings_help_msg_display_move_settings(t_display *disp,
				int *line);

/**
 * @brief Displays commands settings on the screen and the terminal
 * 
 * @param gen 
 */
void	in_0_settings_help_msg(t_general *gen)
{
	to_mlx_str_put(gen->disp.mlx, 0, 0);
	to_mlx_str_put(gen->disp.win, 0, 0);
	_in_0_settings_help_msg_display(&gen->disp);
	printf("%s%s\n\n", MSG_HELP_INTRO_0, MSG_HELP_INTRO_1);
	printf("\e[0;1m1. \e[0;4;1mMovement:\e[0m\n");
	printf("\t%-15s [ %s ]\n", "FORWARD:", XKeysymToString(KEY_FORWARD));
	printf("\t%-15s [ %s ]\n", "LEFT:", XKeysymToString(KEY_LEFT));
	printf("\t%-15s [ %s ]\n", "BACKWARD:", XKeysymToString(KEY_BACK));
	printf("\t%-15s [ %s ]\n", "RIGHT:", XKeysymToString(KEY_RIGHT));
	printf("\t%-15s [ %s ]\n", "SPRINT:", XKeysymToString(KEY_SPRINT));
	printf(MSG_HELP_ROTATION_KEYS, XKeysymToString(KEY_LOOK_LEFT),
		XKeysymToString(KEY_LOOK_RIGHT));
	printf("2. Interaction:\n");
	printf(MSG_HELP_INTERACTION_PRINT, XKeysymToString(KEY_ACT));
	printf("3. Map:\n");
	printf("\t- %s: Display the world map.\n", XKeysymToString(KEY_BIG_MAP));
	printf("4. Settings:\n");
	printf("\t%s\n", MSG_HELP_SETTINGS_PRINT);
	printf(MSG_HELP_WALK_SPEED_PRINT, XKeysymToString(KEY_WALK_SPEED));
	printf(MSG_HELP_SPEED_ROT_KEY_PRINT, XKeysymToString(KEY_ROT_SPEED_KEY));
	printf(MSG_HELP_SPEED_ROT_MOUSE_PRNT, XKeysymToString(KEY_ROT_SPEED_MOUSE));
	printf(MSG_HELP_FOV, XKeysymToString(KEY_FOV));
	printf(MSG_HELP_ZOOM_MINIMAP, XKeysymToString(KEY_MINI_ZOOM));
}

/**
 * @brief Displays commands settings on the terminal 
 * 
 * @param gen 
 */
static void	_in_0_settings_help_msg_display(t_display *disp)
{
	char	**tmp;
	int		line;

	line = 0;
	mlx_put_image_to_window(disp->mlx, disp->win,
		disp->img_out_map->img, 0, 0);
	to_mlx_str_put(MSG_HELP_INTRO_0, g_offx, g_nl * ++line + g_offy);
	to_mlx_str_put(MSG_HELP_INTRO_1, g_offx, g_nl * ++line + g_offy);
	_in_0_settings_help_msg_display_move_settings(disp, &line);
	++line;
	to_mlx_str_put("2. INTERACTION", g_offx, g_nl * ++line + g_offy);
	to_mlx_str_put("2. INTERACTION", g_offx, g_nl * line + 1 + g_offy);
	to_mlx_draw_line_h(disp->mlx, disp->win,
		(t_coord_i){17 + g_offx, g_nl * line + 3 + g_offy}, 70);
	tmp = (char *[3]){"INTERACTION:",
		XKeysymToString(KEY_ACT), " or [ left_click ]"};
	_in_0_help_disp_to_win(disp, g_offx + 10, g_nl * ++line + g_offy, tmp);
	++line;
	to_mlx_str_put("3. MAP:", g_offx, g_nl * ++line + g_offy);
	to_mlx_str_put("3. MAP:", g_offx, g_nl * line + 1 + g_offy);
	to_mlx_draw_line_h(disp->mlx, disp->win,
		(t_coord_i){17 + g_offx, g_nl * line + 3 + g_offy}, 25);
	tmp = (char *[3]){"WORLD MAP", XKeysymToString(KEY_BIG_MAP), NULL};
	_in_0_help_disp_to_win(disp, g_offx + 10, g_nl * ++line + g_offy, tmp);
	_in_0_settings_help_msg_display_custom_settings(disp, &line);
}	

/**
 * @brief Displays movement settings on the screen
 * 
 * @param disp 
 * @param line 
 * @param g_offx 
 * @param g_offy 
 */
static void	_in_0_settings_help_msg_display_move_settings(t_display *disp
	, int *line)
{
	char	**tmp;

	++(*line);
	to_mlx_str_put("1. MOUVEMENTS", g_offx, g_nl * ++(*line) + g_offy);
	to_mlx_str_put("1. MOUVEMENTS", g_offx, g_nl * (*line) + g_offy + 1);
	to_mlx_draw_line_h(disp->mlx, disp->win,
		(t_coord_i){17 + g_offx, g_nl * (*line) + g_offy + 3}, 64);
	tmp = (char *[3]){"FORWARD:", XKeysymToString(KEY_FORWARD), NULL};
	_in_0_help_disp_to_win(disp, g_offx + 10, g_nl * ++(*line) + g_offy, tmp);
	tmp = (char *[3]){"LEFT:", XKeysymToString(KEY_LEFT), NULL};
	_in_0_help_disp_to_win(disp, g_offx + 10, g_nl * ++(*line) + g_offy, tmp);
	tmp = (char *[3]){"BACKWARD:", XKeysymToString(KEY_BACK), NULL};
	_in_0_help_disp_to_win(disp, g_offx + 10, g_nl * ++(*line) + g_offy, tmp);
	tmp = (char *[3]){"RIGHT:", XKeysymToString(KEY_RIGHT), NULL};
	_in_0_help_disp_to_win(disp, g_offx + 10, g_nl * ++(*line) + g_offy, tmp);
	tmp = (char *[3]){"SPRINT:", XKeysymToString(KEY_SPRINT), NULL};
	_in_0_help_disp_to_win(disp, g_offx + 10, g_nl * ++(*line) + g_offy, tmp);
	tmp = (char *[3]){"ROTATION RIGHT:", XKeysymToString(KEY_LOOK_RIGHT), NULL};
	_in_0_help_disp_to_win(disp, g_offx + 10, g_nl * ++(*line) + g_offy, tmp);
	tmp = (char *[3]){"ROTATION LEFT:", XKeysymToString(KEY_LOOK_LEFT), NULL};
	_in_0_help_disp_to_win(disp, g_offx + 10, g_nl * ++(*line) + g_offy, tmp);
}

/**
 * @brief Displays the customable settings on the screen
 * 
 * @param disp 
 * @param line 
 * @param g_offx 
 * @param g_offy 
 */
static void	_in_0_settings_help_msg_display_custom_settings(t_display *disp,
	int *line)
{
	char	**tmp;

	++(*line);
	to_mlx_str_put("4. SETTINGS", g_offx, g_nl * ++(*line) + g_offy);
	to_mlx_str_put("4. SETTINGS", g_offx, g_nl * (*line) + g_offy + 1);
	to_mlx_draw_line_h(disp->mlx, disp->win,
		(t_coord_i){17 + g_offx, g_nl * (*line) + g_offy + 3}, 50);
	to_mlx_str_put(MSG_HELP_SETTINGS_0, g_offx, g_nl * ++(*line) + g_offy);
	to_mlx_str_put(MSG_HELP_SETTINGS_1, g_offx, g_nl * ++(*line) + g_offy);
	to_mlx_str_put(MSG_HELP_SETTINGS_2, g_offx, g_nl * ++(*line) + g_offy);
	tmp = (char *[3]){"WALK SPEED:", XKeysymToString(KEY_WALK_SPEED),
		" + [ Mouse wheel ]"};
	_in_0_help_disp_to_win(disp, g_offx + 10, g_nl * ++(*line) + g_offy, tmp);
	tmp = (char *[3]){"SPEED_ROTATION KEYS:",
		XKeysymToString(KEY_ROT_SPEED_KEY), " + [ Mouse wheel ]"};
	_in_0_help_disp_to_win(disp, g_offx + 10, g_nl * ++(*line) + g_offy, tmp);
	tmp = (char *[3]){"SPEED_ROTATION MOUSE:",
		XKeysymToString(KEY_ROT_SPEED_MOUSE), " + [ Mouse wheel ]"};
	_in_0_help_disp_to_win(disp, g_offx + 10, g_nl * ++(*line) + g_offy, tmp);
	tmp = (char *[3]){"FOV:", XKeysymToString(KEY_FOV), " + [ Mouse wheel ]"};
	_in_0_help_disp_to_win(disp, g_offx + 10, g_nl * ++(*line) + g_offy, tmp);
	tmp = (char *[3]){"ZOOM_MINIMAP:", XKeysymToString(KEY_MINI_ZOOM),
		" + [ Mouse wheel ]"};
	_in_0_help_disp_to_win(disp, g_offx + 10, g_nl * ++(*line) + g_offy, tmp);
}

/**
 * @brief displays commands settings with a specific pattern
 * 
 * @param disp 
 * @param x 
 * @param y 
 * @param tab the differents strings to display
 */
static void	_in_0_help_disp_to_win(t_display *disp, int x, int y,
		char **tab)
{
	char	buf[150];
	int		i;
	int		j;

	mlx_string_put(disp->mlx, disp->win, x, y, 0xffffff, "- ");
	x += 10;
	mlx_string_put(disp->mlx, disp->win, x, y, 0xffffff, tab[0]);
	i = -1;
	j = 1;
	buf[0] = '[';
	buf[1] = ' ';
	while (tab[1] && tab[1][++i] && j < 146)
		buf[++j] = tab[1][i];
	i = -1;
	buf[++j] = ' ';
	buf[++j] = ']';
	while (tab[2] && tab[2][++i] && j < 148)
		buf[++j] = tab[2][i];
	buf[j + 1] = 0;
	mlx_string_put(disp->mlx, disp->win, x + HELP_DISP_OFFSET,
		y, 0xffffff, buf);
}
