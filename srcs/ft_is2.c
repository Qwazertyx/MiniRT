/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:06:12 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/14 16:23:05 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

static int	ft_is_number(char c)
{
	if ((c >= '0' && c <= '9') || c == '-')
		return (1);
	return (0);
}

int	ft_is_num(char **split)
{
	int	i;
	int	j;

	i = 0;
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
		{
			if (!ft_is_number(split[i][j]) && split[i][j] != '.' && \
			split[i][j] != ',')
				return (0);
		}
	}
	return (1);
}
