#include "../incl/miniRT.h"

//Lumière ambiante :Camera :Lumière :Sphere:Plan : Cylindre :
void	mypixelput(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (int)(y * data->line_length + x
			* (data->bits_per_pixel * 0.125));
	if (y < data->winwidth && x < data->winlength)
	{
		//printf("%d %d - ",x, data->winlength);
		//printf("%d %d\n",y, data->winwidth);
		*(unsigned int *)dst = color;
	}
}

//int	setfacenormal(t_ray ray, t_vec outwardnormal, t_var *p)
//{
//	if (vecdot(ray.direction, outwardnormal) < 0)
//		p->hitrec.frontface = 1;
//	else
//		p->hitrec.frontface = 0;
//	if (p->hitrec.frontface == 1)
//		p->hitrec.normal = outwardnormal;
//	else
//		p->hitrec.normal = vecmult(outwardnormal, -1);
//}

/*
// a = vecdot(ray.direction, ray.direction);
// b = 2 * vecdot(vecsub(ray.origin, sphere.xyz), ray.direction);
// c = vecdot(vecsub(ray.origin, sphere.xyz), vecsub(ray.origin, sphere.xyz))
// 	- sphere.height * sphere.height;
// delta = b * b - 4 * a * c;
//i used a simplified version to be faster
//po intersection
//no normal
*/

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

double	contactpl(t_pl plane, t_ray ray, t_var *p)
{
	double	denom;
	double	t;

	denom = vecdot(plane.way, ray.direction);
	t = 0;
	if (abs(denom) > 0.00001)
		t = vecdot(vecsub(plane.xyz, ray.origin), plane.way) / denom;
	if (t < 0.00001)
		return (0);
	p->data->po = vecadd(ray.origin, vecmult(ray.direction, t));
	p->data->no = plane.way;
	return (t);
}

int	colortrgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	colorrgb(int r, int g, int b)
{
	int	t;

	t = 0;
	return (t << 24 | r << 16 | g << 8 | b);
}

double	goodlux(double num)
{
	if (num < 0)
		return (0);
	if (num > 255)
		return (255);
	return (num);
}

double	intershadow(t_ray myray, t_var *p)
{
	t_ray	rebund;
	int		i;
	double	dist;
	double	min_t;

	rebund.origin = vecadd(p->data->smpo, vecmult(p->data->smno, 0.01));
	rebund.direction = getnormalized(vecsub(p->l->xyz, p->data->smpo));
	i = 0;
	min_t = 99999999999999;
	while (p->sp[i].exist)
	{
		dist = contactsp(p->sp[i], rebund, p);
		if (dist && dist < min_t)
		{
			min_t = dist;
			p->data->shadowno = p->data->no;
			p->data->shadowpo = p->data->po;
		}
		i++;
	}
	i = 0;
	while (p->pl[i].exist)
	{
		dist = contactpl(p->pl[i], rebund, p);
		if (dist && dist < min_t)
		{
			min_t = dist;
			p->data->smno = p->data->no;
			p->data->smpo = p->data->po;
		}
		i++;
	}
	if (min_t * min_t > vecnorm(vecsub(p->l->xyz, p->data->shadowpo)))
		return (0.9);
	return (0);
}

double	returnluxa(t_vec lux, unsigned char *color, t_var *p)
{
	return (colorrgb(goodlux(lux.x + goodlux(p->a->rgb[0] * p->a->ratio \
	* color[0] / 255)), \
					goodlux(lux.y + goodlux (p->a->rgb[1] * p->a->ratio \
	* color[1] / 255)), \
					goodlux(lux.z + goodlux(p->a->rgb[2] * p->a->ratio \
	* color[2] / 255))));
}

double	raycolor(t_ray myray, double min_t, t_var *p, unsigned char *color)
{
	double	dist;
	t_vec	lux;

	lux = newvec(color[0], color[1], color[2]);
	p->data->depthmax--;
	if (min_t != 99999999999999)
	{
		lux = vecmult(lux, intershadow(myray, p));
		lux = vecmult(lux, p->l->ratio * 50000 * goodlux(vecdot(\
		getnormalized(vecsub(p->l->xyz, p->data->smpo)), p->data->smno) \
		/ vecnorm(vecsub(p->l->xyz, p->data->smpo))));
		return (returnluxa(lux, color, p));
	}
	return (colorrgb(0, 0, 0));
}

void	assignrgb(unsigned char *dst, unsigned char *src)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		dst[i] = src[i];
		i++;
	}
}

double	inter(t_ray myray, t_var *p)
{
	int				i;
	unsigned char	rgb[3];
	double			min_t;
	double			dist;

	i = 0;
	min_t = 99999999999999;
	while (p->sp[i].exist)
	{
		dist = contactsp(p->sp[i], myray, p);
		if (dist && dist < min_t)
		{
			min_t = dist;
			assignrgb(rgb, p->sp[i].rgb);
			p->data->smno = p->data->no;
			p->data->smpo = p->data->po;
		}
		i++;
	}
	i = 0;
	while (p->pl[i].exist)
	{
		dist = contactpl(p->pl[i], myray, p);
		if (dist && dist < min_t)
		{
			min_t = dist;
			assignrgb(rgb, p->pl[i].rgb);
			p->data->smno = p->data->no;
			p->data->smpo = p->data->po;
		}
		i++;
	}
	return (raycolor(myray, min_t, p, rgb));
}

void	algo(t_var *p, int x, int y)
{
	t_ray	myray;
	int		i;
	double	color;

	myray.origin = p->c->xyz;
	myray.direction = newvec(x - p->data->winwidth / 2, y - p->data->winlength
			/ 2, -p->data->winwidth / (2 * tan((p->c->fov * M_PI / 180) / 2)));
	normalize(myray.direction);
	i = 0;
	color = 0;
	while (i < p->data->sampleppix)
	{
		p->data->depthmax = 50;
		color += inter(myray, p);
		i++;
	}
	mypixelput(p->data, p->data->winwidth - x, y, color / p->data->sampleppix);
	//essayer de changer le sens soon
}

//i = H = x = len
//j = W = y = wid

void	generator(t_var *p)
{
	int	x;
	int	y;

	x = 0;
	while (x < p->data->winlength)
	{
		y = 0;
		while (y < p->data->winwidth)
		{
			algo(p, x, y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(p->data->mlx, p->data->win, p->data->img, 0, 0);
}
