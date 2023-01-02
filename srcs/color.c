/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:54:24 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/20 11:21:08 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

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

int	endlux(t_vec lux, t_var *p, double light, unsigned char *color)
{
	int	r;
	int	g;
	int	b;

	if (light == 0.1)
	{
		r = color[0] * (p->a->rgb[0] / 255.0) * p->a->ratio;
		g = color[1] * (p->a->rgb[1] / 255.0) * p->a->ratio;
		b = color[2] * (p->a->rgb[2] / 255.0) * p->a->ratio;
	}
	else
	{
		r = color[0] * (p->a->rgb[0] / 255.0) * p->a->ratio
			+ lux.x * (p->l->rgb[0] / 255.0) * p->l->ratio;
		g = color[1] * (p->a->rgb[1] / 255.0) * p->a->ratio
			+ lux.y * (p->l->rgb[1] / 255.0) * p->l->ratio;
		b = color[2] * (p->a->rgb[2] / 255.0) * p->a->ratio
			+ lux.z * (p->l->rgb[2] / 255.0) * p->l->ratio;
	}
	return (colorrgb(goodlux(r), goodlux(g), goodlux(b)));
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
