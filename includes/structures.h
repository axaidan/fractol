#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_pt
{
	int	x;
	int	y;
}	t_pt;

typedef struct s_pos
{
	long double	x;
	long double	y;
}	t_pos;

typedef struct s_cpx
{
	long double	real;
	long double	imag;
}	t_cpx;

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgb;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		l_len;
	int		endian;
}	t_img;

typedef struct s_args
{
	int		argc;
	char	**argv;
	int		set;
	t_cpx	j_params;
}	t_args;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
	long double		scale;
	t_pos			pos;
	int				max_ite;
	int				shift;
	int				set;
	t_cpx			j_params;
	int				(*render)(int, t_cpx, int);
	t_pt			center;
	unsigned char	shift_val;
}	t_mlx;

#endif
