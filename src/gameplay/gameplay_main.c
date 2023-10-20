/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:35:18 by acardona          #+#    #+#             */
/*   Updated: 2023/10/20 02:08:30 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"
#include "../../includes/raycasting.h"

#ifdef BONUS

/**
 * @brief function that loop to generate the frames according to the inputs
 * 
 * @param elem void * pointer to the t_general structure
 * @return int 0 anyway, necessary for the mlx
 */
int	game_looping(void *elem)
{
	static t_general		*gen;
	size_t					delay;
	static size_t			last_time = 0;
	register size_t			tmp_time;
	void					*img;

	gen = elem;
	tmp_time = to_getime();
	delay = tmp_time - last_time;
	last_time = tmp_time;
	game_move_player(gen, (t_vector_f){
		(float)(gen->next_moove[GO_RIGHT] - gen->next_moove[GO_LEFT]),
		(float)(gen->next_moove[GO_FORWARD] - gen->next_moove[GO_BACK])},
		delay);
	game_turn_head(gen, gen->next_moove[TURN_R] - gen->next_moove[TURN_L],
		delay);
	if (ft_isinset(gen->map.map[(int)gen->player.p_co.x]
			[(int)gen->player.p_co.y].type, "1 "))
		img = gen->disp.img_out_map->img;
	else
		img = r_frame_construction(gen, tmp_time);
	mlx_put_image_to_window(gen->disp.mlx, gen->disp.win, img, 0, 0);
	return (0);
}

#else

int	game_looping(void *elem)
{
	static t_general		*gen;
	void					*img;

	gen = elem;
	game_move_player(gen, (t_vector_f){
		(float)(gen->next_moove[GO_RIGHT] - gen->next_moove[GO_LEFT]),
		(float)(gen->next_moove[GO_FORWARD] - gen->next_moove[GO_BACK])},
		FIXED_DELAY);
	game_turn_head(gen, gen->next_moove[TURN_R] - gen->next_moove[TURN_L],
		FIXED_DELAY);
	if (ft_isinset(gen->map.map[(int)gen->player.p_co.x]
			[(int)gen->player.p_co.y].type, "1 "))
		img = gen->disp.img_out_map->img;
	else
		img = r_frame_construction(gen, 0);
	mlx_put_image_to_window(gen->disp.mlx, gen->disp.win, img,
		0, 0);
	return (0);
}
#endif

/**
 * @brief turns the player head in the given direction. the angle increment is
 *		calculated based on the rotational speed and the fps
 * 
 * @param gen 
 * @param direction 
 * @param delay in ms since the last frame
 */
void	game_turn_head(t_general *gen, t_head_rotate direction, size_t delay)
{
	if (!direction)
		return ;
	gen->player.p_angle += (float)direction
		* gen->settings.key_turn_speed * delay;
	while (gen->player.p_angle > 2 * M_PI)
		gen->player.p_angle -= 2 * M_PI;
	while (gen->player.p_angle < 0)
		gen->player.p_angle += 2 * M_PI;
}

/**
 * @brief if a non null direction is given the player position is modified in
 *		this direction by a step based on the wakl speed and the fps 
 * 
 * @param gen 
 * @param direction 
 * @param delay in ms since the last frame
 */
void	game_move_player(t_general *gen, t_vector_f direction, size_t delay)
{
	if (!direction.x && !direction.y)
		return ;
	if (direction.x && direction.y)
	{
		direction.x *= SQRT2INV;
		direction.y *= SQRT2INV;
	}
	gen->player.p_co.x += gen->settings.walk_speed * delay
		* (direction.x * cos(gen->player.p_angle)
			+ direction.y * sin(gen->player.p_angle));
	if (gen->player.p_co.x > gen->map.x_max - DIST_WALL_MIN)
		gen->player.p_co.x = gen->map.x_max - DIST_WALL_MIN;
	else if (gen->player.p_co.x < DIST_WALL_MIN)
		gen->player.p_co.x = DIST_WALL_MIN;
	gen->player.p_co.y += gen->settings.walk_speed * delay
		* (direction.y * cos(gen->player.p_angle)
			- direction.x * sin(gen->player.p_angle));
	if (gen->player.p_co.y > gen->map.y_max - DIST_WALL_MIN)
		gen->player.p_co.y = gen->map.y_max - DIST_WALL_MIN;
	else if (gen->player.p_co.y < DIST_WALL_MIN)
		gen->player.p_co.y = DIST_WALL_MIN;
}
