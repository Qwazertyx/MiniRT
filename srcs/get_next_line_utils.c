/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:56:33 by mlagrang          #+#    #+#             */
/*   Updated: 2022/11/04 12:56:34 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int	ft_strlen(char *a)
{
	int	i;

	i = 0;
	while (a && a[i])
		i++;
	return (i);
}

int	ft_strlenn(char *a)
{
	int	i;

	i = 0;
	while (a && a[i] && a[i] != '\n')
		i++;
	if (a && a[i] && a[i] == '\n')
		i++;
	return (i);
}

char	*ft_join(char *a, char *b)
{
	int		i;
	int		j;
	char	*s;

	i = ft_strlen(a);
	j = ft_strlenn(b);
	s = malloc(i + j + 1);
	if (s)
	{
		i = -1;
		j = -1;
		while (a && a[++i])
			s[i] = a[i];
		if (i == -1)
			i = 0;
		while (b && b[++j] && b[j] != '\n')
			s[i + j] = b[j];
		s[i + j] = b[j];
		if ((b && b[j] && b[j] == '\n') || j == -1)
			j++;
		s[i + j] = '\0';
	}
	free(a);
	return (s);
}

int	ft_search(char *a, char c)
{
	int	i;

	i = 0;
	while (a[i] && a[i] != c)
		i++;
	if (a[i] == c)
		return (i);
	return (-1);
}

void	ft_cut(char *a)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (a[i] && a[i] != '\n')
		i++;
	if (a[i] == '\n')
		i++;
	while (j < 10 - i)
	{
		a[j] = a[j + i];
		j++;
	}
	a[j] = '\0';
}
