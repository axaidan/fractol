#include "fractol.h"

int		continuous_pixel_scaling(int ite, t_cpx c2, int set)
{
	t_rgb       rgb;
	long double cont_i;

	if (set == JULIA && c2.real + c2.imag > -0.18 && c2.real + c2.imag < 0.18)
		cont_i = ite;
	else
		cont_i = ite + 1.0 - ((logl(2) / fabsl(c2.imag + c2.real)) / logl(2));
	/*  
	rgb.r = (unsigned char)(sin(0.016 * cont_i + 3) * 127.5 + 127.5);
	rgb.g = ((unsigned char)(sin(0.011 * cont_i + 2) * 127.5 + 127.5));
	rgb.b = ((unsigned char)(sin(0.062 * cont_i + 1) * 127.5 + 127.5));
	*/
	rgb.r = (unsigned char)(sin(0.016 * cont_i + 4) * 230 + 25);
	rgb.g = ((unsigned char)(sin(0.013 * cont_i + 2) * 230 + 25));
	rgb.b = ((unsigned char)(sin(0.01 * cont_i + 1) * 230 + 25));
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

int	black_and_white(int ite, t_cpx c, int set)
{
	(void)c;
	(void)set;

	return ((ite % 255 << 16) + (ite % 255 << 8) + (ite % 255));
}
