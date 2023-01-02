/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:14:20 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/20 11:43:13 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int	get_triple_do(char *s, t_vec *t)
{
	char	**split;

	split = ft_split(s, ',');
	if (!split)
		return (0);
	if (!split[0] || !split[1] || !split[2] || split[3])
		return (free_split(split));
	t->x = ft_atof(split[0]);
	t->y = ft_atof(split[1]);
	t->z = ft_atof(split[2]);
	free_split(split);
	return (1);
}

int	get_triple_un(char *s, unsigned char t[3])
{
	char	**split;

	split = ft_split(s, ',');
	if (!split)
		return (0);
	if (!split[0] || !split[1] || !split[2] || split[3])
		return (free_split(split));
	if (ft_atoi(split[0]) < 0 || ft_atoi(split[0]) > 255 \
	|| ft_atoi(split[1]) < 0 || ft_atoi(split[1]) > 255 \
	|| ft_atoi(split[2]) < 0 || ft_atoi(split[2]) > 255)
		return (0);
	t[0] = (unsigned char)ft_atoi(split[0]);
	t[1] = (unsigned char)ft_atoi(split[1]);
	t[2] = (unsigned char)ft_atoi(split[2]);
	free_split(split);
	return (1);
}

int	parse_struc(t_var *p, char *file)
{
	char	**all_line;
	char	*temp;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	all_line = NULL;
	temp = get_next_line(fd);
	while (temp > 0)
	{
		if (temp[0] != '\n')
			all_line = ft_add_line(all_line, temp);
		else
			free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
	fd = ft_malloc_all(all_line, p);
	free_split(all_line);
	if (!fd)
		return (0);
	return (1);
}
