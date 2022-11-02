#include "../incl/miniRT.h"

void	vardef(t_data *data)
{
	double	aspect_ratio;

	aspect_ratio = 16.0 / 9.0;
	data->winwidth = 1000;
	data->winlength = 1000;//data->winwidth / aspect_ratio;
	data->sampleppix = 1;
	data->depthmax = 50;
}

int	closewin(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int keycode, t_var *p)
{
	if (keycode == 53)
		closewin(p->data);
	if (keycode == 13)
		p->c->xyz.y += 5;
	if (keycode == 0)
		p->c->xyz.x -= 5;
	if (keycode == 1)
		p->c->xyz.y -= 5;
	if (keycode == 2)
		p->c->xyz.x += 5;

	if (keycode == 126)
		p->c->way.y += 0.05;
	if (keycode == 123)
		p->c->way.x -= 0.05;
	if (keycode == 125)
		p->c->way.y -= 0.05;
	if (keycode == 124)
		p->c->way.x += 0.05;
	
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
