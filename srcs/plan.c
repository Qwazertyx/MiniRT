/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:56:57 by mlagrang          #+#    #+#             */
/*   Updated: 2022/11/14 13:28:18 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_malloc_pl(t_var *p, char **lines)
{
	int		i;
	int		len;
	t_pl	*fig;

	i = -1;
	len = 0;
	while (lines[++i])
		if (lines[i][0] == 'p' && lines[i][1] == 'l')
			len++;
	fig = malloc((len + 1) * sizeof(t_pl));
	if (!fig)
		return (0);
	len = 0;
	i = -1;
	while (lines[++i])
		if (lines[i][0] == 'p' && lines[i][1] == 'l')
			if (!ft_create_pl(lines[i], &fig[len++]))
				return (0);
	fig[len].exist = 0;
	p->pl = fig;
	return (1);
}

int	ft_create_pl(char *line, t_pl *fig)
{
	char	**split;

	fig->exist = 1;
	split = ft_split2(line, ' ', '	');
	if (!split)
		return (0);
	if (!get_triple_do(split[1], &fig->xyz))
		return (free_split(split));
	if (!get_triple_do(split[2], &fig->way))
		return (free_split(split));
	if (!get_triple_un(split[3], fig->rgb))
		return (free_split(split));
	free_split(split);
	return (1);
}

double	inter_pl(t_var *p, t_ray myray, double min_t, unsigned char rgb[3])
{
	int		i;
	double	dist;

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
	return (min_t);
}
