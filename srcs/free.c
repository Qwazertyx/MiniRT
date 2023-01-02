/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:53:29 by mlagrang          #+#    #+#             */
/*   Updated: 2022/11/16 17:46:32 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int	closewin(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	exit(EXIT_SUCCESS);
	return (0);
}

void	free_struc(t_var *p)
{
	free(p->a);
	free(p->c);
	free(p->l);
	free(p->sp);
	free(p->pl);
	free(p->cy);
}

int	free_split(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		free(a[i++]);
	free(a);
	return (0);
}
