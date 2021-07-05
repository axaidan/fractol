#include "fractol.h"

void	change_render_method(t_mlx *mlx)
{
	static int	i = 0;

	i++;
	if (i == 4)
		i = 0;
	if (i == 0)
		mlx->render = simple_ite;
	else if (i == 1)
		mlx->render = square_ite;
	else if (i == 2)
		mlx->render = cube_ite;
	else if (i == 3)
		mlx->render = continuous_pixel_scaling;
}

int		continuous_pixel_scaling(int ite, t_cpx c2, int set)
{
	t_rgb       rgb;
	long double cont_i;

	//  continuous_index = ite + 1.0 - ((logl(2) / fabsl(c2.imag + c2.real)) / logl(2));
	//  continuous_index = ite + 1.0 - ((logl(2) / fabsl(c2.imag + c2.imag)) / logl(2));
	//  continuous_index = ite + 1.0 - ((logl(2) / fabsl(c2.real + c2.real)) / logl(2));
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

int	simple_ite(int ite, t_cpx c, int set)
{
	(void)c;
	(void)set;

	return (ite);
}

int	square_ite(int ite, t_cpx c, int set)
{
	(void)c;
	(void)set;

	return (ite * ite);
}

int	cube_ite(int ite, t_cpx c, int set)
{
	(void)c;
	(void)set;

	return (ite * ite * ite);
}
