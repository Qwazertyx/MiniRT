/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:53:36 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/14 16:47:52 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int	ft_nb_w(const char *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
			nb++;
		while (s[i] != c && s[i])
			i++;
	}
	return (nb);
}

static char	*ft_strncpy(char *dest, const char *str, int n)
{
	int	i;

	i = -1;
	while (str[++i] && i < n)
		dest[i] = str[i];
	dest[i] = '\0';
	return (dest);
}

static char	*mallocdef(char **tab, int j, int len)
{
	tab[j] = malloc(len);
	if (!tab[j])
	{
		while (-j > 0)
			free(tab[j]);
		free(tab);
		return (0);
	}
	return (tab[j]);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		l;
	char	**tab;

	tab = malloc(sizeof(char *) * (ft_nb_w(s, c) + 1));
	if (!tab)
		return (0);
	i = 0;
	j = 0;
	while (j < ft_nb_w(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		l = i;
		while (s[i] != c && s[i])
			i++;
		tab[j] = mallocdef(tab, j, i - l + 1);
		if (!tab[j])
			return (0);
		tab[j] = ft_strncpy(tab[j], &s[l], i - l);
		j++;
	}
	tab[j] = 0;
	return (tab);
}
