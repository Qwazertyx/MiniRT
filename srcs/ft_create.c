/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:09:25 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/13 15:10:30 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int	ft_create_a(char *line, t_a *fig)
{
	char	**split;

	fig->exist = 1;
	split = ft_split2(line, ' ', '	');
	if (!split)
		return (0);
	fig->ratio = ft_atof(split[1]);
	fig->init_ratio = fig->ratio;
	if (!get_triple_un(split[2], fig->rgb))
		return (free_split(split));
	free_split(split);
	return (1);
}

int	ft_create_c(char *line, t_c *fig)
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
	fig->fov = ft_atoi(split[3]);
	free_split(split);
	return (1);
}

int	ft_create_l(char *line, t_l *fig)
{
	char	**split;

	fig->exist = 1;
	split = ft_split2(line, ' ', '	');
	if (!split)
		return (0);
	if (!get_triple_do(split[1], &fig->xyz))
		return (free_split(split));
	fig->ratio = ft_atof(split[2]);
	fig->init_ratio = fig->ratio;
	if (!get_triple_un(split[3], fig->rgb))
		return (free_split(split));
	free_split(split);
	return (1);
}

int	ft_create_cy(char *line, t_cy *fig)
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
	fig->width = ft_atof(split[3]);
	fig->height = ft_atof(split[4]);
	if (!get_triple_un(split[5], fig->rgb))
		return (free_split(split));
	free_split(split);
	return (1);
}
