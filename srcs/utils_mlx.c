#include "fractol.h"

void	change_pixel(t_img *img, int x, int y, int shift)
{
	char			*dst;
	t_rgb			rgb;
	int				color;

	dst = img->addr + (y * img->l_len + x * (img->bpp / 8));
	color = *(unsigned int *)dst;
	if (color == BLACK)
		return ;
	rgb.r = (color >> 16) + shift;
	rgb.g = (color >> 8) + shift;
	rgb.b = color + shift;
	color = (rgb.r << 16) + (rgb.g << 8) + rgb.b;
	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->l_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
