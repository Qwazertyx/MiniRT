#include "../incl/miniRT.h"

double contactcap(t_cy cyl, t_ray ray, t_var *p)
{
	t_pl test;
	test.exist = 1;
	assignrgb(test.rgb, cyl.rgb);
	test.way = cyl.way;
	test.xyz = vecadd(cyl.xyz, vecmult(cyl.way, cyl.height));

	double	denom;
	double	t;

	denom = vecdot(test.way, ray.direction);
	t = 0;
	if (fabs(denom) > 0.000000001)
		t = vecdot(vecsub(test.xyz, ray.origin), test.way) / denom;
	if (t < 0.000000001)
		return (0);
	if (t)
	{
		t_vec v = vecsub(vecadd(ray.origin, vecmult(ray.direction, t)), test.xyz);
		double d2 = vecdot(v, v);
		if (sqrtf(d2) <= cyl.width)
		{
			p->data->po = vecadd(ray.origin, vecmult(ray.direction, t));
			p->data->no = test.way;
			return (t);
		}
	}
	return (0);
}

double contactcap2(t_cy cyl, t_ray ray, t_var *p)
{
	t_pl test;
	test.exist = 1;
	assignrgb(test.rgb, cyl.rgb);
	test.way = vecmult(cyl.way, -1);
	test.xyz = cyl.xyz;

	double	denom;
	double	t;

	denom = vecdot(test.way, ray.direction);
	t = 0;
	if (fabs(denom) > 0.000000001)
		t = vecdot(vecsub(test.xyz, ray.origin), test.way) / denom;
	if (t < 0.000000001)
		return (0);
	if (t)
	{
		p->data->po = vecadd(ray.origin, vecmult(ray.direction, t));
		p->data->no = test.way;
		t_vec v = vecsub(vecadd(ray.origin, vecmult(ray.direction, t)), test.xyz);
		double d2 = vecdot(v, v);
		if (sqrtf(d2) <= cyl.width)
		{
			p->data->po = vecadd(ray.origin, vecmult(ray.direction, t));
			p->data->no = test.way;
			return (t);
		}
	}
	return (0);
}

double	contactcy(t_cy cyl, t_ray ray, t_var *p)
{
	// double	a;
	// double	b;
	// double	c;
	// double	delta;
	// double	root;
	// double	t1;
	// double	t2;
	// double	z1;
	// double	z2;

	// a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	// b = 2 * ray.direction.x * (ray.origin.x - cyl.xyz.x) + 2 * ray.direction.z * (ray.origin.z - cyl.xyz.z);
	// c = (ray.origin.x - cyl.xyz.x) * (ray.origin.x - cyl.xyz.x) + (ray.origin.z - cyl.xyz.z) * (ray.origin.z - cyl.xyz.z) - cyl.width * cyl.width;
	// delta = b * b - 4 * a * c;
	// if (delta < 0)
	// 	return (0);
	// t1 = (-1 * b - sqrt(delta)) / (2 * a);
	// t2 = (-1 * b + sqrt(delta)) / (2 * a);
	// z1 = ray.origin.y + t1 * ray.direction.y;
	// z2 = ray.origin.y + t2 * ray.direction.y;
	// dprintf(2, "z1 = %f, z2 = %f\n", z1, z2);
	// if (z1 < cyl.height + cyl.xyz.y && z1 > cyl.xyz.y)
	// 	root = t1;
	// else if (z2 < cyl.height + cyl.xyz.y && z2 > cyl.xyz.y)
	// 	root = t2;
	// else
	// 	return (0);

	// ----------------------------------

	double root;
	t_vec A = cyl.xyz;
	t_vec B = vecadd(cyl.xyz, vecmult(cyl.way, cyl.height));
	double R = cyl.width;
	t_vec d = getnormalized(vecsub(B, A));
	t_vec X = vecsub(ray.direction, vecmult(d, vecdot(ray.direction, d)));
	t_vec Y = vecsub(vecsub(ray.origin, A), vecmult(d, vecdot(vecsub(ray.origin, A), d)));
	float a = vecnorm(X);
	float b = 2 * vecdot(X, Y);
	float c = vecnorm(Y) - R * R;
	float delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	float sdelta = sqrt(delta);
	float t2 = (-b + sdelta) / (2 * a);
	if (t2 < 0)
		return (0);
	float t1 = (-b - sdelta) / (2 * a);
	if (t1 > 0)
		root = t1;
	else
		root = t2;
	p->data->po = vecadd(ray.origin, vecmult(ray.direction, root));
	t_vec P = p->data->po;
	double len = cyl.height;
	float dP = vecdot(vecsub(P, A), d);
	if (dP < 0 || dP > len)
		return (0);
	t_vec proj = vecadd(A, vecmult(d, dP));
	p->data->no = getnormalized(vecsub(P, proj));
	return (root);
}

double	shadow_contactcy(t_cy cyl, t_ray ray, t_var *p)
{

}
