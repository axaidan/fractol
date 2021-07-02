#include "fractol.h"

/*
long double	scale_coord(long double var, long double inf_bnd, long double res)
{
	long double	interval;

	interval = 1.0 - (inf_bnd);
	return (((var * interval) / res) + inf_bnd);
}
*/

int	mandelbrot(t_pos scaled, int max)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	t_pos	c1;
	t_pos	c2;
	int		ite;
	long double continuous_index;

	c2.x = 0.0;
	c2.y = 0.0;
	c1.x = 0.0;
	c1.y = 0.0;
	ite = 0;
	while (ite < max && (c2.x + c2.y) <= 4)
	{
		c1.y = (c1.x + c1.x) * c1.y + scaled.y;
		c1.x = c2.x - c2.y + scaled.x;
		c2.x = c1.x * c1.x;
		c2.y = c1.y * c1.y;
		ite++;
	}
	if (ite == max) 
		return (BLACK);
	else
	{
		continuous_index = (long double)ite + 1.0 - ((logl(2) / fabsl(c2.x + c2.y)) / logl(2));
		r = (unsigned char)(sin(0.016 * continuous_index + 4) * 127.5 + 127.5);
		g = ((unsigned char)(sin(0.011 * continuous_index + 4) * 127.5 + 127.5));
		b = ((unsigned char)(sin(0.062 * continuous_index + 4) * 127.5 + 127.5));
		ite = (r << 16);
		ite += (g << 8);
		ite += b;
//		return (ite * ite * ite);
//		return (ite * ite);
		return (ite);
//		return ((ite % 255 << 16) + (ite % 255 << 8) + (ite % 255));
	}
}

void	draw_fractal(t_mlx *mlx)
{
	t_pt	pix;
	t_pos	scaled;
	int		color;

	pix.y = 0;
	ft_putstr_fd("Processing........", STDOUT_FILENO);
	while (pix.y < RES_Y)
	{
		scaled.y = (pix.y - (long double)RES_Y / 2.0) * mlx->scale + mlx->pos.y;
		pix.x = 0;
		while (pix.x < RES_X)
		{
			scaled.x = (pix.x - (long double)RES_X / 2.0) * mlx->scale + mlx->pos.x;
			color = mandelbrot(scaled, mlx->max_ite);
			my_mlx_pixel_put(&mlx->img, pix.x, pix.y, color);
			pix.x++;
		}
		pix.y++;
	}
	ft_putstr_fd(" DONE !\n", STDOUT_FILENO);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr,
			0, 0);
}

int	fractol(t_mlx *mlx)
{
	draw_fractal(mlx);
	mlx_key_hook(mlx->win_ptr, key_pressed, mlx);
	mlx_mouse_hook(mlx->win_ptr, mouse_used, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (SUCCESS);
}
