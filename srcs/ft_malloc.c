/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:05:39 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/20 11:27:17 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int	ft_malloc_a(t_var *p, char **lines)
{
	int	i;
	int	len;
	t_a	*fig;

	i = -1;
	len = 0;
	while (lines[++i])
		if (lines[i][0] == 'A')
			len++;
	fig = malloc((len + 1) * sizeof(t_a));
	if (!fig)
		return (0);
	len = 0;
	i = -1;
	while (lines[++i])
		if (lines[i][0] == 'A')
			if (!ft_create_a(lines[i], &fig[len++]))
				return (0);
	fig[len].exist = 0;
	fig[len].rgb[0] = 0;
	fig[len].rgb[1] = 0;
	fig[len].rgb[2] = 0;
	p->a = fig;
	return (1);
}

int	ft_malloc_c(t_var *p, char **lines)
{
	int	i;
	int	len;
	t_c	*fig;

	i = -1;
	len = 0;
	while (lines[++i])
		if (lines[i][0] == 'C')
			len++;
	fig = malloc((len + 1) * sizeof(t_c));
	if (!fig)
		return (0);
	len = 0;
	i = -1;
	while (lines[++i])
		if (lines[i][0] == 'C')
			if (!ft_create_c(lines[i], &fig[len++]))
				return (0);
	fig[len].exist = 0;
	p->c = fig;
	return (1);
}

int	ft_malloc_l(t_var *p, char **lines)
{
	int	i;
	int	len;
	t_l	*fig;

	i = -1;
	len = 0;
	while (lines[++i])
		if (lines[i][0] == 'L')
			len++;
	fig = malloc((len + 1) * sizeof(t_l));
	if (!fig)
		return (0);
	len = 0;
	i = -1;
	while (lines[++i])
		if (lines[i][0] == 'L')
			if (!ft_create_l(lines[i], &fig[len++]))
				return (0);
	fig[len].exist = 0;
	fig[len].rgb[0] = 0;
	fig[len].rgb[1] = 0;
	fig[len].rgb[2] = 0;
	p->l = fig;
	return (1);
}

int	ft_malloc_cy(t_var *p, char **lines)
{
	int		i;
	int		len;
	t_cy	*fig;

	i = -1;
	len = 0;
	while (lines[++i])
		if (lines[i][0] == 'c' && lines[i][1] == 'y')
			len++;
	fig = malloc((len + 1) * sizeof(t_cy));
	if (!fig)
		return (0);
	len = 0;
	i = -1;
	while (lines[++i])
		if (lines[i][0] == 'c' && lines[i][1] == 'y')
			if (!ft_create_cy(lines[i], &fig[len++]))
				return (0);
	fig[len].exist = 0;
	p->cy = fig;
	return (1);
}

int	ft_malloc_all(char **lines, t_var *p)
{
	if (!ft_malloc_a(p, lines))
		return (0);
	if (!ft_malloc_c(p, lines))
		return (0);
	if (!ft_malloc_l(p, lines))
		return (0);
	if (!ft_malloc_sp(p, lines))
		return (0);
	if (!ft_malloc_pl(p, lines))
		return (0);
	if (!ft_malloc_cy(p, lines))
		return (0);
	return (1);
}
