#include "fractol.h"

/*
   long double	scale_coord(long double var, long double inf_bnd, long double res)
   {
   long double	interval;

   interval = 1.0 - (inf_bnd);
   return (((var * interval) / res) + inf_bnd);
   }
   */

int	continuous_pixel_scaling(int ite, t_cpx c2, int set)
{
	t_rgb		rgb;
	long double cont_i;

	//	continuous_index = ite + 1.0 - ((logl(2) / fabsl(c2.imag + c2.real)) / logl(2));
	//	continuous_index = ite + 1.0 - ((logl(2) / fabsl(c2.imag + c2.imag)) / logl(2));
	//	continuous_index = ite + 1.0 - ((logl(2) / fabsl(c2.real + c2.real)) / logl(2));
	if (set == JULIA && c2.real + c2.imag > -0.18 && c2.real + c2.imag < 0.18)
		cont_i = ite;
	else
		cont_i = ite + 1.0 - ((logl(2) / fabsl(c2.imag + c2.real)) / logl(2));
	/*
	rgb.r = (unsigned char)(sin(0.016 * cont_i + 3) * 127.5 + 127.5);
	rgb.g = ((unsigned char)(sin(0.011 * cont_i + 2) * 127.5 + 127.5));
	rgb.b = ((unsigned char)(sin(0.062 * cont_i + 1) * 127.5 + 127.5));
	*/
	rgb.r = (unsigned char)(sin(0.050 * cont_i + 3) * 75 + 180);
	rgb.g = ((unsigned char)(sin(0.089 * cont_i + 2) * 75 + 180));
	rgb.b = ((unsigned char)(sin(0.075 * cont_i + 1) * 75 + 180));
	ite = (rgb.r << 16);
	ite += (rgb.g << 8);
	ite += rgb.b;
	return (ite);
}

int	mandelbrot(t_cpx scaled, int max)
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
		return (continuous_pixel_scaling(ite, c2, MANDE));
	//		return (ite);
	//		return (ite * ite);
	//		return (ite * ite * ite);
	//		return ((ite % 255 << 16) + (ite % 255 << 8) + (ite % 255));
}

int	julia(t_cpx c0, int max, t_cpx params)
{
	t_cpx		c;
	//	long double	real_temp;
	int			i;

	i = 0;
	while (c0.real * c0.real + c0.imag * c0.imag <= 2 * 2 && i < max)
	{
		c.real = c0.real;		// X
		c.imag = c0.imag;		// Y
		//		real_temp = c.real * c.real - c.imag * c.imag + c0.real;
		//		c.imag = 2.0 * c.real * c.imag + c0.imag;
		c0.real = c.real * c.real - c.imag * c.imag + params.real;
		c0.imag = 2.0 * c.real * c.imag + params.imag;
		//		c0.real = real_temp;
		i++;
	}
	if (i == max)
		return (BLACK);
	else
		//return (i * i * i);
		return (continuous_pixel_scaling(i, c0, JULIA));
}	

void	draw_fractal(t_mlx *mlx)
{
	t_pt	pix;
	t_cpx	scaled;
	int		color;

	pix.y = 0;

	ft_putstr_fd("Processing........", STDOUT_FILENO);
	while (pix.y < RES_Y)
	{
		scaled.imag = (pix.y - (long double)RES_Y / 2.0) * mlx->scale + mlx->pos.y;
		pix.x = 0;
		if (pix.y == RES_Y / 2)
			ft_putstr_fd("Please wait.........", STDOUT_FILENO);
		while (pix.x < RES_X)
		{
			scaled.real = (pix.x - (long double)RES_X / 2.0) * mlx->scale + mlx->pos.x;
			if (mlx->set == MANDE)
				color = mandelbrot(scaled, mlx->max_ite);
			else
				color = julia(scaled, mlx->max_ite, mlx->j_params);
			my_mlx_pixel_put(&mlx->img, pix.x, pix.y, color);
			pix.x++;
		}
		pix.y++;
	}
	ft_putstr_fd("\a DONE !\n", STDOUT_FILENO);
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
