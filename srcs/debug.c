#include "../incl/miniRT.h"

void	print_a(t_a *fig)
{
	int	i;

	i = -1;
	while (fig[++i].exist)
	{
		dprintf(2, "a[%d]->ratio = %f\n", i, fig[i].ratio);
		dprintf(2, "a[%d]->rgb = %d,%d,%d\n", i, fig[i].rgb[0], fig[i].rgb[1], fig[i].rgb[2]);
		dprintf(2, "\n");
	}
}

void	print_c(t_c *fig)
{
	int	i;

	i = -1;
	while (fig[++i].exist)
	{
		dprintf(2, "c[%d]->xyz = %f,%f,%f\n", i, fig[i].xyz.x, fig[i].xyz.y, fig[i].xyz.z);
		dprintf(2, "c[%d]->way = %f,%f,%f\n", i, fig[i].way.x, fig[i].way.y, fig[i].way.z);
		dprintf(2, "c[%d]->fov = %d\n", i, fig[i].fov);
		dprintf(2, "\n");
	}
}

void	print_l(t_l *fig)
{
	int	i;

	i = -1;
	while (fig[++i].exist)
	{
		dprintf(2, "l[%d]->xyz = %f,%f,%f\n", i, fig[i].xyz.x, fig[i].xyz.y, fig[i].xyz.z);
		dprintf(2, "l[%d]->ratio = %f\n", i, fig[i].ratio);
		dprintf(2, "l[%d]->rgb = %d,%d,%d\n", i, fig[i].rgb[0], fig[i].rgb[1], fig[i].rgb[2]);

		dprintf(2, "\n");
	}
}

void	print_sp(t_sp *fig)
{
	int	i;

	i = -1;
	while (fig[++i].exist)
	{
		dprintf(2, "sp[%d]->xyz = %f,%f,%f\n", i, fig[i].xyz.x, fig[i].xyz.y, fig[i].xyz.z);
		dprintf(2, "sp[%d]->height = %f\n", i, fig[i].height);
		dprintf(2, "sp[%d]->rgb = %d,%d,%d\n", i, fig[i].rgb[0], fig[i].rgb[1], fig[i].rgb[2]);
		dprintf(2, "\n");
	}
}

void	print_pl(t_pl *fig)
{
	int	i;

	i = -1;
	while (fig[++i].exist)
	{
		dprintf(2, "pl[%d]->xyz = %f,%f,%f\n", i, fig[i].xyz.x, fig[i].xyz.y, fig[i].xyz.z);
		dprintf(2, "pl[%d]->way = %f,%f,%f\n", i, fig[i].xyz.x, fig[i].xyz.y, fig[i].xyz.z);
		dprintf(2, "pl[%d]->rgb = %d,%d,%d\n", i, fig[i].rgb[0], fig[i].rgb[1], fig[i].rgb[2]);
		dprintf(2, "\n");
	}
}

void	print_cy(t_cy *fig)
{
	int	i;

	i = -1;
	while (fig[++i].exist)
	{
		dprintf(2, "cy[%d]->xyz = %f,%f,%f\n", i, fig[i].xyz.x, fig[i].xyz.y, fig[i].xyz.z);
		dprintf(2, "cy[%d]->way = %f,%f,%f\n", i, fig[i].xyz.x, fig[i].xyz.y, fig[i].xyz.z);
		dprintf(2, "cy[%d]->width = %f\n", i, fig[i].width);
		dprintf(2, "cy[%d]->height = %f\n", i, fig[i].height);
		dprintf(2, "cy[%d]->rgb = %d,%d,%d\n", i, fig[i].rgb[0], fig[i].rgb[1], fig[i].rgb[2]);
		dprintf(2, "\n");
	}
}


void	print_everything(t_var *p)
{
	print_a(p->a);
	print_c(p->c);
	print_l(p->l);
	print_sp(p->sp);
	print_pl(p->pl);
	print_cy(p->cy);
}

void	print_vec(t_vec t)
{
	dprintf(1, "%f	%f	%f\n", t.x, t.y, t.z);
}