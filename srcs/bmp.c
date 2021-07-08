/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <axaidan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:12:15 by axaidan           #+#    #+#             */
/*   Updated: 2021/07/08 11:05:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

int	write_bmp_header(t_config *c, int fd)
{
	unsigned char	bmp_header[14];
	unsigned int	file_size;
	int				error;

	ft_memset(bmp_header, 0, 14);
	bmp_header[0] = 'B';
	bmp_header[1] = 'M';
	file_size = 54 + (4 * c->r_length * c->r_height);
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

int	write_dib_header(t_config *c, int fd)
{
	unsigned char	dib_header[40];
	int				error;

	ft_memset(dib_header, 0, 40);
	dib_header[0] = 40;
	dib_header[4] = (unsigned char)(c->r_length);
	dib_header[5] = (unsigned char)(c->r_length >> 8);
	dib_header[6] = (unsigned char)(c->r_length >> 16);
	dib_header[7] = (unsigned char)(c->r_length >> 24);
	dib_header[8] = (unsigned char)(c->r_height);
	dib_header[9] = (unsigned char)(c->r_height >> 8);
	dib_header[10] = (unsigned char)(c->r_height >> 16);
	dib_header[11] = (unsigned char)(c->r_height >> 24);
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

int	write_pix_array(t_config *c, int fd)
{
	unsigned char	*uint_addr;
	unsigned char	*last_line;
	unsigned int	line_length;
	int				error;

	uint_addr = (unsigned char*)(c->img_game.addr);
	line_length = c->img_game.line_len;
	last_line = uint_addr + (line_length * (c->r_height));
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

int	concat_file_name(int i, char *file, char *ext)
{
	char	*file_num;
	char	*file_name;
	char	*ext;


}

int	make_bmp(t_config *c)
{
	static int	i = 0;
	int		fd;
	int		error;
	char	*path;

	i++;
	file_num = ft_itoa(i);
	file_name = "screenshot_";
	ext = ".bmp"
	error = -1;
	fd = open("screenshot.bmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return (ER_BMP_OPEN);
	error = write_bmp_header(c, fd);
	if (error)
		return (error);
	error = write_dib_header(c, fd);
	if (error)
		return (error);
	error = write_pix_array(c, fd);
	if (error)
		return (error);
	close(fd);
	return (0);
}
