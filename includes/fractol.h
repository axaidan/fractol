#ifndef FRACTOL_H
# define FRACTOL_H

/*	STANDARD LIBS */
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <math.h>
# include <fcntl.h>
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
void	init_args_struct(t_args *args, int argc, char **argv);
void	init_mlx_struct(t_mlx *mlx);
void	init_variables(t_mlx *mlx);
void	init_start_bounds_pts(int key, t_pt *pix, t_pt *bounds);

/*	system.c */
int		start_mlx(t_mlx *mlx);
int		close_mlx(t_mlx *mlx, int error);
int		check_args(t_args *args);

/*	errors.c */
int		print_ret_err(int error);

/*	fractol.c */
int		julia(t_cpx c0, int max, t_cpx params, int (*render)(int, t_cpx, int));
int		mandelbrot(t_cpx scaled, int max, int (*render)(int, t_cpx, int));
int		fractol(t_mlx *mlx);
void	draw_fractal(t_mlx *mlx);

/*	utils_mlx.c */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	change_pixel(t_img *img, int x, int y, int (*render)(int, t_cpx, int));
int		change_color_by(int color, int val);

/*	hooks.c */
int		mouse_used(int button, int x, int y, t_mlx *mlx);
int		key_pressed(int key, t_mlx *mlx);
int		shift_colors(t_mlx *mlx);
void	change_render_method(t_mlx *mlx);

/*	display.c */
void	display_controls(void);
void	display_info(t_mlx *mlx);
void	display_render_progress(t_pt pix);
void	display_handler(t_mlx *mlx, int key);

/*	render.c */
int		continuous_pixel_scaling(int ite, t_cpx c2, int set);
int		simple_ite(int ite, t_cpx c, int set);
int		square_ite(int ite, t_cpx c, int set);
int		cube_ite(int ite, t_cpx c, int set);
int		black_and_white(int ite, t_cpx c, int set);

/*	move.c */
void	move_fractal(t_mlx *mlx, int key);

/*	bmp.c */
int		make_bmp(t_mlx *mlx);

#endif
