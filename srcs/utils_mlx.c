#include "fractol.h"

void	change_pixel(t_img *img, int x, int y, int (*render)(int, t_cpx, int))
{
	char			*dst;
	t_rgb			rgb;
	int				color;

	dst = img->addr + (y * img->l_len + x * (img->bpp / 8));
	color = *(unsigned int *)dst;
	if (color == BLACK && render != black_and_white)
		return ;
	rgb.r = (color >> 16) - 1;
	rgb.g = (color >> 8) - 1;
	rgb.b = color - 1;
	color = (rgb.r << 16) + (rgb.g << 8) + rgb.b;
	*(unsigned int *)dst = color;
}

int	change_color_by(int color, int val)
{
	t_rgb			rgb;

	if (color == BLACK)
		return (color);
	rgb.r = (color >> 16) - val;
	rgb.g = (color >> 8) - val;
	rgb.b = color - val;
	color = (rgb.r << 16) + (rgb.g << 8) + rgb.b;
	return (color);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->l_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
