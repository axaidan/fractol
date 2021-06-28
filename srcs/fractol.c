#include "fractol.h"

int	key_pressed(int key, t_mlx *mlx)
{
	if (key == ESC)
		close_mlx(mlx, FALSE);
	return (SUCCESS);
}

float	scale(float var, float inf_bnd, float sup_bnd, float res)
{
	float	interval;
	float	to_return;

	interval = sup_bnd - (inf_bnd);
	to_return = (((var * interval) / res) + inf_bnd);
//	printf("%.0fth pixel scaled in %.1f to %.1f (%.2f) interval is %.3f\n",
//			var, inf_bnd, sup_bnd, interval, to_return);
	return (to_return);
}

int	algo(t_pt pix)
{
	t_pos	scaled;
	float	x;
	float	y;
	float	temp_x;
	int		max;
	int		ite;

	scaled.x = scale((float)(pix.x), BND_X, 1.0, (float)RES_X);
	scaled.y = scale((float)(pix.y), BND_Y, 1.0, (float)RES_Y);
	x = 0.0;
	y = 0.0;
	ite = 0;
	max = 1000;
	while ((x * x + y * y) <= 2 * 2 && ite < max)
	{
		temp_x = x * x - y * y + scaled.x;
		y  = 2 * x * y + scaled.y;
		x = temp_x;
		ite++;
	}
	return (ite * ite);
}

void	draw_fractal(t_mlx *mlx)
{
	t_pt	pix;
	int		color;

	pix.y = 0;
	while (pix.y < RES_Y)
	{
		pix.x = 0;
		while (pix.x < RES_X)
		{
			color = algo(pix);
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
	mlx_hook(mlx->win_ptr, KeyPress, KeyPressMask, key_pressed, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (SUCCESS);
}
