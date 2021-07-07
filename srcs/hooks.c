#include "fractol.h"

void	change_render_method(t_mlx *mlx)
{
	static int	i = 2;

	i++;
	if (i == 5)
		i = 0;
	if (i == 0)
		mlx->render = simple_ite;
	else if (i == 1)
		mlx->render = square_ite;
	else if (i == 2)
		mlx->render = cube_ite;
	else if (i == 3)
		mlx->render = continuous_pixel_scaling;
	else if (i == 4)
		mlx->render = black_and_white;
}

int	key_pressed(int key, t_mlx *mlx)
{
	if (key == ESC)
		close_mlx(mlx, FALSE);
	else if (key == PLUS || key == MINUS || key == 'm' || key == 'r')
	{
		if (key == PLUS && mlx->max_ite < LIM_ITE)
			mlx->max_ite += CH_ITE;
		else if (key == MINUS && mlx->max_ite > CH_ITE)
			mlx->max_ite -= CH_ITE;
		else if (key == 'r')
			init_variables(mlx);
		else if (key == 'm')
			change_render_method(mlx);
		draw_fractal(mlx);
	}
	else if (key == UP_ARR || key == DN_ARR || key == LE_ARR || key == RI_ARR)
		move_fractal(mlx, key);
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
	mlx->pos.x += (x - RES_X / 2) * mlx->scale;
	mlx->pos.y += (y - RES_Y / 2) * mlx->scale;
	if (button == UP_SCR)
	{
		mlx->scale /= 1.5;
		if (mlx->max_ite > CH_ITE)
			mlx->max_ite += CH_ITE;
		mlx->pos.x -= (x - RES_X / 2) * mlx->scale;
		mlx->pos.y -= (y - RES_Y / 2) * mlx->scale;
	}
	else if (button == DN_SCR)
	{
		mlx->scale *= 1.5;
		if (mlx->max_ite < LIM_ITE)
			mlx->max_ite -= CH_ITE;
		mlx->pos.x -= (x - RES_X / 2) * mlx->scale;
		mlx->pos.y -= (y - RES_Y / 2) * mlx->scale;
	}
	draw_fractal(mlx);
	return (SUCCESS);
}

int	shift_colors(t_mlx *mlx)
{
	t_pt					pix;
	static int				inc_dec;
	static unsigned char	shift = 0;

	if (mlx->shift == TRUE)
	{
		if (shift == 0)
			inc_dec = 1;
		if (shift == 255)
			inc_dec = -1;
		shift += inc_dec;
		pix.y = 0;
		while (pix.y < RES_Y)
		{
			pix.x = 0;
			while (pix.x < RES_X)
				change_pixel(&mlx->img, pix.x++, pix.y, inc_dec);
			pix.y++;
		}
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr,
			0, 0);
	}
	return (SUCCESS);
}
