/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_angles_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:19:27 by acardona          #+#    #+#             */
/*   Updated: 2023/10/03 18:37:55 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

// static void	_tools_angle_calc_const_step(float fov, double *angles_set);
static void	_tools_angle_calc_adapted_step(float fov, double *angles_set,
				double *angle_correc);

/**
 * @brief calculates the angle_offset to add to the player angle to obtain each
 *	ray's angle to point toward each pixel column of the screen.
 * 
 * @param old_fov point to gen->fov
 * @param new_fov new fov used to calculate the angleset
 * @param angle_set pointer to gen->angles_set
 */
void	to_angle_set_init(float *old_fov, float new_fov, double *angles_set, double *angle_correc)
{
	*old_fov = new_fov;
	_tools_angle_calc_adapted_step(new_fov, angles_set, angle_correc);
}

/**
 * @brief Calculates the angles with a constant step (linear model)
 * 
 * @param fov 
 * @param table_dest 
 */
/*
static void	_tools_angle_calc_const_step(float fov, double *angles_set)
{
	int		idx;

	idx = -1;
	while (++idx < WIN_WIDTH)
		angles_set[idx] = fov * idx / WIN_WIDTH - 0.5 * fov;
}
*/

static void	_tools_angle_calc_adapted_step(float fov, double *angles_set,
	double *angle_correc)
{
	int		idx;
	double	focal;

	focal = WIN_WIDTH / (2 * tan(fov / 2));
	idx = -1;
	while (++idx < WIN_WIDTH)
	{
		angles_set[idx] = atan(((double)(idx - (double)WIN_WIDTH / 2)) / focal);
		angle_correc[idx] = cos(angles_set[idx]);
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