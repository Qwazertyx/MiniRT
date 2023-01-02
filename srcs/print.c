/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:38:37 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/14 16:33:48 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int	ft_puterror(char *str)
{
	ft_putstr_fd(str, 2);
	return (0);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

int	ft_error(char **split)
{
	int	i;

	write(2, "Error\nOn line:\n", 15);
	i = 0;
	while (split && split[i])
	{
		ft_putstr_fd(split[i++], 2);
		write(2, " ", 1);
	}
	write(2, "\n", 1);
	free_split(split);
	return (0);
}
