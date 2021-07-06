#include "fractol.h"

//       void *memmove(void *dest, const void *src, size_t n);

void	move_pixels(t_mlx *mlx, int key)
{
	int		offset;
	t_pt	pix;
	char	*pix_arr;
	int		l_len; // EN CHAR

//	offset = (RES_X - RES_X / 10) * sizeof(int);
	pix_arr = mlx->img.addr;
	l_len = mlx->img.l_len;
	offset = l_len / 10;
	printf("l_len = %d\n", l_len);
	printf("offset = %d\n", offset);
	if (key == LE_ARR)
	{
		pix.y = 0;
		pix.x = 0;
		while (pix.y < RES_Y)
		{
			ft_memmove(pix_arr + (pix.y * l_len),
				(pix_arr + (pix.y * l_len)) + offset,
				sizeof(int) * (RES_X - RES_X / 10));
			pix.y++;
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}

void	move_fractal(t_mlx *mlx, int key)
{
	move_pixels(mlx, key);
	(void)key;
	mlx->pos.x += (RES_X / 2 - (RES_X - RES_X / 10)) / 2.0 * mlx->scale;
//	mlx->pos.y += (RES_Y / 2 - (RES_Y - RES_Y / 10)) / 2.0 * mlx->scale;
	//draw_fractal(mlx);

	return ;
}
