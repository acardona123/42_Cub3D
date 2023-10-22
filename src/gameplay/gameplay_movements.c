/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:17:08 by acardona          #+#    #+#             */
/*   Updated: 2023/10/22 02:56:54 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

/**
 * @brief turns the player head in the given direction. the angle increment is
 *		calculated based on the rotational speed and the fps
 * 
 * @param gen 
 * @param direction direction of the rotation (<0 = left, >0 = right)
 * @param delay time in ms passed since the last rendering (use to keep a
 *		constant rotation velocity)
 */
void	gp_turn_head(t_general *gen, t_head_rotate direction, size_t delay)
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

#ifdef BONUS

static void		_gp_move_player_avoid_wall(t_map *map, t_coord_f *target_pt);
inline static bool	_gp_is_obstacle(t_map *map, int x, int y);

/**
 * @brief mooves the player in the direction dir. It tries to do a step of
 *		delay * walk_speed (to keep a constant velocity independant of the fps).
 *		If their is an obstacle on the way the player stop. In any case if it
 *		ends too close to an obstacle it is repositioned at DIST_WALL_MIN from
 *		it.
 * 
 * @param gen 
 * @param dir_x vector representing the latteral (left-right) move direction
 * @param dir_y vector representing the front (forward-backward) move direction
 * @param delay time in ms passed since the last rendering (use to keep a
 *		constant movement velocity)
 */
void	gp_move_player(t_general *gen, float dir_x, float dir_y, size_t delay)
{
	t_hitpoint	hitpoint;
	t_coord_f	target_dest;

	if (!dir_x && !dir_y)
		return ;
	hitpoint = r_ray_hit(&gen->player.p_co, gen->player.p_angle + M_PI
			* ((dir_y == -1.) + 0.5 * dir_x), &gen->map);
	target_dest.x = gen->player.p_co.x + gen->settings.walk_speed * delay
		* ((dir_x && dir_y) * SQRT2INV + (!dir_x || !dir_y))
		* (dir_x * cos(gen->player.p_angle) + dir_y * sin(gen->player.p_angle));
	target_dest.y = gen->player.p_co.y + gen->settings.walk_speed * delay
		* ((dir_x && dir_y) * SQRT2INV + (!dir_x || !dir_y))
		* (dir_y * cos(gen->player.p_angle) - dir_x * sin(gen->player.p_angle));
	if (to_vector_norm_sqr(gen->player.p_co, hitpoint.pt_co)
		< to_vector_norm_sqr(gen->player.p_co, target_dest))//optimisable en norme absolue: |gen->player.p_co.x - hitpoint.pt_co.x| < |gen->player.p_co.x - target_dest.pt_co.x| || |gen->player.p_co.y - hitpoint.pt_co.y| < |gen->player.p_co.y - target_dest.pt_co.y|
	{
		gen->player.p_co.x = hitpoint.pt_co.x + DIST_WALL_MIN
			* ((hitpoint.hit_face == FACE_E) - (hitpoint.hit_face == FACE_W));
		gen->player.p_co.y = hitpoint.pt_co.y + DIST_WALL_MIN
			* ((hitpoint.hit_face == FACE_N) - (hitpoint.hit_face == FACE_S));
	}
	else
		gen->player.p_co = target_dest;
	_gp_move_player_avoid_wall(&gen->map, &gen->player.p_co);
}

/**
 * @brief updates the player position so that it is not too close to an obstacle
 *		(wall or door not open)
 * 
 * @param map pointer to the map structure
 * @param p_co pointer to the player position 
 */
static void	_gp_move_player_avoid_wall(t_map *map, t_coord_f *p_co)
{
	t_coord_i	p_int;
	t_coord_f	p_dec;

	p_int.x = (int)p_co->x;
	p_int.y = (int)p_co->y;
	p_dec.x = p_co->x - floor(p_co->x);
	p_dec.y = p_co->y - floor(p_co->y);
	if (p_dec.y < DIST_WALL_MIN && (!p_int.y
			|| _gp_is_obstacle(map, p_int.x, p_int.y - 1)))
		p_co->y = floor(p_co->y) + DIST_WALL_MIN;
	else if (1 - p_dec.y < DIST_WALL_MIN && (p_int.y == map->height - 1
			|| _gp_is_obstacle(map, p_int.x, p_int.y + 1)))
		p_co->y = ceil(p_co->y) - DIST_WALL_MIN;
	if (p_dec.x < DIST_WALL_MIN && (!p_int.x
			|| _gp_is_obstacle(map, p_int.x - 1, p_int.y)))
		p_co->x = floor(p_co->x) + DIST_WALL_MIN;
	else if (1 - p_dec.x < DIST_WALL_MIN && (p_int.x == map->width - 1
			|| _gp_is_obstacle(map, p_int.x + 1, p_int.y)))
		p_co->x = ceil(p_co->x) - DIST_WALL_MIN;
}

/**
 * @brief checks if the chunk is an obstacle (wall or door not opened)
 * 
 * @param map 
 * @param x 
 * @param y 
 * @return true 
 * @return false 
 */
inline static bool	_gp_is_obstacle(t_map *map, int x, int y)
{
	return (map->map[x][y].type == WALL || (map->map[x][y].type == DOOR
		&& map->map[x][y].status != DOOR_OPEN));
}

#else

/**
 * @brief if a non null direction is given the player position is modified in
 *		this direction by a step based on the wakl speed and the fps 
 * 
 * @param gen 
 * @param direction 
 * @param delay in ms since the last frame
 */
void	gp_move_player(t_general *gen, float dir_x, float dir_y, size_t delay)
{
	if (!dir_x && !dir_y)
		return ;
	if (dir_x && dir_y)
	{
		dir_x *= SQRT2INV;
		dir_y *= SQRT2INV;
	}
	gen->player.p_co.x += gen->settings.walk_speed * delay
		* (dir_x * cos(gen->player.p_angle)
			+ dir_y * sin(gen->player.p_angle));
	if (gen->player.p_co.x > gen->map.x_max - DIST_WALL_MIN)
		gen->player.p_co.x = gen->map.x_max - DIST_WALL_MIN;
	else if (gen->player.p_co.x < DIST_WALL_MIN)
		gen->player.p_co.x = DIST_WALL_MIN;
	gen->player.p_co.y += gen->settings.walk_speed * delay
		* (dir_y * cos(gen->player.p_angle)
			- dir_x * sin(gen->player.p_angle));
	if (gen->player.p_co.y > gen->map.y_max - DIST_WALL_MIN)
		gen->player.p_co.y = gen->map.y_max - DIST_WALL_MIN;
	else if (gen->player.p_co.y < DIST_WALL_MIN)
		gen->player.p_co.y = DIST_WALL_MIN;
}

#endif
