#include "fractol.h"

int	print_ret_err(int error)
{
	if (error == FALSE)
		return (SUCCESS);
	ft_putstr_fd("ERROR - fractol: ", STDERR_FILENO);
	if (error == ER_MLX_INIT)
		ft_putendl_fd("mlx_init()", STDERR_FILENO);
	else if (error == ER_WIN_CREA)
		ft_putendl_fd("mlx_new_window()", STDERR_FILENO);
	else if (error == ER_IMG_CREA)
		ft_putendl_fd("mlx_new_image()", STDERR_FILENO);
	else if (error == ER_BAD_SET)
		ft_putendl_fd("arg one \'set\' neither \"mandelbrot\" nor \"julia\"",
			STDERR_FILENO);
	else if (error == ER_BAD_ARGC)
		ft_putendl_fd("program takes zero, one or three arguments",
			STDERR_FILENO);
	else if (error == ER_BAD_JPRMS)
		ft_putendl_fd("julia parameters must be numeric", STDERR_FILENO);
	else if (error == ER_ZERO_JPRM)
		ft_putendl_fd("julia parameter must not be zero", STDERR_FILENO);
//	if (error > ER_BAD_ARGC)
//		display_help();
	return (error);
}
