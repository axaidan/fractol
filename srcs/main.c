#include "fractol.h"

int main(int argc, char *argv[])
{
	t_mlx	mlx;
	int		error;
	t_args	args;

	error = 0;
	init_mlx_struct(&mlx);
	init_args_struct(&args, argc, argv);
	error = start_mlx(&mlx);
	if (error)
		return (error);
	error = fractol(&mlx);
	if (error)
		return (error);
	close_mlx(&mlx, error);
	return (SUCCESS);
}
