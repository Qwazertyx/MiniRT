/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:57:21 by mlagrang          #+#    #+#             */
/*   Updated: 2022/11/04 13:00:50 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

t_vec	newvec(double x, double y, double z)
{
	t_vec	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

//t_vec	vecdiv(t_vec v1, double mult)
//{
//	t_vec	new;
//
//	new.x = v1.x / mult;
//	new.y = v1.y / mult;
//	new.z = v1.z / mult;
//	return (new);
//}

double	vecdot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	getnormalized(t_vec v1)
{
	double	norm;
	t_vec	new;

	norm = sqrt(vecnorm(v1));
	new.x = v1.x / norm;
	new.y = v1.y / norm;
	new.z = v1.z / norm;
	return (new);
}

void	normalize(t_vec v1)
{
	double	norm;

	norm = sqrt(vecnorm(v1));
	v1.x /= norm;
	v1.y /= norm;
	v1.z /= norm;
}

double	vecnorm(t_vec v1)
{
	return (v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
}
