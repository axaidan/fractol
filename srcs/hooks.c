#include "fractol.h"

int	key_pressed(int key, t_mlx *mlx)
{
//	printf("%d\n", key);
	if (key == ESC)
		close_mlx(mlx, FALSE);
	else if (key == PLUS || key == MINUS)
	{
		if (key == PLUS)
			mlx->max_ite += 16;
		if (key == MINUS)
			mlx->max_ite += 16;
		draw_fractal(mlx);
	}
	else if (key == 'r')
	{
		init_variables(mlx);
		draw_fractal(mlx);
	}
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
		//agrandissement *= 1.5;
	}
	else if (button == DN_SCR)
	{
		//zoom_lvl--;
		mlx->scale *= 1.5;
		//agrandissement /= 1.5;
	}
	draw_fractal(mlx);
	return (SUCCESS);
}
