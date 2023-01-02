/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorsnotused.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:58:30 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/13 14:25:10 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

t_vec	vecat(t_ray ray, double t)
{
	return (vecadd(ray.origin, vecmult(ray.direction, t)));
}

t_vec	vecunit(t_vec v1)
{
	return (vecdiv(v1, veclen(v1)));
}

double	veclen(t_vec v1)
{
	return (sqrt(vecnorm(v1)));
}

t_vec	vecdiv(t_vec v1, double mult)
{
	t_vec	new;

	new = vecmult(v1, 1 / mult);
	return (new);
}

t_vec	met_a_un(t_vec v1)
{
	double	mult;

	if (fabs(v1.x) >= fabs(v1.y) && fabs(v1.x) >= fabs(v1.z))
		mult = fabs(v1.x);
	if (fabs(v1.y) >= fabs(v1.x) && fabs(v1.y) >= fabs(v1.z))
		mult = fabs(v1.y);
	if (fabs(v1.z) >= fabs(v1.x) && fabs(v1.z) >= fabs(v1.y))
		mult = fabs(v1.z);
	v1.x /= mult;
	v1.y /= mult;
	v1.z /= mult;
	return (v1);
}
