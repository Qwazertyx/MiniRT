/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ato.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:03:36 by mlagrang          #+#    #+#             */
/*   Updated: 2022/11/14 14:33:20 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int	ft_atoi(char *s)
{
	int		i;
	int		p;
	long	c;

	i = 0;
	p = 1;
	c = 0;
	if (s[i] == '-')
		p = p * -1 + 0 * i++;
	while (s[i] >= '0' && s[i] <= '9')
		c = c * 10 + (s[i++] - '0');
	return (c * p);
}

double	ft_atod(char *s)
{
	int		i;
	int		p;
	double	l;
	double	c;

	i = 0;
	p = 1;
	l = 10.0;
	c = 0;
	if (s[i] == '-')
		p = p * -1 + 0 * i++;
	while (s[i] && s[i] != '.')
		i++;
	if (!s[i])
		return (0);
	i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		c = c + ((s[i++] - '0') / l);
		l = l * 10.0;
	}
	return (c * p);
}

double	ft_atof(char *s)
{
	return (ft_atoi(s) + ft_atod(s));
}
