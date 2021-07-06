#include "fractol.h"

int	mandelbrot(t_cpx scaled, int max, int (*render)(int, t_cpx, int))
{
	t_cpx	c1;
	t_cpx	c2;
	int		ite;

	c2.real = 0.0;
	c2.imag = 0.0;
	c1.real = 0.0;
	c1.imag = 0.0;
	ite = 0;
	while (ite < max && (c2.real + c2.imag) <= 4)
	{
		c1.imag = (c1.real + c1.real) * c1.imag + scaled.imag;
		c1.real = c2.real - c2.imag + scaled.real;
		c2.real = c1.real * c1.real;
		c2.imag = c1.imag * c1.imag;
		ite++;
	}
	if (ite == max)
		return (BLACK);
	else
		return (render(ite, c2, MANDE));
}

int	julia(t_cpx c0, int max, t_cpx params, int (*render)(int, t_cpx, int))
{
	t_cpx		c;
	long double	real_temp;
	int			i;

	i = 0;
	while (c0.real * c0.real + c0.imag * c0.imag <= 4 && i < max)
	{
		c.real = c0.real;
		c.imag = c0.imag;
		real_temp = c.real * c.real - c.imag * c.imag + params.real;
		c0.imag = 2.0 * c.real * c.imag + params.imag;
		c0.real = real_temp;
		i++;
	}
	if (i == max)
		return (BLACK);
	else
		return (render(i, c0, JULIA));
}	

void	draw_fractal(t_mlx *mlx)
{
	t_pt	pix;
	t_cpx	scaled;
	int		color;

	pix.y = 0;
	while (pix.y < RES_Y)
	{
		scaled.imag = (pix.y - RES_Y / 2.0) * mlx->scale + mlx->pos.y;
		pix.x = 0;
		while (pix.x < RES_X)
		{
			scaled.real = (pix.x - RES_X / 2.0) * mlx->scale + mlx->pos.x;
			if (mlx->set == MANDE)
				color = mandelbrot(scaled, mlx->max_ite, mlx->render);
			else
				color = julia(scaled, mlx->max_ite, mlx->j_params, mlx->render);
			my_mlx_pixel_put(&mlx->img, pix.x, pix.y, color);
			display_render_progress(pix);
			pix.x++;
		}
		pix.y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr,
		0, 0);
}

int	fractol(t_mlx *mlx)
{
	draw_fractal(mlx);
	mlx_key_hook(mlx->win_ptr, key_pressed, mlx);
	mlx_mouse_hook(mlx->win_ptr, mouse_used, mlx);
	mlx_loop_hook(mlx->mlx_ptr, shift_colors, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (SUCCESS);
}
