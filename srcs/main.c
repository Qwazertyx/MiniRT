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
		{
			s = ft_joinc(s, str[i]);
			if (!s)
				return (ft_free(str));
		}
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i] && str[i] != ' ' && str[i] != '\n')
		{
			s = ft_joinc(s, str[i++]);
			if (!s)
				return (ft_free(str));
		}
	}
	free(str);
	return (s);
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

int	get_triple_do(char *s, t_vec *t)
{
	char	**split;

	split = ft_split(s, ',');
	if (!split)
		return (0);
	if (split[3])
		return (free_split(split));
	t->x = ft_atof(split[0]);
	t->y = ft_atof(split[1]);
	t->z = ft_atof(split[2]);
	free_split(split);
	return (1);
}

int	get_triple_un(char *s, unsigned char t[3])
{
	char	**split;

	split = ft_split(s, ',');
	if (!split)
		return (0);
	if (split[3])
		return (free_split(split));
	if (ft_atoi(split[0]) < 0 || ft_atoi(split[0]) > 255 \
	|| ft_atoi(split[1]) < 0 || ft_atoi(split[1]) > 255 \
	|| ft_atoi(split[2]) < 0 || ft_atoi(split[2]) > 255)
		return (0);
	t[0] = (unsigned char)ft_atoi(split[0]);
	t[1] = (unsigned char)ft_atoi(split[1]);
	t[2] = (unsigned char)ft_atoi(split[2]);
	free_split(split);
	return (1);
}

int	ft_create_a(char *line, t_a *fig)
{
	char	**split;

	fig->exist = 1;
	split = ft_split2(line, ' ', '	');
	if (!split)
		return (0);
	fig->ratio = ft_atof(split[1]);
	if (!get_triple_un(split[2], fig->rgb))
		return (free_split(split));
	free_split(split);
	return (1);
}

int	ft_create_c(char *line, t_c *fig)
{
	char	**split;

	fig->exist = 1;
	split = ft_split2(line, ' ', '	');
	if (!split)
		return (0);
	if (!get_triple_do(split[1], &fig->xyz))
		return (free_split(split));
	if (!get_triple_do(split[2], &fig->way))
		return (free_split(split));
	fig->fov = ft_atoi(split[3]);
	free_split(split);
	return (1);
}

int	ft_create_l(char *line, t_l *fig)
{
	char	**split;

	fig->exist = 1;
	split = ft_split2(line, ' ', '	');
	if (!split)
		return (0);
	if (!get_triple_do(split[1], &fig->xyz))
		return (free_split(split));
	fig->ratio = ft_atof(split[2]);
	if (!get_triple_un(split[3], fig->rgb))
		return (free_split(split));
	free_split(split);
	return (1);
}

int	ft_create_sp(char *line, t_sp *fig)
{
	char	**split;

	fig->exist = 1;
	split = ft_split2(line, ' ', '	');
	if (!split)
		return (0);
	if (!get_triple_do(split[1], &fig->xyz))
		return (free_split(split));
	fig->height = ft_atof(split[2]);
	if (!get_triple_un(split[3], fig->rgb))
		return (free_split(split));
	free_split(split);
	return (1);
}

int	ft_create_pl(char *line, t_pl *fig) 
{
	char	**split;

	fig->exist = 1;
	split = ft_split2(line, ' ', '	');
	if (!split)
		return (0);
	if (!get_triple_do(split[1], &fig->xyz))
		return (free_split(split));
	if (!get_triple_do(split[2], &fig->way))
		return (free_split(split));
	if (!get_triple_un(split[3], fig->rgb))
		return (free_split(split));
	free_split(split);
	return (1);
}

int	ft_create_cy(char *line, t_cy *fig)
{
	char	**split;

	fig->exist = 1;
	split = ft_split2(line, ' ', '	');
	if (!split)
		return (0);
	if (!get_triple_do(split[1], &fig->xyz))
		return (free_split(split));
	if (!get_triple_do(split[2], &fig->way))
		return (free_split(split));
	fig->width = ft_atof(split[3]);
	fig->height = ft_atof(split[4]);
	if (!get_triple_un(split[5], fig->rgb))
		return (free_split(split));
	free_split(split);
	return (1);
}

int	ft_malloc_a(t_var *p, char **lines)
{
	int	i;
	int	len;
	t_a	*fig;

	i = -1;
	len = 0;
	while (lines[++i])
		if (lines[i][0] == 'A')
			len++;
	fig = malloc((len + 1) * sizeof(t_a));
	if (!fig)
		return (0);
	len = 0;
	i = -1;
	while (lines[++i])
		if (lines[i][0] == 'A')
			if (!ft_create_a(lines[i], &fig[len++]))
				return (0);
	fig[len].exist = 0;
	p->a = fig;
	return (1);
}

int	ft_malloc_c(t_var *p, char **lines)
{
	int	i;
	int	len;
	t_c	*fig;

	i = -1;
	len = 0;
	while (lines[++i])
		if (lines[i][0] == 'C')
			len++;
	fig = malloc((len + 1) * sizeof(t_c));
	if (!fig)
		return (0);
	len = 0;
	i = -1;
	while (lines[++i])
		if (lines[i][0] == 'C')
			if (!ft_create_c(lines[i], &fig[len++]))
				return (0);
	fig[len].exist = 0;
	p->c = fig;
	return (1);
}

int	ft_malloc_l(t_var *p, char **lines)
{
	int	i;
	int	len;
	t_l	*fig;

	i = -1;
	len = 0;
	while (lines[++i])
		if (lines[i][0] == 'L')
			len++;
	fig = malloc((len + 1) * sizeof(t_l));
	if (!fig)
		return (0);
	len = 0;
	i = -1;
	while (lines[++i])
		if (lines[i][0] == 'L')
			if (!ft_create_l(lines[i], &fig[len++]))
				return (0);
	fig[len].exist = 0;
	p->l = fig;
	return (1);
}

int	ft_malloc_sp(t_var *p, char **lines)
{
	int	i;
	int	len;
	t_sp	*fig;

	i = -1;
	len = 0;
	while (lines[++i])
		if (lines[i][0] == 's' && lines[i][1] == 'p')
			len++;
	fig = malloc((len + 1) * sizeof(t_sp));
	if (!fig)
		return (0);
	len = 0;
	i = -1;
	while (lines[++i])
		if (lines[i][0] == 's' && lines[i][1] == 'p')
			if (!ft_create_sp(lines[i], &fig[len++]))
				return (0);
	fig[len].exist = 0;
	p->sp = fig;
	return (1);
}

int	ft_malloc_pl(t_var *p, char **lines)
{
	int	i;
	int	len;
	t_pl	*fig;

	i = -1;
	len = 0;
	while (lines[++i])
		if (lines[i][0] == 'p' && lines[i][1] == 'l')
			len++;
	fig = malloc((len + 1) * sizeof(t_pl));
	if (!fig)
		return (0);
	len = 0;
	i = -1;
	while (lines[++i])
		if (lines[i][0] == 'p' && lines[i][1] == 'l')
			if (!ft_create_pl(lines[i], &fig[len++]))
				return (0);
	fig[len].exist = 0;
	p->pl = fig;
	return (1);
}

int	ft_malloc_cy(t_var *p, char **lines)
{
	int	i;
	int	len;
	t_cy	*fig;

	i = -1;
	len = 0;
	while (lines[++i])
		if (lines[i][0] == 'c' && lines[i][1] == 'y')
			len++;
	fig = malloc((len + 1) * sizeof(t_cy));
	if (!fig)
		return (0);
	len = 0;
	i = -1;
	while (lines[++i])
		if (lines[i][0] == 'c' && lines[i][1] == 'y')
			if (!ft_create_cy(lines[i], &fig[len++]))
				return (0);
	fig[len].exist = 0;
	p->cy = fig;
	return (1);
}

int	ft_malloc_all(char **lines, t_var *p)
{
	if (!ft_malloc_a(p, lines))
		return (0);
	if (!ft_malloc_c(p, lines))
		return (0);
	if (!ft_malloc_l(p, lines))
		return (0);
	if (!ft_malloc_sp(p, lines))
		return (0);
	if (!ft_malloc_pl(p, lines))
		return (0);
	if (!ft_malloc_cy(p, lines))
		return (0);
	return (1);
}

int	parse_struc(t_var *p, char *file)
{
	char	**all_line;
	char	*temp;
	int		fd;

	fd = open(file, O_RDONLY);
	all_line = NULL;
	temp = get_next_line(fd);
	while (temp > 0)
	{
		if (temp[0] != '\n')
			all_line = ft_add_line(all_line, temp);
		else
			free(temp);
		temp = get_next_line(fd);
		// temp = no_double_space(temp);
	}
	close(fd);
	fd = ft_malloc_all(all_line, p);
	free_split(all_line);
	if (!fd)
		return (0);
	return (1);
}

int	ft_is_alpha(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!((s[i] >= 'a' && s[i] <= 'z') || \
		(s[i] >= 'A' && s[i] <= 'Z')))
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
	int				j;
	int				ret;
	unsigned char t[3];

	i = 0;
	j = 0;
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
	return(1);
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
		if (s[i] && s[i] != ',')
			return (0);
	}
	return (1);
}

int	check_a(char **lines)
{
	if (!ft_is_do(lines[1]) || \
	ft_atof(lines[1]) < 0.0 || ft_atof(lines[1]) > 1.0)
		return (0);
	if (!ft_is_triint(lines[2]))
		return (0);
	if (lines[3])
		return (0);
	return (1);
}

int	check_c(char **lines)
{
	t_vec	t;

	if (!ft_is_trido(lines[1]))
		return (0);
	if (!ft_is_trido(lines[2]))
		return (0);
	get_triple_do(lines[2], &t);
	if (t.x < -1.0 || t.x > 1.0 || t.y < -1.0 || \
	t.y > 1.0 || t.z < -1.0 || t.z > 1.0)
		return (0);
	if (!ft_is_int(lines[3]) || \
	ft_atoi(lines[3]) < 0 || ft_atoi(lines[3]) > 180)
		return (0);
	if (lines[4])
		return (0);
	return (1);
}

int	check_l(char **lines)
{
	if (!ft_is_trido(lines[1]))
		return (0);
	if (!ft_is_do(lines[2]) || \
	ft_atof(lines[2]) < 0.0 || ft_atof(lines[2]) > 1.0)
		return (0);
	if (!ft_is_triint(lines[3]))
		return (0);
	if (lines[4])
		return (0);
	return (1);
}

int	check_sp(char **lines)
{
	if (!ft_is_trido(lines[1]))
		return (0);
	if (!ft_is_do(lines[2]) || ft_atof(lines[2]) <= 0)
		return (0);
	if (!ft_is_triint(lines[3]))
		return (0);
	if (lines[4])
		return(0);
	return (1);
}

int	check_pl(char **lines)
{
	t_vec	t;

	if (!ft_is_trido(lines[1]))
		return (0);
	if (!ft_is_trido(lines[2]))
		return (0);
	get_triple_do(lines[2], &t);
	if (t.x < -1.0 || t.x > 1.0 || t.y < -1.0 || t.y > 1.0 \
	|| t.z < -1.0 || t.z > 1.0)
		return (0);
	if (!ft_is_triint(lines[3]))
		return (0);
	if (lines[4])
		return(0);
	return (1);
}

int	check_cy(char **lines)
{
	t_vec	t;

	if (!ft_is_trido(lines[1]))
		return (0);
	if (!ft_is_trido(lines[2]))
		return (0);
	get_triple_do(lines[2], &t);
	if (t.x < -1.0 || t.x > 1.0 || t.y < -1.0 || t.y > 1.0 \
	|| t.z < -1.0 || t.z > 1.0)
		return (0);
	if (!ft_is_do(lines[3]) || ft_atof(lines[3]) <= 0)
		return (0);
	if (!ft_is_do(lines[4]) || ft_atof(lines[4]) <= 0)
		return (0);
	if (!ft_is_triint(lines[5]))
		return (0);
	if (lines[6])
		return(0);
	return (1);
}


int	check_digits(char **lines)
{
	if (lines[0][0] == 'A')
		return (check_a(lines));
	else if (lines[0][0] == 'C')
		return (check_c(lines));
	else if (lines[0][0] == 'L')
		return (check_l(lines));
	else if (lines[0][0] == 's' && lines[0][1] == 'p')
		return (check_sp(lines));
	else if (lines[0][0] == 'p' && lines[0][1] == 'l')
		return (check_pl(lines));
	else if (lines[0][0] == 'c' && lines[0][1] == 'y')
		return (check_cy(lines));
	return (0);
}

void	ft_increase(int m[3], char c)
{
	if (c == 'A')
		m[0]++;
	if (c == 'C')
		m[1]++;
	if (c == 'L')
		m[2]++;
}

void	ft_null(int m[3])
{
	m[0] = 0;
	m[1] = 0;
	m[2] = 0;
}

int	ft_verif(char **lines)
{
	int		i;
	char	**split;
	int		m[3];

	i = 0;
	ft_null(m);
	while (lines[i])
	{
		split = ft_split2(lines[i], ' ', '	');
		if (!split)
			return (0);
		if (!ft_is_alpha(split[0]))
			return (free_split(split));
		if (split[0][0] == 'A' || split[0][0] == 'C' || split[0][0] == 'L')
			ft_increase(m, split[0][0]);
		if (m[0] > 1 || m[1] > 1 || m[2] > 1)
			return (free_split(split));
		if (!check_digits(split))
			return (free_split(split));
		free_split(split);
		i++;
	}
	return (1);
}

int	verif_input(char *file)
{
	char	**all_line;
	char	*temp;
	int		fd;

	fd = open(file, O_RDONLY);
	all_line = NULL;
	temp = no_double_space(get_next_line(fd));
	while (temp > 0)
	{
		if (temp[0] != '\n')
			all_line = ft_add_line(all_line, no_double_space(temp));
		else
			free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
	fd = ft_verif(all_line);
	free_split(all_line);
	if (!fd)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_var	p;

	if (ac != 2)
		return (1);
	if (!verif_input(av[1]))
	{
		dprintf(2, "input problem\n");
		return (1);
	}
	if (!parse_struc(&p, av[1]))
	{
		dprintf(2, "problem in parsing\n");
		return (1);
	}
	print_everything(&p);
	windowsop(&p);
	free_struc(&p);
}
