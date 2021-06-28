#include "fractol.h"

void	init_mlx_struct(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->img.img_ptr = NULL;
	mlx->img.addr = NULL;
	mlx->img.bpp = -1;
	mlx->img.l_len = -1;
	mlx->img.endian = -1;
}
