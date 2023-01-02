/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorscalcul.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:01:57 by mlagrang          #+#    #+#             */
/*   Updated: 2022/11/04 13:01:58 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

t_vec	veccross(t_vec v1, t_vec v2)
{
	return (newvec(v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x));
}

t_vec	vecmult(t_vec v1, double mult)
{
	t_vec	new;

	new.x = v1.x * mult;
	new.y = v1.y * mult;
	new.z = v1.z * mult;
	return (new);
}

t_vec	vecsub(t_vec v1, t_vec v2)
{
	t_vec	new;

	new.x = v1.x - v2.x;
	new.y = v1.y - v2.y;
	new.z = v1.z - v2.z;
	return (new);
}

t_vec	vecadd(t_vec v1, t_vec v2)
{
	t_vec	new;

	new.x = v1.x + v2.x;
	new.y = v1.y + v2.y;
	new.z = v1.z + v2.z;
	return (new);
}

t_vec	vecadd3(t_vec v1, t_vec v2, t_vec v3)
{
	t_vec	new;

	new.x = v1.x + v2.x + v3.x;
	new.y = v1.y + v2.y + v3.y;
	new.z = v1.z + v2.z + v3.z;
	return (new);
}
