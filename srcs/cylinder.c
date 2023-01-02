/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:52:20 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/07 14:23:15 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

t_pl	createcap(t_cy cyl, int way)
{
	t_pl	cap;

	assignrgb(cap.rgb, cyl.rgb);
	cap.way = vecmult(cyl.way, way);
	if (way == 1)
	{
		cap.xyz = vecadd(cyl.xyz, vecmult(getnormalized(cyl.way), \
		cyl.height));
	}
	else
		cap.xyz = cyl.xyz;
	return (cap);
}

double	contactcap(t_cy cyl, t_ray ray, t_var *p)
{
	t_pl	test;
	double	denom;
	double	t;
	double	d2;
	t_vec	v;

	test = createcap(cyl, 1);
	denom = vecdot(test.way, ray.direction);
	t = 0;
	if (fabs(denom) > 0.000000001)
		t = vecdot(vecsub(test.xyz, ray.origin), test.way) / denom;
	if (t < 0.000000001)
		return (0);
	if (t)
	{
		v = vecsub(vecadd(ray.origin, vecmult(ray.direction, t)), test.xyz);
		d2 = vecdot(v, v);
		if (sqrtf(d2) <= cyl.width)
		{
			p->data->po = vecadd(ray.origin, vecmult(ray.direction, t));
			p->data->no = test.way;
			return (t);
		}
	}
	return (0);
}

double	contactcap2(t_cy cyl, t_ray ray, t_var *p)
{
	t_pl	test;
	double	denom;
	double	t;
	double	d2;
	t_vec	v;

	test = createcap(cyl, -1);
	denom = vecdot(test.way, ray.direction);
	t = 0;
	if (fabs(denom) > 0.000000001)
		t = vecdot(vecsub(test.xyz, ray.origin), test.way) / denom;
	if (t < 0.000000001)
		return (0);
	if (t)
	{
		v = vecsub(vecadd(ray.origin, vecmult(ray.direction, t)), test.xyz);
		d2 = vecdot(v, v);
		if (sqrtf(d2) <= cyl.width)
		{
			p->data->po = vecadd(ray.origin, vecmult(ray.direction, t));
			p->data->no = test.way;
			return (t);
		}
	}
	return (0);
}

t_vec	precontactcy(t_cy cyl, t_ray ray, t_vec a, float *abc)
{
	t_vec	b;
	double	r;
	t_vec	d;
	t_vec	x;
	t_vec	y;

	b = vecadd(cyl.xyz, vecmult(cyl.way, cyl.height));
	r = cyl.width;
	d = getnormalized(vecsub(b, a));
	x = vecsub(ray.direction, vecmult(d, vecdot(ray.direction, d)));
	y = vecsub(vecsub(ray.origin, a),
			vecmult(d, vecdot(vecsub(ray.origin, a), d)));
	abc[0] = vecnorm(x);
	abc[1] = 2 * vecdot(x, y);
	abc[2] = vecnorm(y) - r * r;
	return (d);
}

double	contactcy(t_cy cyl, t_ray ray, t_var *p)
{
	double	t[2];
	double	delta;
	float	abc[3];
	float	dp;
	t_vec	d;

	d = precontactcy(cyl, ray, cyl.xyz, abc);
	delta = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (delta < 0)
		return (0);
	t[0] = (-abc[1] + sqrt(delta)) / (2 * abc[0]);
	if (t[0] < 0)
		return (0);
	t[1] = (-abc[1] - sqrt(delta)) / (2 * abc[0]);
	if (t[1] > 0)
		t[0] = t[1];
	p->data->po = vecadd(ray.origin, vecmult(ray.direction, t[0]));
	dp = vecdot(vecsub(p->data->po, cyl.xyz), d);
	if (dp < 0 || dp > cyl.height)
		return (0);
	p->data->no = getnormalized(vecsub(p->data->po,
				vecadd(cyl.xyz, vecmult(d, dp))));
	return (t[0]);
}
