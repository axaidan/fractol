#include "fractol.h"

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
