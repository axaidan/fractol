#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	s_pt
{
	int	x;
	int	y;
}				t_pt;

typedef struct	s_pos
{
	float	x;
	float	y;
}				t_pos;

typedef struct	s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		l_len;
	int		endian;
}				t_img;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	float	scale;
}				t_mlx;

#endif
