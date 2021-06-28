#include "fractol.h"

int	close_mlx(t_mlx *mlx, int error)
{
	if (mlx->mlx_ptr)
	{
		if (mlx->win_ptr)
			mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		if (mlx->img.img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		mlx->mlx_ptr = NULL;
	}
	if (error)
		print_ret_err(error);
	exit(error);
	return (SUCCESS);
}

int	start_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return (close_mlx(mlx, ER_MLX_INIT));
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, RES_X, RES_Y, "fractol");
	if (mlx->win_ptr == NULL)
		return (close_mlx(mlx, ER_WIN_CREA));
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, RES_X, RES_Y); 
	if (mlx->img.img_ptr == NULL)
		return (close_mlx(mlx, ER_IMG_CREA));
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,
		&mlx->img.l_len, &mlx->img.endian);
	return (SUCCESS);
}
