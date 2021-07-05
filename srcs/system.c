#include "fractol.h"

static long double	mini_atold(char *s, int *error)
{
	int			sign;
	long int	n_part; 
	long int	f_part;
	int			pow;
	
	sign = 1;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	n_part = 0;
	while (*s && ft_isdigit(*s))
		n_part = n_part * 10 + *(s++) - '0';
	if (*s == '.')
		s++;
	f_part = 0;
	pow = 1;
	while (*s && ft_isdigit(*s))
	{
		f_part = f_part * 10 + *(s++) - '0';
		pow *= 10;
	}
	if (*s != '\0' && ft_isdigit(*s == FALSE))
		*error = ER_BAD_JPRMS;
	return(sign * ((long double)n_part + ((long double)f_part / pow)));
}

static int get_julia_params(t_args *args)
{
	int	error;

	error = 0;
	args->j_params.real = mini_atold(args->argv[2], &error);
	printf("j_p.real = %Lf\n", args->j_params.real);
	if (error)
		return (close_mlx(NULL, error));
	args->j_params.imag = mini_atold(args->argv[3], &error);
	printf("j_p.imag = %Lf\n", args->j_params.imag);
	if (error)
		return (close_mlx(NULL, error));
	return (SUCCESS);
}

int	check_args(t_args *args)
{
	int	error;

	error = 0;
	if (args->argc != 1 && args->argc != 2 && args->argc != 4)
		return (close_mlx(NULL, ER_BAD_ARGC));
	if (ft_strncmp("mandelbrot", args->argv[1], 11) == 0)
		args->set = MANDE;
	else if (ft_strncmp("julia", args->argv[1], 6) == 0)
		args->set = JULIA;
	else
		return (close_mlx(NULL, ER_BAD_SET));
	if (args->set == JULIA && args->argc == 4)
	{
		error = get_julia_params(args);
		if (error)
			return (close_mlx(NULL, ER_BAD_JPRMS));
	}
	else if (args->set == JULIA && args->argc == 2)
	{
		args->j_params.real = cRe;
		args->j_params.imag = cIm;
	}
	return (SUCCESS);
}

int	close_mlx(t_mlx *mlx, int error)
{
	if (mlx && mlx->mlx_ptr)
	{
		if (mlx->win_ptr)
			mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		if (mlx->img.img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		mlx->mlx_ptr = NULL;
	}
	if (error)
		print_ret_err(error);
	exit(error);
	return (SUCCESS);
}

int	start_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return (close_mlx(mlx, ER_MLX_INIT));
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, RES_X, RES_Y, "fractol");
	if (mlx->win_ptr == NULL)
		return (close_mlx(mlx, ER_WIN_CREA));
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, RES_X, RES_Y); 
	if (mlx->img.img_ptr == NULL)
		return (close_mlx(mlx, ER_IMG_CREA));
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,
		&mlx->img.l_len, &mlx->img.endian);
	return (SUCCESS);
}
