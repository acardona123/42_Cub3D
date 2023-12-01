/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_walk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:17:08 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 18:32:04 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gameplay.h"

static t_coord_f	_gp_walk_get_target(t_general *gen, float dir_x,
						float dir_y, size_t delay);

#ifdef BONUS

static const float	g_angle_dir[3][3] = {{5. * M_PI_4, 3. * M_PI_2, 7 * M_PI_4},
{M_PI, 0., 0.}, {3 * M_PI_4, M_PI_2, M_PI_4}};

static void			_gp_walk_slide_along_wall(t_general *gen, t_coord_f target,
						int dir_x, int dir_y);

/**
 * @brief moves the player in the direction dir. It tries to do a step of
 *		delay * walk_speed (to keep a constant velocity independant of the fps).
 *		If their is an obstacle on the way the player slides along it.
 * 
 * @param gen 
 * @param dir_x vector representing the latteral (left-right) move direction
 * @param dir_y vector representing the front (forward-backward) move direction
 * @param delay time in ms passed since the last rendering (use to keep a
 *		constant movement velocity)
 */
void	gp_walk(t_general *gen, int dir_xp, int dir_yp, size_t delay)
{
	t_hitpoint	hit_pt;
	t_coord_f	target;

	if (!dir_xp && !dir_yp)
		return ;
	target = _gp_walk_get_target(gen, dir_xp, dir_yp, delay);
	hit_pt = r_ray_hit(gen, (t_ray_params){ray_walk, to_getime(), gen->player
			.p_co, gen->player.p_angle + g_angle_dir[dir_xp + 1][dir_yp + 1]});
	if (to_vector_norm_sqr(gen->player.p_co, hit_pt.pt_co)
		> to_vector_norm_sqr(gen->player.p_co, target))
	{
		gen->player.p_co.x = target.x + EPSILON * ((hit_pt.hit_face == FACE_E)
				- (hit_pt.hit_face == FACE_W));
		gen->player.p_co.y = target.y + EPSILON * ((hit_pt.hit_face == FACE_N)
				- (hit_pt.hit_face == FACE_S));
	}
	else
	{
		gen->player.p_co = hit_pt.pt_co;
		_gp_walk_slide_along_wall(gen, target,
			((hit_pt.hit_face == FACE_N) || (hit_pt.hit_face == FACE_S))
			* (1 - 2 * (hit_pt.pt_co.x > target.x)),
			((hit_pt.hit_face == FACE_E) || (hit_pt.hit_face == FACE_W))
			* (1 - 2 * (hit_pt.pt_co.y > target.y)));
	}
}

/**
 * @brief when a player trying to move to a target point touches an obstacle.
 *		In this case it moves in the direction parallele to the wall until it
 *		reaches another obstacle or the projection of the target point on this
 *		trajectory
 * 
 * @param gen 
 * @param target the point given by _gp_walk_get_target 
 * @param dir the director vector of the gliding movement
 */
static void	_gp_walk_slide_along_wall(t_general *gen, t_coord_f target,
	int dir_x, int dir_y)
{
	t_hitpoint	hitpoint;

	if (dir_x)
	{
		hitpoint = r_ray_hit(gen, (t_ray_params){ray_walk, to_getime(),
				gen->player.p_co, g_angle_dir[dir_x + 1][1]});
		if ((dir_x > 0 && hitpoint.pt_co.x <= target.x)
			|| (dir_x < 0 && hitpoint.pt_co.x >= target.x))
			gen->player.p_co.x = hitpoint.pt_co.x;
		else
			gen->player.p_co.x = target.x;
	}
	else
	{
		hitpoint = r_ray_hit(gen, (t_ray_params){ray_walk, to_getime(),
				gen->player.p_co, g_angle_dir[1][dir_y + 1]});
		if ((dir_y > 0 && hitpoint.pt_co.y <= target.y)
			|| (dir_y < 0 && hitpoint.pt_co.y >= target.y))
			gen->player.p_co.y = hitpoint.pt_co.y;
		else
			gen->player.p_co.y = target.y;
	}
}

#else

/**
 * @brief if a non null direction is given the player position is modified in
 *		this direction by a step fixed step (walk_speed * FIXED_DELAY) 
 * 
 * @param gen 
 * @param direction 
 * @param delay ignored
 */
void	gp_walk(t_general *gen, int dir_xp, int dir_yp, size_t delay)
{
	(void)delay;
	if (!dir_xp && !dir_yp)
		return ;
	gen->player.p_co = _gp_walk_get_target(gen, dir_xp, dir_yp, FIXED_DELAY);
	if (gen->player.p_co.x > gen->map.x_max - DIST_WALL_MIN)
		gen->player.p_co.x = gen->map.x_max - DIST_WALL_MIN;
	else if (gen->player.p_co.x < DIST_WALL_MIN)
		gen->player.p_co.x = DIST_WALL_MIN;
	if (gen->player.p_co.y > gen->map.y_max - DIST_WALL_MIN)
		gen->player.p_co.y = gen->map.y_max - DIST_WALL_MIN;
	else if (gen->player.p_co.y < DIST_WALL_MIN)
		gen->player.p_co.y = DIST_WALL_MIN;
}

#endif

/**
 * @brief Calulate the target player position based on its current position,
 *		the movement direction, the speed and the delay between frames. This
 *		does not take into account the presence of walls or mapborders.
 * 
 * @param gen 
 * @param dir_x -1, 0 or 1. Abscisse the movement vector
 * @param dir_y idem dir_x om y axis
 * @param delay 
 * @return t_coord_f the coordinates of the targeted position after the movement
 */
static t_coord_f	_gp_walk_get_target(t_general *gen, float dir_x,
	float dir_y, size_t delay)
{
	t_coord_f	target;

	if (dir_x && dir_y)
	{
		dir_x *= M_SQRT1_2;
		dir_y *= M_SQRT1_2;
	}
	target.x = gen->player.p_co.x + gen->settings.walk_speed * delay
		* (dir_x * cos(gen->player.p_angle) + dir_y * sin(gen->player.p_angle));
	target.y = gen->player.p_co.y + gen->settings.walk_speed * delay
		* (dir_y * cos(gen->player.p_angle) - dir_x * sin(gen->player.p_angle));
	return (target);
}

/*
//tests
//https://www.geogebra.org/calculator/vhca2swr

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	t_general	gen;
	t_vector_f	direction_pref = {0, 1};
	size_t		delay = 23;//for distance calculation, big to test all
	//	collisions
	float		angle_deg = 0;

	gen = (t_general){0};
	init_main(ac, av, &gen);
	gen.player.p_co.x = 4.500000;
	gen.player.p_co.y = 2.02;
	// gen.player.p_co.x -= 0.5 + DIST_WALL_MIN;
	// gen.player.p_co.y += 0.5 - DIST_WALL_MIN;
	// gen.player.p_co.x -= .5;
	// gen.player.p_co.y += .5;
	gen.player.p_angle = angle_deg * M_PI / 180;
	int i = 100;
	while (--i)
	{

		printf("player: (%f, %f), %.2f deg\n", gen.player.p_co.x,
			gen.player.p_co.y,angle_deg);
		gp_walk(&gen, direction_pref.x, direction_pref.y, delay);
		printf("\n==> p_co = (%f, %f)\n\n", gen.player.p_co.x, gen.player.p_co.y);
	}
	direction_pref = (t_vector_f){1, 1};
	i = 100;
	while (--i)
	{

		printf("player: (%f, %f), %.2f deg\n", gen.player.p_co.x,
			gen.player.p_co.y,angle_deg);
		gp_walk(&gen, direction_pref.x, direction_pref.y, delay);
		printf("\n==> p_co = (%f, %f)\n\n", gen.player.p_co.x, gen.player.p_co.y);
	}
	gp_walk(&gen, direction_pref.x, direction_pref.y, delay);
	printf("\n==> p_co = (%f, %f)\n", gen.player.p_co.x, gen.player.p_co.y);

	end_destroy_general(&gen);
	return (0);
}
*/