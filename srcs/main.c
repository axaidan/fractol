#include "fractol.h"

int main(void)
{
	t_mlx	mlx;
	int		error;

	error = 0;
	printf("sizeof(float)\t= %ld\n", sizeof(float));
	printf("sizeof(double)\t= %ld\n", sizeof(double));
	printf("sizeof(long double)\t= %ld\n", sizeof(long double));
	init_mlx_struct(&mlx);
	error = start_mlx(&mlx);
	if (error)
		return (error);
	error = fractol(&mlx);
	if (error)
		return (error);
	close_mlx(&mlx, error);
	return (SUCCESS);
}
