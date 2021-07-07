#include "fractol.h"

void	display_info(t_mlx *mlx)
{
	printf("maximum iterations\t= %d\n", mlx->max_ite);
}

void	display_render_progress(t_pt pix)
{
	if (pix.y == 0 && pix.x == 0)
		ft_putstr_fd("Processing........", STDOUT_FILENO);
	else if (pix.y == RES_Y / 2 && pix.x == 0)
		ft_putstr_fd("Please wait.........", STDOUT_FILENO);
	else if (pix.y == RES_Y - 1 && pix.x == RES_X - 1)
		ft_putstr_fd("\a DONE !\n", STDOUT_FILENO);
}
