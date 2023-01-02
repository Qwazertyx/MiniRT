/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:13:31 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/20 11:38:37 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int	check_l(char **lines)
{
	if (!lines[0] || !lines[1] || !lines[2] || !lines[3])
		return (0);
	if (!ft_is_trido(lines[1]))
		return (0);
	if (!ft_is_do(lines[2]) || \
	ft_atof(lines[2]) < 0.0 || ft_atof(lines[2]) > 1.0)
		return (0);
	if (!ft_is_triint(lines[3]))
		return (0);
	if (lines[4])
		return (0);
	return (1);
}

int	check_sp(char **lines)
{
	if (!lines[0] || !lines[1] || !lines[2] || !lines[3])
		return (0);
	if (!ft_is_trido(lines[1]))
		return (0);
	if (!ft_is_do(lines[2]) || ft_atof(lines[2]) <= 0)
		return (0);
	if (!ft_is_triint(lines[3]))
		return (0);
	if (lines[4])
		return (0);
	return (1);
}

int	check_pl(char **lines)
{
	t_vec	t;

	if (!lines[0] || !lines[1] || !lines[2] || !lines[3])
		return (0);
	if (!ft_is_trido(lines[1]))
		return (0);
	if (!ft_is_trido(lines[2]))
		return (0);
	get_triple_do(lines[2], &t);
	if (t.x < -1.0 || t.x > 1.0 || t.y < -1.0 || t.y > 1.0 \
	|| t.z < -1.0 || t.z > 1.0)
		return (0);
	if (!ft_is_triint(lines[3]))
		return (0);
	if (lines[4])
		return (0);
	return (1);
}

int	check_cy(char **lines)
{
	t_vec	t;

	if (!lines[0] || !lines[1] || !lines[2] || !lines[3] || !lines[4] || \
		!lines[5])
		return (0);
	if (!ft_is_trido(lines[1]))
		return (0);
	if (!ft_is_trido(lines[2]))
		return (0);
	get_triple_do(lines[2], &t);
	if (t.x < -1.0 || t.x > 1.0 || t.y < -1.0 || t.y > 1.0 \
	|| t.z < -1.0 || t.z > 1.0)
		return (0);
	if (!ft_is_do(lines[3]) || ft_atof(lines[3]) <= 0)
		return (0);
	if (!ft_is_do(lines[4]) || ft_atof(lines[4]) <= 0)
		return (0);
	if (!ft_is_triint(lines[5]))
		return (0);
	if (lines[6])
		return (0);
	return (1);
}
