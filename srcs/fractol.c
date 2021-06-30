#include "fractol.h"

int	key_pressed(int key, t_mlx *mlx)
{
	if (key == ESC)
		close_mlx(mlx, FALSE);
	return (SUCCESS);
}

int	mouse_used(int button, int x, int y, t_mlx *mlx)
{
	static int		zoom_lvl = 0;;
	static long double	bnd_x = BND_X;
	static long double	bnd_y = BND_Y;

	mlx->pos.x += (x - RES_X / 2) * mlx->scale;
	mlx->pos.y += (y - RES_Y / 2) * mlx->scale;
	if (button == UP_SCR)
	{
		zoom_lvl++;
		mlx->max_ite += 8;
		mlx->scale /= 1.5;
	}
	else if (button == DN_SCR)
	{
		zoom_lvl--;
		mlx->max_ite -= 8;
		mlx->scale *= 1.5;
	}
	printf("zoom_lvl\t= %d\n", zoom_lvl);
	printf("max\t\t= %d\n", mlx->max_ite);
	printf("ldouble scale\t\t= %.32Lf\n", mlx->scale);
	draw_fractal(mlx, bnd_x, bnd_y);
	return (SUCCESS);
}

long double	scale_coord(long double var, long double inf_bnd, long double res)
{
	long double	interval;

	interval = 1.0 - (inf_bnd);
	return (((var * interval) / res) + inf_bnd);
}

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
		return (ite * (ite << 3) * (ite << 4));
}

void	draw_fractal(t_mlx *mlx, long double bnd_x, long double bnd_y)
{
	(void)bnd_y;
	(void)bnd_x;
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
	printf("done\n\n");
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr,
		0, 0);
}

int	fractol(t_mlx *mlx)
{
	draw_fractal(mlx, BND_X, BND_Y);
	mlx_key_hook(mlx->win_ptr, key_pressed, mlx);
	mlx_mouse_hook(mlx->win_ptr, mouse_used, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (SUCCESS);
}
