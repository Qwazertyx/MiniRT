#include "../incl/miniRT.h"

t_vec	vecadd(t_vec v1, t_vec v2)
{
	t_vec	new;

	new.x = v1.x + v2.x;
	new.y = v1.y + v2.y;
	new.z = v1.z + v2.z;
	return (new);
}

t_vec	newvec(double x, double y, double z)
{
	t_vec	new;

	new.x = x;
	new.y = y;
	new.z = z;
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

t_vec	vecmult(t_vec v1, double mult)
{
	t_vec	new;

	new.x = v1.x * mult;
	new.y = v1.y * mult;
	new.z = v1.z * mult;
	return (new);
}

t_vec	vecdiv(t_vec v1, double mult)
{
	t_vec	new;

	new = vecmult(v1, 1 / mult);
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

t_vec	veccross(t_vec v1, t_vec v2)
{
	return (newvec(v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x));
}

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

t_vec	vecunit(t_vec v1)
{
	return (vecdiv(v1, veclen(v1)));
}

double	veclen(t_vec v1)
{
	return (sqrt(vecnorm(v1)));
}

double	vecnorm(t_vec v1)
{
	return (v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
}

t_vec	vecat(t_ray ray, double t)
{
	return (vecadd(ray.origin, vecmult(ray.direction, t)));
}
