/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:57:11 by mlagrang          #+#    #+#             */
/*   Updated: 2022/11/14 13:28:31 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_malloc_sp(t_var *p, char **lines)
{
	int		i;
	int		len;
	t_sp	*fig;

	i = -1;
	len = 0;
	while (lines[++i])
		if (lines[i][0] == 's' && lines[i][1] == 'p')
			len++;
	fig = malloc((len + 1) * sizeof(t_sp));
	if (!fig)
		return (0);
	len = 0;
	i = -1;
	while (lines[++i])
		if (lines[i][0] == 's' && lines[i][1] == 'p')
			if (!ft_create_sp(lines[i], &fig[len++]))
				return (0);
	fig[len].exist = 0;
	p->sp = fig;
	return (1);
}

int	ft_create_sp(char *line, t_sp *fig)
{
	char	**split;

	fig->exist = 1;
	split = ft_split2(line, ' ', '	');
	if (!split)
		return (0);
	if (!get_triple_do(split[1], &fig->xyz))
		return (free_split(split));
	fig->height = ft_atof(split[2]);
	if (!get_triple_un(split[3], fig->rgb))
		return (free_split(split));
	free_split(split);
	return (1);
}

double	inter_sp(t_var *p, t_ray myray, double min_t, unsigned char rgb[3])
{
	int		i;
	double	dist;

	i = 0;
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
	return (min_t);
}
