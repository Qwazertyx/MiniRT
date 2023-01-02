/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:56:39 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/07 14:22:06 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

double	assign_cy(t_var *p, double dm[2], unsigned char rgb[3],
		unsigned char srcrgb[3])
{
	if (dm[0] && dm[0] < dm[1])
	{
		assignrgb(rgb, srcrgb);
		p->data->smno = p->data->no;
		p->data->smpo = p->data->po;
		return (dm[0]);
	}
	return (dm[1]);
}

double	inter_cy(t_var *p, t_ray myray, double min_t, unsigned char rgb[3])
{
	int		i;
	double	dm[2];

	dm[1] = min_t;
	i = 0;
	while (p->cy[i].exist)
	{
		dm[0] = contactcy(p->cy[i], myray, p);
		if (dm[0] && dm[0] < dm[1])
			dm[1] = assign_cy(p, dm, rgb, p->cy[i].rgb);
		dm[0] = contactcap(p->cy[i], myray, p);
		if (dm[0] && dm[0] < dm[1])
			dm[1] = assign_cy(p, dm, rgb, p->cy[i].rgb);
		dm[0] = contactcap2(p->cy[i], myray, p);
		if (dm[0] && dm[0] < dm[1])
			dm[1] = assign_cy(p, dm, rgb, p->cy[i].rgb);
		i++;
	}
	return (dm[1]);
}

double	inter(t_ray myray, t_var *p)
{
	unsigned char	rgb[3];
	double			min_t;

	min_t = 999999999999;
	min_t = inter_sp(p, myray, min_t, rgb);
	min_t = inter_pl(p, myray, min_t, rgb);
	min_t = inter_cy(p, myray, min_t, rgb);
	return (raycolor(min_t, p, rgb));
}
