#include "fractol.h"

static void	display_help(void)
{
	ft_putchar_fd('\n', STDERR_FILENO);
	ft_putendl_fd("usage:\t./fractol [\"mandelbrot\", \"julia\"] [real] [imag]",
		STDERR_FILENO);
	ft_putendl_fd("\t(without argument default set is mandelbrot)",
		STDERR_FILENO);
	ft_putendl_fd("\tif you choose \"julia\" set, you can input two numbers",
		STDERR_FILENO);
	ft_putendl_fd("\tas c values for julia's real and imaginary C values",
		STDERR_FILENO);
	ft_putendl_fd("\t(julia's default C values are r = 0.285 and i = 0.013)\n",
		STDERR_FILENO);
	ft_putendl_fd("At run :", STDERR_FILENO);
	display_controls();
	ft_putendl_fd("You can approximately perform 90 zooms before pixellating\n",
		STDERR_FILENO);
	ft_putendl_fd("Enjoy\n\t\t\taxaidan", STDERR_FILENO);
}

int	print_ret_usage_err(int error)
{	
	if (error == ER_BAD_SET)
		ft_putendl_fd("arg one \'set\' neither \"mandelbrot\" nor \"julia\"",
			STDERR_FILENO);
	else if (error == ER_BAD_ARGC)
		ft_putendl_fd("program takes zero, one or three arguments",
			STDERR_FILENO);
	else if (error == ER_BAD_JPRMS)
		ft_putendl_fd("julia parameters must be numeric", STDERR_FILENO);
	else if (error == ER_ZERO_JPRM)
		ft_putendl_fd("julia parameter must not be zero", STDERR_FILENO);
	else if (error == ER_EMPTY_ARG)
		ft_putendl_fd("empty argument", STDERR_FILENO);
	return (error);
}	

int	print_ret_err(int error)
{
	if (error == FALSE)
		return (SUCCESS);
	ft_putstr_fd("ERROR - fractol: ", STDERR_FILENO);
	if (error == ER_MLX_INIT)
		ft_putendl_fd("mlx_init() failed", STDERR_FILENO);
	else if (error == ER_WIN_CREA)
		ft_putendl_fd("mlx_new_window() failed", STDERR_FILENO);
	else if (error == ER_IMG_CREA)
		ft_putendl_fd("mlx_new_image() failed", STDERR_FILENO);
	else if (error == ER_PATH_CONCAT)
		ft_putendl_fd("screenshot file name creation failed", STDERR_FILENO);
	else if (error == ER_BMP_OPEN)
		ft_putendl_fd("open(2) .bmp screenshot file failed", STDERR_FILENO);
	else if (error == ER_BMP_HDR || error == ER_DIB_HDR)
		ft_putendl_fd("write(2) .bmp screenshot file header failed",
			STDERR_FILENO);
	else if (error == ER_PIX_ARR)
		ft_putendl_fd("write(2) .bmp screenshot file failedd", STDERR_FILENO);
	if (error > ER_BAD_ARGC)
	{
		print_ret_usage_err(error);
		display_help();
	}
	return (error);
}
