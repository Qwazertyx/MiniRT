#include "../incl/miniRT.h"

void	free_struc(t_var *p)
{
	free(p->a);
	free(p->c);
	free(p->l);
	free(p->sp);
	free(p->pl);
	free(p->cy);
}