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
	t_vec			po;
	t_vec			smpo;
	t_vec			no;
	t_vec			smno;
	t_vec			shadowpo;
	t_vec			shadowno;
}					t_data;

//Ambient lightning:
typedef struct s_a
{
	double			ratio;
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
	unsigned char	rgb[3];
	int				exist;
}				t_l;

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


//Rays
typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}				t_ray;

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
	t_data	*data;
	t_vec	*vec;
	double	t_min;
	double	t_max;
}				t_var;

//PRINT
void	print_everything(t_var *p);

//FREE
void	free_struc(t_var *p);

//FT_JOIN
char	*ft_joinc(char *s1, char c);
char	*ft_joins(char *a, char *b);
char	*ft_joinsfree(char *a, char *b);

//FT_SPLIT
char	**ft_split(char const *s, char c);
char	**ft_split2(char const *s, char c, char c1);

//GET_NEXT_LINE
int		ft_strlen(char *a);
int		ft_strlenn(char *a);
char	*ft_join(char *a, char *b);
int		ft_search(char *a, char c);
void	ft_cut(char *a);
char	*ft_free(char *a);
char	*get_next_line(int fd);

//WINDOWS PARAMETERS
int		windowsop(t_var *p);
void	mypixelput(t_data *data, int x, int y, int color);
void	generator(t_var *p);
int		closewin(t_data *data);

//VECTORS UTILS
t_vec	vecadd(t_vec v1, t_vec v2);
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

#endif
