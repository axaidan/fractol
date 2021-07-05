#include "fractol.h"

int main(int argc, char *argv[])
{
	t_mlx	mlx;
	int		error;
	t_args	args;

	error = 0;
	init_mlx_struct(&mlx);
	init_args_struct(&args, argc, argv);
	if (argc > 1)
	{
		error = check_args(&args);
		if (error)
			return (error);
		mlx.j_params = args.j_params;
		mlx.set = args.set;
	}
	error = start_mlx(&mlx);
	if (error)
		return (error);
	error = fractol(&mlx);
	if (error)
		return (error);
	close_mlx(&mlx, error);
	return (SUCCESS);
}
