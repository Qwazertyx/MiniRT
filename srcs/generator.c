/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:54:00 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/14 17:46:37 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

//Lumière ambiante :Camera :Lumière :Sphere:Plan : Cylindre :
void	mypixelput(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (int)(y * data->line_length + x
			* (data->bits_per_pixel * 0.125));
	if (y < data->winwidth && x < data->winlength)
		*(unsigned int *)dst = color;
}

double	raycolor(double min_t, t_var *p, unsigned char *color)
{
	double	light;
	t_vec	lux;

	lux = newvec(color[0], color[1], color[2]);
	p->data->depthmax--;
	if (min_t != 999999999999)
	{
		light = intershadow(p);
		lux = vecmult(lux, light);
		lux = vecmult(lux, p->l->ratio * 50000 * goodlux(vecdot(\
		getnormalized(vecsub(p->l->xyz, p->data->smpo)), p->data->smno) \
		/ vecnorm(vecsub(p->l->xyz, p->data->smpo))));
		return (endlux(lux, p, light, color));
	}
	return (colorrgb(0, 0, 0));
}

t_vec	getup(t_vec way)
{
	return (getnormalized(veccross(veccross(way, newvec(0, 1, 0)), way)));
}

void	algo(t_var *p, int x, int y)
{
	t_ray	myray;
	int		i;
	double	color;

	myray.origin = p->c->xyz;
	myray.direction = newvec(x - p->data->winwidth / 2, y - p->data->winlength \
	/ 2, (-p->data->winwidth / (2 * tan((p->c->fov * M_PI / 180) / 2))));
	normalize(myray.direction);
	myray.direction = vecadd3(vecmult(veccross(p->c->way, getup(p->c->way)), \
	myray.direction.x), vecmult(getup(p->c->way), myray.direction.y), \
	vecmult(p->c->way, myray.direction.z));
	i = 0;
	color = 0;
	while (i < p->data->sampleppix)
	{
		p->data->depthmax = 50;
		color += inter(myray, p);
		i++;
	}
	mypixelput(p->data, p->data->winwidth - x, y, color / p->data->sampleppix);
}

//i = H = x = len
//j = W = y = wid

void	generator(t_var *p)
{
	int	x;
	int	y;

	p->c->way = met_a_un(p->c->way);
	x = 0;
	while (x < p->data->winlength)
	{
		y = 0;
		while (y < p->data->winwidth)
		{
			p->x = x;
			p->y = y;
			algo(p, x, y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(p->data->mlx, p->data->win, p->data->img, 0, 0);
}
