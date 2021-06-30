#include "fractol.h"

int	key_pressed(int key, t_mlx *mlx)
{
	if (key == ESC)
		close_mlx(mlx, FALSE);
	return (SUCCESS);
}

int	mouse_used(int button, int x, int y, t_mlx *mlx)
{
	static float	bnd_x = BND_X;
	static float	bnd_y = BND_Y;

	(void)x;
	(void)y;
	if (button == UP_SCR)
	{
		bnd_x -= 0.1;
		bnd_y -= 0.1;
	}
	else if (button == DN_SCR)
	{
		bnd_x += 0.1;
		bnd_y += 0.1;
	}
	draw_fractal(mlx, bnd_x, bnd_y);
	return (SUCCESS);
}

float	scale_coord(float var, float inf_bnd, float sup_bnd, float res)
{
	float	interval;

	interval = sup_bnd - (inf_bnd);
	return (((var * interval) / res) + inf_bnd);
}

int	mandelbrot(t_pos scaled)
{
	t_pos	c1;
	t_pos	c2;
	int		ite;
	int		max;

	c2.x = 0.0;
	c2.y = 0.0;
	c1.x = 0.0;
	c1.y = 0.0;
	ite = 0;
	max = 500;
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
		return (ite * ite);
}

void	draw_fractal(t_mlx *mlx, float bnd_x, float bnd_y)
{
	t_pt	pix;
	t_pos	scaled;
	int		color;

	pix.y = 0;
	while (pix.y < RES_Y)
	{
		scaled.y = scale_coord((float)(pix.y), bnd_y, 1.0, (float)RES_Y);
		pix.x = 0;
		while (pix.x < RES_X)
		{
			scaled.x = scale_coord((float)(pix.x), bnd_x, 1.0, (float)RES_X);
			color = mandelbrot(scaled);
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
	draw_fractal(mlx, BND_X, BND_Y);
	mlx_key_hook(mlx->win_ptr, key_pressed, mlx);
	mlx_mouse_hook(mlx->win_ptr, mouse_used, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (SUCCESS);
}
