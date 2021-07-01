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
	t_pos	c1;
	t_pos	c2;
	int		ite;

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
		return (WHITE);
	else
		return (ite * ite * ite);
//		return ((ite % 255 << 16) + (ite % 255 << 8) + (ite % 255));
}

void	draw_fractal(t_mlx *mlx)
{
	t_pt	pix;
	t_pos	scaled;
	int		color;

	pix.y = 0;
	while (pix.y < RES_Y)
	{
		scaled.y = (pix.y - (long double)RES_Y / 2.0) * mlx->scale + mlx->pos.y;
		pix.x = 0;
		while (pix.x < RES_X)
		{
			scaled.x = (pix.x - (long double)RES_X / 2.0) * mlx->scale + mlx ->pos.x;
			color = mandelbrot(scaled, mlx->max_ite);
			my_mlx_pixel_put(&mlx->img, pix.x, pix.y, color);
			pix.x++;
		}
		pix.y++;
	}
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
