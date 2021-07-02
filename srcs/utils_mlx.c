#include "fractol.h"

void	change_pixel(t_img *img, int x, int y)
{
	char	*dst;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int		color;

	dst = img->addr + (y * img->l_len + x * (img->bpp / 8));
	color = *(unsigned int *)dst;
	if (color == BLACK)
		return ;
	r = (color >> 16) - 1;
	g = (color >> 8) - 1;
	b = color - 1;
	color = (r << 16) + (g << 8) + b;
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->l_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}
