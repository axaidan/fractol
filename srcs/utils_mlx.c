#include "fractol.h"

/*
t_rgb	shift_hue(t_rgb in, float shift)
{
  float U = cos(shift*M_PI/180);
  float W = sin(shift*M_PI/180);

  t_rgb ret;
  ret.r = (.299+.701*U+.168*W)*in.r
    + (.587-.587*U+.330*W)*in.g
    + (.114-.114*U-.497*W)*in.b;
  ret.g = (.299-.299*U-.328*W)*in.r
    + (.587+.413*U+.035*W)*in.g
    + (.114-.114*U+.292*W)*in.b;
  ret.b = (.299-.3*U+1.25*W)*in.r
    + (.587-.588*U-1.05*W)*in.g
    + (.114+.886*U-.203*W)*in.b;
  return ret;
}
*/

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
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->l_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}
