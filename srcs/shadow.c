/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:57:00 by mlagrang          #+#    #+#             */
/*   Updated: 2022/11/14 15:14:26 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

double	intershadow_cyl(t_var *p, t_ray rebund, double dist, double min_t)
{
	int	i;

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

double	intershadow_while(t_var *p, t_ray rebund, double dist, double min_t)
{
	int	i;

	i = 0;
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
	return (intershadow_cyl(p, rebund, dist, min_t));
}

double	intershadow(t_var *p)
{
	t_ray	rebund;
	int		i;
	double	dist;
	double	min_t;

	dist = 0;
	rebund.origin = vecadd(p->data->smpo, vecmult(p->data->smno, 0.01));
	rebund.direction = getnormalized(vecsub(p->l->xyz, p->data->smpo));
	i = 0;
	min_t = vecnorm(vecsub(p->l->xyz, p->data->smpo));
	return (intershadow_while(p, rebund, dist, min_t));
}
