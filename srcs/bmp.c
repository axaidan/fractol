#include "fractol.h"

int	write_bmp_header(t_mlx *mlx, int fd)
{
	(void)mlx;
	unsigned char	bmp_header[14];
	unsigned int	file_size;
	int				error;

	ft_memset(bmp_header, 0, 14);
	bmp_header[0] = 'B';
	bmp_header[1] = 'M';
	file_size = 54 + (4 * RES_X * RES_Y);
	bmp_header[2] = (unsigned char)(file_size);
	bmp_header[3] = (unsigned char)(file_size >> 8);
	bmp_header[4] = (unsigned char)(file_size >> 16);
	bmp_header[5] = (unsigned char)(file_size >> 24);
	bmp_header[10] = (unsigned char)54;
	error = write(fd, bmp_header, 14) < 0;
	if (error)
	{
		close(fd);
		return (ER_BMP_HDR);
	}
	return (0);
}

int	write_dib_header(t_mlx *mlx, int fd)
{
	(void)mlx;
	unsigned char	dib_header[40];
	int				error;

	ft_memset(dib_header, 0, 40);
	dib_header[0] = 40;
	dib_header[4] = (unsigned char)(RES_X);
	dib_header[5] = (unsigned char)(RES_X >> 8);
	dib_header[6] = (unsigned char)(RES_X >> 16);
	dib_header[7] = (unsigned char)(RES_X >> 24);
	dib_header[8] = (unsigned char)(RES_Y);
	dib_header[9] = (unsigned char)(RES_Y >> 8);
	dib_header[10] = (unsigned char)(RES_Y >> 16);
	dib_header[11] = (unsigned char)(RES_Y >> 24);
	dib_header[12] = 1;
	dib_header[13] = 0;
	dib_header[14] = 32;
	dib_header[15] = 0;
	error = write(fd, dib_header, 40) < 0;
	if (error)
	{
		close(fd);
		return (ER_DIB_HDR);
	}
	return (0);
}

int	write_pix_array(t_mlx *mlx, int fd)
{
	unsigned char	*uint_addr;
	unsigned char	*last_line;
	unsigned int	line_length;
	int				error;

	uint_addr = (unsigned char*)(mlx->img.addr);
	line_length = mlx->img.l_len;
	last_line = uint_addr + (line_length * (RES_Y - 1));
	while (last_line >= uint_addr)
	{
		error = write(fd, last_line, line_length) < 0;
		if (error)
		{
			close(fd);
			return (ER_PIX_ARR);
		}
		last_line -= line_length;
	}
	return (0);
}

static char	*concat_file_name(int i)
{
	char	*file_num;
	char	*file_name;
	char	*ext;

	file_num = ft_itoa(i);
	if (file_num == NULL)
		return (NULL);
	file_name = "screenshot_";
	file_name = ft_strjoin(file_name, file_num);
	free(file_num);
	if (file_name == NULL)
		return (NULL);
	ext = ".bmp";
	ext = ft_strjoin(file_name, ext);
	free(file_name);
	if (ext == NULL)
		return (NULL);
	return (ext);
}

int	make_bmp(t_mlx *mlx)
{
	static int	i = 0;
	int			fd;
	int			error;
	char		*path;

	i++;
	error = -1;
	path = concat_file_name(i);
	if (path == NULL)
		return (ER_PATH_CONCAT);
	fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0666);
	free(path);
	if (fd < 0)
		return (ER_BMP_OPEN);
	error = write_bmp_header(mlx, fd);
	if (error)
		return (error);
	error = write_dib_header(mlx, fd);
	if (error)
		return (error);
	error = write_pix_array(mlx, fd);
	if (error)
		return (error);
	close(fd);
	return (0);
}
