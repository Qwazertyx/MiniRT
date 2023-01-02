/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:47:41 by vsedat            #+#    #+#             */
/*   Updated: 2022/12/20 11:19:25 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <sys/types.h>
# include "../mlx/mlx.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>

//Vecs
typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

//Window struct
typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				winwidth;
	int				winlength;
	int				sampleppix;
	int				depthmax;
	int				colorit;
	t_vec			po;
	t_vec			smpo;
	t_vec			no;
	t_vec			smno;
	t_vec			shadowpo;
	t_vec			shadowno;
}					t_data;

//Rays
typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}				t_ray;

//Ambient lightning:
typedef struct s_a
{
	double			ratio;
	double			init_ratio;
	unsigned char	rgb[3];
	int				exist;
}				t_a;

//Camera:
typedef struct s_c
{
	t_vec	xyz;
	t_vec	way;
	int		fov;
	int		exist;
}				t_c;

//Light:
typedef struct s_l
{
	t_vec			xyz;
	double			ratio;
	double			init_ratio;
	unsigned char	rgb[3];
	int				exist;
}				t_l;

//l colors
typedef struct s_pal
{
	unsigned char	rgb[3];
}						t_pal;

//Sphere:
typedef struct s_sp
{
	t_vec			xyz;
	double			height;
	unsigned char	rgb[3];
	int				exist;
}				t_sp;

//Plane:
typedef struct s_pl
{
	t_vec			xyz;
	t_vec			way;
	unsigned char	rgb[3];
	int				exist;
}				t_pl;

//Cylinder:
typedef struct s_cy
{
	t_vec			xyz;
	t_vec			way;
	double			height;
	double			width;
	unsigned char	rgb[3];
	int				exist;
}				t_cy;

//Cone:
typedef struct s_co
{
	t_vec			xyz;
	t_vec			way;
	double			height;
	double			angle;
	unsigned char	rgb[3];
	int				exist;
}				t_co;

////hitrecord
//typedef struct s_hitrc
//{
//	t_vec	p;
//	t_vec	normal;
//	double	t;
//	int		frontface;
//}				t_hitrc;

//Main struct
typedef struct s_var
{
	t_a		*a;
	t_c		*c;
	t_l		*l;
	t_sp	*sp;
	t_pl	*pl;
	t_cy	*cy;
	t_co	*co;
	t_data	*data;
	t_vec	*vec;
	double	t_min;
	double	t_max;
	int		x;
	int		y;
}				t_var;

//OBJECTS
double	contactsp(t_sp sphere, t_ray ray, t_var *p);
double	contactpl(t_pl plane, t_ray ray, t_var *p);
double	contactcy(t_cy cyl, t_ray ray, t_var *p);
double	contactcap(t_cy cyl, t_ray ray, t_var *p);
double	contactcap2(t_cy cyl, t_ray ray, t_var *p);

//INTERSECTIONS
double	inter_sp(t_var *p, t_ray myray, double min_t, unsigned char rgb[3]);
double	inter_pl(t_var *p, t_ray myray, double min_t, unsigned char rgb[3]);
double	inter(t_ray myray, t_var *p);
double	intershadow(t_var *p);

//COLOR
int		colorrgb(int r, int g, int b);
double	goodlux(double num);
int		endlux(t_vec lux, t_var *p, double light, unsigned char *color);
void	assignrgb(unsigned char *dst, unsigned char *src);

//CHECK
int		check_a(char **lines);
int		check_c(char **lines);
int		check_l(char **lines);
int		check_sp(char **lines);
int		check_pl(char **lines);
int		check_cy(char **lines);

//PRINT
int		ft_error(char **split);
void	ft_putstr_fd(char *str, int fd);
int		ft_puterror(char *str);

//FREE
void	free_struc(t_var *p);
int		free_split(char **a);

//FT_ATO
int		ft_atoi(char *s);
double	ft_atod(char *s);
double	ft_atof(char *s);

//FT_CREATE
int		ft_create_a(char *line, t_a *fig);
int		ft_create_c(char *line, t_c *fig);
int		ft_create_l(char *line, t_l *fig);
int		ft_create_sp(char *line, t_sp *fig);
int		ft_create_pl(char *line, t_pl *fig);
int		ft_create_cy(char *line, t_cy *fig);
void	ft_null(int m[3]);
void	ft_increase(int m[3], char c);

//FT_IS
int		ft_is_alpha(char *s);
int		ft_is_int(char *s);
int		ft_is_triint(char *s);
int		ft_is_do(char *s);
int		ft_is_trido(char *s);
int		ft_is_num(char **split);

//FT_JOIN
char	*ft_joinc(char *s1, char c);
char	*ft_joins(char *a, char *b);
char	*ft_joinsfree(char *a, char *b);

//FT_MALLOC
int		ft_malloc_a(t_var *p, char **lines);
int		ft_malloc_c(t_var *p, char **lines);
int		ft_malloc_l(t_var *p, char **lines);
int		ft_malloc_sp(t_var *p, char **lines);
int		ft_malloc_pl(t_var *p, char **lines);
int		ft_malloc_cy(t_var *p, char **lines);
int		ft_malloc_all(char **lines, t_var *p);

//FT_SPLIT
int		ft_nb_w(const char *s, char c);
char	**ft_split(char const *s, char c);
char	**ft_split2(char const *s, char c, char c1);

//FT_VERIF
int		ft_verif(char **lines);
int		check_digits(char **lines);
int		verif_input(char *file);
int		is_empty(char *s);

//GENERATOR
double	raycolor(double min_t, t_var *p, unsigned char *color);

//GET_NEXT_LINE
int		ft_strlen(char *a);
int		ft_strlenn(char *a);
char	*ft_join(char *a, char *b);
int		ft_search(char *a, char c);
void	ft_cut(char *a);
char	*ft_free(char *a);
char	*get_next_line(int fd);

//GET
int		get_triple_do(char *s, t_vec *t);
int		get_triple_un(char *s, unsigned char t[3]);
int		parse_struc(t_var *p, char *file);

//STRMOD
char	**ft_add_line(char **old, char *to_add);
char	*no_double_space(char *str);

//WINDOWS PARAMETERS
int		windowsop(t_var *p);
void	mypixelput(t_data *data, int x, int y, int color);
void	generator(t_var *p);
int		closewin(t_data *data);

//VECTORS
t_vec	vecadd(t_vec v1, t_vec v2);
t_vec	vecadd3(t_vec v1, t_vec v2, t_vec v3);
t_vec	vecsub(t_vec v1, t_vec v2);
t_vec	vecmult(t_vec v1, double mult);
t_vec	vecdiv(t_vec v1, double mult);
t_vec	veccross(t_vec v1, t_vec v2);
t_vec	newvec(double x, double y, double z);
double	vecdot(t_vec v1, t_vec v2);
double	vecnorm(t_vec v1);
void	normalize(t_vec v1);
t_vec	vecunit(t_vec v1);
double	veclen(t_vec v1);
t_vec	vecat(t_ray ray, double t);
t_vec	getnorm(t_vec v1);
t_vec	getnormalized(t_vec v1);
t_vec	met_a_un(t_vec v1);

#endif
