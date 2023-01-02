/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:11:21 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/20 11:37:02 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int	ft_verif(char **lines)
{
	int		i;
	char	**split;
	int		m[3];

	i = 0;
	ft_null(m);
	while (lines[i])
	{
		split = ft_split2(lines[i], ' ', '	');
		if (!split)
			return (0);
		if (!ft_is_alpha(split[0]) || !ft_is_num(split))
			return (ft_error(split));
		if (split[0][0] == 'A' || split[0][0] == 'C' || split[0][0] == 'L')
			ft_increase(m, split[0][0]);
		if (m[0] > 1 || m[1] > 1 || m[2] > 1)
			return (ft_error(split));
		if (!check_digits(split))
			return (ft_error(split));
		free_split(split);
		i++;
	}
	if (m[1] != 1)
		return (ft_puterror("Error\nNo cam found\n"));
	return (1);
}

int	verif_input(char *file)
{
	char	**all_line;
	char	*temp;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_puterror("Error\nNo such file\n"));
	all_line = NULL;
	temp = get_next_line(fd);
	if (!temp)
		return (ft_puterror("Error\nAn error occured during read"));
	while (temp > 0)
	{
		if (is_empty(temp))
			all_line = ft_add_line(all_line, no_double_space(temp));
		else
			free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
	fd = ft_verif(all_line);
	free_split(all_line);
	if (!fd)
		return (0);
	return (1);
}

int	check_digits(char **lines)
{
	if (lines[0][0] == 'A')
		return (check_a(lines));
	else if (lines[0][0] == 'C')
		return (check_c(lines));
	else if (lines[0][0] == 'L')
		return (check_l(lines));
	else if (lines[0][0] == 's' && lines[0][1] == 'p')
		return (check_sp(lines));
	else if (lines[0][0] == 'p' && lines[0][1] == 'l')
		return (check_pl(lines));
	else if (lines[0][0] == 'c' && lines[0][1] == 'y')
		return (check_cy(lines));
	return (0);
}

int	check_a(char **lines)
{
	if (!lines[0] || !lines[1] || !lines[2])
		return (0);
	if (!ft_is_do(lines[1]) || \
	ft_atof(lines[1]) < 0.0 || ft_atof(lines[1]) > 1.0)
		return (0);
	if (!ft_is_triint(lines[2]))
		return (0);
	if (lines[3])
		return (0);
	return (1);
}

int	check_c(char **lines)
{
	t_vec	t;

	if (!lines[0] || !lines[1] || !lines[2] || !lines[3])
		return (0);
	if (!ft_is_trido(lines[1]))
		return (0);
	if (!ft_is_trido(lines[2]))
		return (0);
	get_triple_do(lines[2], &t);
	if (t.x < -1.0 || t.x > 1.0 || t.y < -1.0 || \
	t.y > 1.0 || t.z < -1.0 || t.z > 1.0)
		return (0);
	if (!ft_is_int(lines[3]) || \
	ft_atoi(lines[3]) < 0 || ft_atoi(lines[3]) > 180)
		return (0);
	if (lines[4])
		return (0);
	return (1);
}
