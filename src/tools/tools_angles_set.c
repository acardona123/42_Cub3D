/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_angles_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:19:27 by acardona          #+#    #+#             */
/*   Updated: 2023/12/01 20:45:50 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

/**
 * @brief calculates the angle_offset to add to the player angle to obtain each
 *	ray's angle to point toward each pixel column of the screen.
 * 
 * @param old_fov point to gen->settings->fov
 * @param new_fov new fov used to calculate the angleset
 * @param angle_set pointer to gen->angles_set
 * @param angle_correc  pointer to gen->angles_correc, containing the cosinus of
 *			each angle_set element
 */
void	to_angle_set_init(float *old_fov, float new_fov, double *angles_set,
	double *angle_correc)
{
	int		idx;
	double	focal;

	*old_fov = new_fov;
	focal = WIN_WIDTH / (2 * tan(new_fov / 2));
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

	to_angle_set_init(&gen.settings.fov, DEFAULT_FOV, gen.angles_set);
	i = -1;
	while (++i < WIN_WIDTH)
		printf("%d: %f (%f deg) : %f (%f deg) \n", i, DEFAULT_FOV,
		DEFAULT_FOV * 180 / M_PI, gen.angles_set[i],
		gen.angles_set[i] * 180 / M_PI);
	return (0);
}
*/