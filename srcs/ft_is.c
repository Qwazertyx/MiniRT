/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:10:13 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/14 16:50:09 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int	ft_is_alpha(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!((s[i] >= 'a' && s[i] <= 'z') || \
		(s[i] >= 'A' && s[i] <= 'Z')))
			return (0);
	if (i > 2)
		return (0);
	return (1);
}

int	ft_is_int(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
	return (1);
}

int	ft_is_triint(char *s)
{
	int				i;
	int				ret;
	unsigned char	t[3];

	i = 0;
	ret = 0;
	while (s[i])
	{
		while (s[i] && s[i] >= '0' && s[i] <= '9')
			i++;
		if (s[i] && s[i] == ',')
			ret++;
		if (ret > 2)
			return (0);
		if (s[i])
			i++;
	}
	if (!get_triple_un(s, t))
		return (0);
	if (t[0] > 255 || t[0] < 0 || t[1] > 255 || \
	t[1] < 0 || t[2] > 255 || t[2] < 0)
		return (0);
	return (1);
}

int	ft_is_do(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] && s[i] == '.')
		i++;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i])
		return (0);
	return (1);
}

int	ft_is_trido(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_nb_w(s, ',') != 3)
		return (0);
	while (++j <= 3)
	{
		if (s[i] == '-')
			i++;
		while (s[i] && s[i] >= '0' && s[i] <= '9')
			i++;
		if (s[i] && s[i] == '.')
			i++;
		while (s[i] && s[i] >= '0' && s[i] <= '9')
			i++;
		if ((s[i] && s[i] != ',') || (s[i] && s[i] == ',' && j == 3))
			return (0);
		i++;
	}
	return (1);
}
