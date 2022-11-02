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

	rebund.origin = vecadd(p->data->smpo, vecmult(p->data->smno, 0.000000000001));
	rebund.direction = getnormalized(vecsub(p->l->xyz, p->data->smpo));
	i = 0;
	min_t = vecnorm(vecsub(p->l->xyz, p->data->smpo));
	while (p->sp[i].exist)
	{
		dist = contactsp(p->sp[i], rebund, p);
		if (dist && dist * dist < min_t)
			return (0.1);
		i++;
	}
	i = 0;
	while (p->pl[i].exist)
	{
		dist = contactpl(p->pl[i], rebund, p);
		if (dist && dist * dist < min_t)
			return (0.1);
		i++;
	}
	i = 0;
	while (p->cy[i].exist)
	{
		dist = contactcy(p->cy[i], rebund, p);
		if (dist && dist * dist < min_t)
			return (0.1);
		dist = contactcap(p->cy[i], rebund, p);
		if (dist && dist * dist < min_t)
			return (0.1);
		dist = contactcap2(p->cy[i], rebund, p);
		if (dist && dist * dist < min_t)
			return (0.1);
		i++;
	}
	return (1);
}

double	returnluxa(t_vec lux, unsigned char *color, t_var *p, double light)
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
	double	light;
	t_vec	lux;

	lux = newvec(color[0], color[1], color[2]);
	p->data->depthmax--;
	if (min_t != 999999999999)
	{
		light = intershadow(myray, p);
		lux = vecmult(lux, light);
		lux = vecmult(lux, p->l->ratio * 50000 * goodlux(vecdot(\
		getnormalized(vecsub(p->l->xyz, p->data->smpo)), p->data->smno) \
		/ vecnorm(vecsub(p->l->xyz, p->data->smpo))));
		return (returnluxa(lux, color, p, light));
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
	min_t = 999999999999;
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
	i = 0;
	while (p->cy[i].exist)
	{
		dist = contactcy(p->cy[i], myray, p);
		if (dist && dist < min_t)
		{
			min_t = dist;
			assignrgb(rgb, p->cy[i].rgb);
			p->data->smno = p->data->no;
			p->data->smpo = p->data->po;
		}
		dist = contactcap(p->cy[i], myray, p);
		if (dist && dist < min_t)
		{
			min_t = dist;
			assignrgb(rgb, p->cy[i].rgb);
			p->data->smno = p->data->no;
			p->data->smpo = p->data->po;
		}
		dist = contactcap2(p->cy[i], myray, p);
		if (dist && dist < min_t)
		{
			min_t = dist;
			assignrgb(rgb, p->cy[i].rgb);
			p->data->smno = p->data->no;
			p->data->smpo = p->data->po;
		}
		i++;
	}
	return (raycolor(myray, min_t, p, rgb));
}

t_vec	getup(double z)
{
	if (z >= 0 && z <= 0.25)
		return (newvec(z/0.25, 1, 0));
	else if (z >= 0.25 && z <= 0.5)
		return (newvec(1, 1 - (z - 0.25)/0.25, 0));
	else if (z >= 0.5 && z <= 0.75)
		return (newvec(1, -1 + (z - 0.75)/0.25, 0));
	else if (z >= 0.75 && z <= 1)
		return (newvec(1 - z, -1, 0));
	else if (z <= 0 && z >= -0.25)
		return (newvec(z/0.25, 1, 0));
	else if (z <= -0.25 && z >= -0.5)
		return (newvec(-1, 1 - (z + 0.25)/-0.25, 0));
	else if (z <= -0.5 && z >= -0.75)
		return (newvec(-1, -1 - (z + 0.75)/-0.25, 0));
	else //z <= -0.75 && z >= -1)
		return (newvec(-1 - z, -1, 0));
}

void	algo(t_var *p, int x, int y)
{
	t_ray	myray;
	int		i;
	double	color;

	myray.origin = p->c->xyz;
	myray.direction = newvec(x - p->data->winwidth / 2, y - p->data->winlength
			/ 2, (-p->data->winwidth / (2 * tan((p->c->fov * M_PI / 180) / 2))));
	normalize(myray.direction);
	double	z = p->c->way.z;
	p->c->way.z = 1;
	t_vec up = getup(z);
	t_vec cam_r = veccross(p->c->way, up);
	t_vec step1 = vecmult(cam_r, myray.direction.x);
	t_vec step2 = vecmult(up, myray.direction.y);
	t_vec step3 = vecmult(p->c->way, myray.direction.z);
	p->c->way.z = z;
	myray.direction = vecadd3(step1, step2, step3);
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

	p->x = 0;
	while (p->x < p->data->winlength)
	{
		p->y = 0;
		while (p->y < p->data->winwidth)
		{
			algo(p, p->x, p->y);
			p->y++;
		}
		p->x++;
	}
	mlx_put_image_to_window(p->data->mlx, p->data->win, p->data->img, 0, 0);
}
