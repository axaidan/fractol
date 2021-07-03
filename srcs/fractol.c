#include "fractol.h"

/*
   long double	scale_coord(long double var, long double inf_bnd, long double res)
   {
   long double	interval;

   interval = 1.0 - (inf_bnd);
   return (((var * interval) / res) + inf_bnd);
   }
   */

int	continuous_pixel_scaling(int ite, t_pos c2)
{
	/*
	char	r;
	char	g;
	char	b;
	*/
	t_rgb		rgb;
	long double continuous_index;

	continuous_index = (long double)ite + 1.0 - ((logl(2) / fabsl(c2.x + c2.y)) / logl(2));
	rgb.r = (unsigned char)(sin(0.016 * continuous_index + 3) * 127.5 + 127.5);
	rgb.g = ((unsigned char)(sin(0.011 * continuous_index + 2) * 127.5 + 127.5));
	rgb.b = ((unsigned char)(sin(0.062 * continuous_index + 1) * 127.5 + 127.5));
	ite = (rgb.r << 16);
	ite += (rgb.g << 8);
	ite += rgb.b;
	return (ite);

}

int	mandelbrot(t_pos scaled, int max)
{
	t_pos	c1;
	t_pos	c2;
	int		ite;

	c2.x = 0.0;
	c2.y = 0.0;
	c1.x = 0.0;
	c1.y = 0.0;
	ite = 0;
	while (ite < max && (c2.x + c2.y) <= 4)
	{
		c1.y = (c1.x + c1.x) * c1.y + scaled.y;
		c1.x = c2.x - c2.y + scaled.x;
		c2.x = c1.x * c1.x;
		c2.y = c1.y * c1.y;
		ite++;
	}
	if (ite == max) 
		return (BLACK);
	else
		return (continuous_pixel_scaling(ite, c2));
		//		return (ite * ite);
		//		return (ite * ite * ite);
		//		return ((ite % 255 << 16) + (ite % 255 << 8) + (ite % 255));
}

void	draw_fractal(t_mlx *mlx)
{
	t_pt	pix;
	t_pos	scaled;
	int		color;

	pix.y = 0;
	ft_putstr_fd("Processing........", STDOUT_FILENO);
	while (pix.y < RES_Y)
	{
		scaled.y = (pix.y - (long double)RES_Y / 2.0) * mlx->scale + mlx->pos.y;
		pix.x = 0;
		if (pix.y == RES_Y / 2)
			ft_putstr_fd("Please wait.........", STDOUT_FILENO);
		while (pix.x < RES_X)
		{
			scaled.x = (pix.x - (long double)RES_X / 2.0) * mlx->scale + mlx->pos.x;
			color = mandelbrot(scaled, mlx->max_ite);
			my_mlx_pixel_put(&mlx->img, pix.x, pix.y, color);
			pix.x++;
		}
		pix.y++;
	}
	ft_putstr_fd("\a DONE !\n", STDOUT_FILENO);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr,
			0, 0);
}

/*
int	button_press(int button, int x, int y, t_mlx *mlx)
{
	if (button == UP_SCR)
		printf("Up scroll pressed\n");
	else if (button == DN_SCR)
		printf("Down scroll pressed\n");
    mlx->pos.x += (x - RES_X / 2) * mlx->scale;
    mlx->pos.y += (y - RES_Y / 2) * mlx->scale;
    if (button == UP_SCR)
    {
        //zoom_lvl++;
        mlx->scale /= 1.5;
        mlx->max_ite += 16;
        //agrandissement *= 1.5;
    }
    else if (button == DN_SCR)
    {
        //zoom_lvl--;
        mlx->scale *= 1.5;
        mlx->max_ite -= 16;
        //agrandissement /= 1.5;
    }
    draw_fractal(mlx);
	return (SUCCESS);
}

int	button_release(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	(void)mlx;
	if (button == UP_SCR)
		printf("Up scroll released\n");
	else if (button == DN_SCR)
		printf("Down scroll released\n");
	return (SUCCESS);
}
*/


int	fractol(t_mlx *mlx)
{
	draw_fractal(mlx);
	mlx_key_hook(mlx->win_ptr, key_pressed, mlx);
	mlx_mouse_hook(mlx->win_ptr, mouse_used, mlx);
//	mlx_hook(mlx->win_ptr, ButtonPress, ButtonPressMask, button_press, mlx);
//	mlx_hook(mlx->win_ptr, ButtonRelease, ButtonReleaseMask, button_release, mlx);
	mlx_loop_hook(mlx->mlx_ptr, shift_colors, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (SUCCESS);
}
