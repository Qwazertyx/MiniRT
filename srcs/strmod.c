/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:04:45 by mlagrang          #+#    #+#             */
/*   Updated: 2022/11/04 13:05:00 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

char	**ft_add_line(char **old, char *to_add)
{
	int		i;
	char	**new;

	i = 0;
	while (old && old[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (old && old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i] = to_add;
	new[i + 1] = 0;
	free(old);
	return (new);
}

char	*no_double_space(char *str)
{
	char	*s;
	int		i;

	s = NULL;
	i = 0;
	while (str && str[i] && str[i] == ' ')
		i++;
	while (str && str[i] && str[i] != '\n')
	{
		if (str[i] == ' ')
			s = ft_joinc(s, str[i]);
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i] && str[i] != ' ' && str[i] != '\n')
			s = ft_joinc(s, str[i++]);
		if (!s)
			return (ft_free(str));
	}
	free(str);
	return (s);
}
