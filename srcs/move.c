#include "fractol.h"

//       void *memmove(void *dest, const void *src, size_t n);

void	move_pixels_horizontally(t_mlx *mlx, int key)
{
	int		offset;
	int		y;
	char	*pix_arr;
	int		l_len; // EN CHAR

	pix_arr = mlx->img.addr;
	l_len = mlx->img.l_len;
	offset = l_len / MOVE_PERCENTAGE;
	y = 0;
	while (y < RES_Y)
	{
		if (key == LE_ARR)
			ft_memmove((pix_arr + (y * l_len)) + offset,
					pix_arr + (y * l_len),
					sizeof(int) * (RES_X - RES_X / MOVE_PERCENTAGE));
		else if (key == RI_ARR)
			ft_memmove(pix_arr + (y * l_len),
					(pix_arr + (y * l_len)) + offset,
					sizeof(int) * (RES_X - RES_X / MOVE_PERCENTAGE));
		y++;
	}
}

void	move_pixels_down(t_mlx *mlx)
{
	int		y;
	char	*pix_arr;
	int		l_len;
	int		to;

	pix_arr = mlx->img.addr;
	l_len = mlx->img.l_len;
	y = RES_Y / MOVE_PERCENTAGE;
	to = 0;
	while (y < RES_Y)
	{
		ft_memmove(pix_arr + (to * l_len), pix_arr + (y * l_len), l_len);
		to++;
		y++;
	}
}

void	move_pixels_up(t_mlx *mlx)
{
	int		y;
	char	*pix_arr;
	int		l_len;
	int		to;

	pix_arr = mlx->img.addr;
	l_len = mlx->img.l_len;
	y = RES_Y - RES_Y / MOVE_PERCENTAGE;
	to = RES_Y;
	while (y >= 0)
	{
		ft_memmove(pix_arr + (to * l_len), pix_arr + (y * l_len), l_len);
		to--;
		y--;
	}
}

void	calculate_remaining(t_mlx *mlx, int key)
{
	t_pt	start;
	t_pt	pix;
	t_pt	bounds;
	t_cpx	scaled;
	int		color;

	init_start_bounds_pts(key, &start, &bounds);
	pix.y = start.y;
	printf("remaining starting...\n");
	while (pix.y < bounds.y)
	{
		scaled.imag = (pix.y - RES_Y / 2.0) * mlx->scale + mlx->pos.y;
		pix.x = start.x;
		while (pix.x < bounds.x)
		{
			scaled.real = (pix.x - RES_X / 2.0) * mlx->scale + mlx->pos.x;
			if (mlx->set == MANDE)
				color = mandelbrot(scaled, mlx->max_ite, mlx->render);
			else
				color = julia(scaled, mlx->max_ite, mlx->j_params, mlx->render);
            my_mlx_pixel_put(&mlx->img, pix.x, pix.y, color);
			pix.x++;
		}
		pix.y++;
	}
	printf("remaining finished..\n");
}

void	move_fractal(t_mlx *mlx, int key)
{
	printf("moving starting...\n");
	if (key == LE_ARR || key == RI_ARR)
	{
		move_pixels_horizontally(mlx, key);
		if (key == LE_ARR)
			mlx->pos.x += -(RES_X / MOVE_PERCENTAGE) * mlx->scale;
		else if (key == RI_ARR)
			mlx->pos.x += (RES_X / MOVE_PERCENTAGE) * mlx->scale;
	}
	else if (key == UP_ARR)
	{
		move_pixels_up(mlx);
		mlx->pos.y += -(RES_Y / MOVE_PERCENTAGE) * mlx->scale;
	}
	else if (key == DN_ARR)
	{
		move_pixels_down(mlx);
		mlx->pos.y += (RES_Y / MOVE_PERCENTAGE) * mlx->scale;
	}
	printf("moving finished...\n");
	calculate_remaining(mlx, key);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return ;
}
