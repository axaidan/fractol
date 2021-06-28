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
	return (error);
}
