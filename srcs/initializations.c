#include "fractol.h"

void	init_variables(t_mlx *mlx)
{
	mlx->scale = 1.0 / 128.0;
	mlx->pos.x = 0.0;
	mlx->pos.y = 0.0;
	mlx->max_ite = 256;
	mlx->shift = FALSE;
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
