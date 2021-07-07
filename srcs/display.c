#include "fractol.h"

void    display_controls(void)
{
	ft_putchar_fd('\n', STDERR_FILENO);
	ft_putendl_fd("h key\t\t: display help", STDERR_FILENO);
    ft_putendl_fd("mouse scroll\t: zoom towards mouse pointer", STDERR_FILENO);
    ft_putendl_fd("arrows\t\t: scroll frame", STDERR_FILENO);
    ft_putendl_fd("m key\t\t: change render mode\ns key\t\t: shift colors",
        STDERR_FILENO);
    ft_putendl_fd("i key\t\t: display maximum iterations", STDERR_FILENO);
    ft_putendl_fd("+ key\t\t: increase maximum iterations, up to 1056",
        STDERR_FILENO);
    ft_putendl_fd("- key\t\t: decrease maximum iterations, down to 8",
        STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	display_info(t_mlx *mlx)
{
	printf("maximum iterations\t= %d\n", mlx->max_ite);
}

void	display_render_progress(t_pt pix)
{
	int	i;	

	if (pix.y == 0 && pix.x == 0)
	{
		ft_putchar_fd('\r', STDOUT_FILENO);
		i = 0;
		while (i++ < 3)
			ft_putstr_fd("               ", STDOUT_FILENO);
		ft_putchar_fd('\r', STDOUT_FILENO);
		ft_putstr_fd("Processing", STDOUT_FILENO);
	}
	else if (pix.y == RES_Y / 2 && pix.x == 0)
		ft_putstr_fd(" Please wait", STDOUT_FILENO);
	else if (pix.y == RES_Y - 1 && pix.x == RES_X - 1)
		ft_putstr_fd("\a DONE !", STDOUT_FILENO);
	else if (pix.y % (RES_Y / 10) == 0 && pix.x == 0)
	   	ft_putstr_fd(" .", STDOUT_FILENO);
}
