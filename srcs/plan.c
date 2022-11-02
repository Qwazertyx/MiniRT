#include "../incl/miniRT.h"

double	contactpl(t_pl plane, t_ray ray, t_var *p)
{
	double	denom;
	double	t;

	denom = vecdot(plane.way, ray.direction);
	t = 0;
	if (fabs(denom) > 0.000000001)
		t = vecdot(vecsub(plane.xyz, ray.origin), plane.way) / denom;
	if (t < 0.000000001)
		return (0);
	p->data->po = vecadd(ray.origin, vecmult(ray.direction, t));
	p->data->no = plane.way;
	return (t);
}

double	shadow_contactpl(t_pl plane, t_ray ray, t_var *p)
{
	float ddot = vecdot(ray.direction, plane.way);
	if (fabs(ddot) < 1E-9)
		return (0);
	double t = vecdot(vecsub(plane.xyz, ray.origin), plane.way) / ddot;
	if (t < 0.0)
		return (0);
	return (t);
}
