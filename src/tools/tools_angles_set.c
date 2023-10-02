/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_angles_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:19:27 by acardona          #+#    #+#             */
/*   Updated: 2023/10/02 20:01:05 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

static void	_tools_angle_calc_const_step(float fov, double *angles_set);
static void	_tools_angle_calc_cos_step(float fov, double *angles_set);

/**
 * @brief calculates the angle_offset to add to the player angle to obtain each
 *	ray's angle to point toward each pixel column of the screen.
 * 
 * @param old_fov point to gen->fov
 * @param new_fov new fov used to calculate the angleset
 * @param angle_set pointer to gen->angles_set
 */
void	to_angle_set_init(float *old_fov, float new_fov, double *angles_set)
{
	*old_fov = new_fov;
	if (1)//const_step
		_tools_angle_calc_const_step(new_fov, angles_set);
	else
		_tools_angle_calc_cos_step(new_fov, angles_set);
}

/**
 * @brief Calculates the angles with a constant step (linear model)
 * 
 * @param fov 
 * @param table_dest 
 */
static void	_tools_angle_calc_const_step(float fov, double *angles_set)
{
	int		idx;

	idx = -1;
	while (++idx < WIN_WIDTH)
		angles_set[idx] = fov * idx / WIN_WIDTH - 0.5 * fov;
}

static void	_tools_angle_calc_cos_step(float fov, double *angles_set)
{
	int		idx;
	float amplitude = 0.1;

	angles_set[0] = -fov / 2;
	idx = 0;
	while (++idx < WIN_WIDTH)
	{
		angles_set[idx] = angles_set[idx - 1] + fov * (1 - amplitude * cos(2 * M_PI * idx / (WIN_WIDTH - 1))) / WIN_WIDTH;
		printf("idx: %d => angle = %f\n", idx, angles_set[idx]);
	}
}

/*
#include "../../includes/shared.h"
int main()
{
	int 		i;
	t_general	gen = {0};

	to_angle_set_init(&gen.fov, DEFAULT_FOV, gen.angles_set);
	i = -1;
	while (++i < WIN_WIDTH)
		printf("%d: %f (%f deg) : %f (%f deg) \n", i, DEFAULT_FOV,
		DEFAULT_FOV * 180 / M_PI, gen.angles_set[i],
		gen.angles_set[i] * 180 / M_PI);
	return (0);
}
*/