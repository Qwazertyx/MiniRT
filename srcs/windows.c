/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:57:30 by mlagrang          #+#    #+#             */
/*   Updated: 2022/12/20 11:11:41 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

void	vardef(t_data *data)
{
	double	aspect_ratio;

	aspect_ratio = 16.0 / 9.0;
	data->winwidth = 700;
	data->winlength = data->winwidth;
	data->sampleppix = 1;
	data->depthmax = 50;
	data->colorit = 0;
}

int	key_hook3(int keycode, t_var *p, t_pal *tab)
{
	if (keycode == 40 && p->l->ratio != 0 && p->l->exist)
		p->l->ratio = 0;
	else if (keycode == 40 && p->l->ratio == 0 && p->l->exist)
		p->l->ratio = p->l->init_ratio;
	srand (10);
	if (keycode == 15)
	{
		p->l->rgb[0] = tab[p->data->colorit].rgb[0];
		p->l->rgb[1] = tab[p->data->colorit].rgb[1];
		p->l->rgb[2] = tab[p->data->colorit].rgb[2];
		p->data->colorit++;
		if (p->data->colorit > 15)
			p->data->colorit = 0;
	}
	return (0);
}

int	key_hook2(int keycode, t_var *p)
{
	t_pal	tab[16];

	tab[0] = (t_pal){255, 255, 255};
	tab[1] = (t_pal){192, 192, 192};
	tab[2] = (t_pal){128, 128, 128};
	tab[3] = (t_pal){0, 0, 0};
	tab[4] = (t_pal){255, 0, 0};
	tab[5] = (t_pal){128, 0, 0};
	tab[6] = (t_pal){255, 255, 0};
	tab[7] = (t_pal){128, 128, 0};
	tab[8] = (t_pal){0, 255, 0};
	tab[9] = (t_pal){0, 128, 0};
	tab[10] = (t_pal){0, 255, 255};
	tab[11] = (t_pal){0, 128, 128};
	tab[12] = (t_pal){0, 0, 255};
	tab[13] = (t_pal){0, 0, 128};
	tab[14] = (t_pal){255, 0, 255};
	tab[15] = (t_pal){128, 0, 128};
	key_hook3(keycode, p, tab);
	return (0);
}

int	key_hook(int keycode, t_var *p)
{
	if (keycode == 53)
		closewin(p->data);
	if (keycode == 37 && p->a->ratio != 0 && p->a->exist)
		p->a->ratio = 0;
	else if (keycode == 37 && p->a->ratio == 0 && p->a->exist)
		p->a->ratio = p->a->init_ratio;
	key_hook2(keycode, p);
	generator(p);
	return (0);
}

int	windowsop(t_var *p)
{
	t_data	data;

	p->data = &data;
	data.mlx = mlx_init();
	vardef(&data);
	data.win = mlx_new_window(data.mlx, data.winwidth, data.winlength, "UwU");
	data.img = mlx_new_image(data.mlx, data.winwidth, data.winlength);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	generator(p);
	mlx_hook(data.win, 17, 1L << 2, closewin, &data);
	mlx_key_hook(data.win, key_hook, p);
	mlx_loop(data.mlx);
	return (0);
}
