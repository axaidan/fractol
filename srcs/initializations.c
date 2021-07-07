#include "fractol.h"

void	init_start_bounds_pts(int key, t_pt *start, t_pt *bounds)
{
	if (key == UP_ARR)
	{
		start->x = 0;
		start->y = 0;
		bounds->x = RES_X;
		bounds->y = RES_Y - RES_Y / MOVE_PERCENTAGE;
	}
	else if (key == DN_ARR)
	{
		start->x = 0;
		start->y = RES_Y - RES_Y / MOVE_PERCENTAGE;
		bounds->x = RES_X;
		bounds->y = RES_Y;
	}
	else if (key == LE_ARR)
	{
		start->x = 0;
		start->y = 0;
		bounds->x = RES_X - RES_X / MOVE_PERCENTAGE;
		bounds->y = RES_Y;
	}
	else
	{
		start->x = RES_X - RES_X / MOVE_PERCENTAGE;
		start->y = 0;
		bounds->x = RES_X;
		bounds->y = RES_Y;
	}
}

void	init_args_struct(t_args *args, int argc, char **argv)
{
	args->argc = argc;
	args->argv = argv;
	args->set = MANDE;
	args->j_params.real = cRe;
	args->j_params.imag = cIm;
}

void	init_variables(t_mlx *mlx)
{
	static int	first_time = TRUE;


	mlx->scale = 1.0 / 128.0;
	mlx->pos.x = 0.0;
	mlx->pos.y = 0.0;
	mlx->max_ite = 256;
	mlx->shift = FALSE;
	if (first_time == TRUE)
	{
		mlx->set = MANDE;
		mlx->j_params.real = 0.0;
		mlx->j_params.imag = 0.0;
		mlx->render = continuous_pixel_scaling;
	}
	first_time = FALSE;
}

void	init_mlx_struct(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->img.img_ptr = NULL;
	mlx->img.addr = NULL;
	mlx->img.bpp = -1;
	mlx->img.l_len = -1;
	mlx->img.endian = -1;
	/*
	   mlx->scale = 1.0 / 128.0;
	   mlx->pos.x = 0.0;
	   mlx->pos.y = 0.0;
	   mlx->max_ite = 256;
	   */
	init_variables(mlx);
}
