#include "fractol.h"

int	key_pressed(int key, t_mlx *mlx)
{
	if (key == ESC)
		close_mlx(mlx, FALSE);
	else if (key == PLUS || key == MINUS)
	{
		if (key == PLUS)
			mlx->max_ite += 16;
		if (key == MINUS)
			mlx->max_ite -= 16;
		draw_fractal(mlx);
	}
	else if (key == 'r')
	{
		init_variables(mlx);
		draw_fractal(mlx);
	}
	else if (key == 's' && mlx->shift == FALSE)
		mlx->shift = TRUE;
	else if (key == 's' && mlx->shift == TRUE)
		mlx->shift = FALSE;
	else if (key == 'i')
		display_info(mlx);
	return (SUCCESS);
}

int	mouse_used(int button, int x, int y, t_mlx *mlx)
{
	//	static int          zoom_lvl = 0;;
	//	static long double  agrandissement = 1.0;

	mlx->pos.x += (x - RES_X / 2) * mlx->scale;
	mlx->pos.y += (y - RES_Y / 2) * mlx->scale;
	if (button == UP_SCR)
	{
		//zoom_lvl++;
		mlx->scale /= 1.5;
		mlx->max_ite += 16;
		//agrandissement *= 1.5;
	}
	else if (button == DN_SCR)
	{
		//zoom_lvl--;
		mlx->scale *= 1.5;
		mlx->max_ite -= 16;
		//agrandissement /= 1.5;
	}
	draw_fractal(mlx);
	return (SUCCESS);
}

int	shift_colors(t_mlx *mlx)
{
	t_pt			pix;
	static float	shift = 0.0;
	float			sinusoid;

	sinusoid = sin(shift);
	if (mlx->shift == TRUE)
	{
		pix.y = 0;
		while(pix.y < RES_Y)
		{
			pix.x = 0;
			while (pix.x < RES_X)
			{
				change_pixel(&mlx->img, pix.x, pix.y, sinusoid);
				pix.x++;
			}
			pix.y++;
		}
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr,
				0, 0);
	}
	shift += 0.01;
	return (SUCCESS);
}
