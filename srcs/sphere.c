#include "../incl/miniRT.h"

double	contactsp(t_sp sphere, t_ray ray, t_var *p)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	root;

	a = vecnorm(ray.direction);
	b = vecdot(vecsub(ray.origin, sphere.xyz), ray.direction);
	c = vecnorm(vecsub(ray.origin, sphere.xyz)) - sphere.height * sphere.height;
	delta = b * b - a * c;
	if (delta < 0)
		return (0);
	if ((-b + sqrt(delta)) / a < 0)
		return (0);
	if ((-b - sqrt(delta)) / a > 0)
		root = (-b - sqrt(delta)) / a;
	else
		root = (-b + sqrt(delta)) / a;
	p->data->po = vecadd(ray.origin, vecmult(ray.direction, root));
	p->data->no = getnormalized(vecsub(p->data->po, sphere.xyz));
	return (root);
}
