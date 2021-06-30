#ifndef FRACTOL_H
# define FRACTOL_H

/*	STANDARD LIBS */
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <math.h>
# include <string.h>
# include <errno.h>

/*	MLX RELATED LIBS */
# include <mlx.h>
# include <X11/X.h>

/*	PROJECT HEADERS */
# include "libft.h"
# include "structures.h"
# include "defines.h"
# include "errors.h"

/*	initializations.c */
void	init_mlx_struct(t_mlx *mlx);

/*	system.c */
int		start_mlx(t_mlx *mlx);
int		close_mlx(t_mlx *mlx, int error);

/*	errors.c */
int		print_ret_err(int error);

/*	fractol.c */
int		fractol(t_mlx *mlx);
void	draw_fractal(t_mlx *mlx, double bnd_x, double bnd_y);

/*	utils_mlx.c */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif
