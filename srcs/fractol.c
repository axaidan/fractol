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

float	scale(float var, float inf_bnd, float sup_bnd, float res)
{
	float	interval;

	interval = sup_bnd - (inf_bnd);
	return (((var * interval) / res) + inf_bnd);
}

int	algo(t_pos scaled)
{
	t_pos	pos;
	float	temp_x;
	int		max;
	int		ite;

	pos.x = 0.0;
	pos.y = 0.0;
	ite = 0;
	max = 500;
	while ((pos.x * pos.x + pos.y * pos.y) <= 2 * 2 && ite < max)
	{
		temp_x = pos.x * pos.x - pos.y * pos.y + scaled.x;
		pos.y  = 2 * pos.x * pos.y + scaled.y;
		pos.x = temp_x;
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
		scaled.y = scale((float)(pix.y), bnd_y, 1.0, (float)RES_Y);
		pix.x = 0;
		while (pix.x < RES_X)
		{
			scaled.x = scale((float)(pix.x), bnd_x, 1.0, (float)RES_X);
			color = algo(scaled);
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
//	mlx_hook(mlx->win_ptr, KeyPress, KeyPressMask, key_pressed, mlx);
	mlx_key_hook(mlx->win_ptr, key_pressed, mlx);
	mlx_mouse_hook(mlx->win_ptr, mouse_used, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (SUCCESS);
}
