/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <axaidan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:05:02 by axaidan           #+#    #+#             */
/*   Updated: 2020/11/30 19:18:00 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_double(t_conv conv, va_list args)
{
	int		dbl_len;
	int		j;
	int		i;

	conv.d = va_arg(args, double);
	if (!(conv.sub = ftoa(conv.d, conv.preci)))
		return (-1);
	if (conv.f_zero_f)
		if (!(conv.sub = zero_pad_int(conv)))
			return (-1);
	dbl_len = (int)ft_strlen(conv.sub);
	j = 0;
	if (!(conv.f_minus) && !(conv.f_zero_f))
		while (j < conv.width - dbl_len)
			j += putchar_ret(' ');
	i = 0;
	while (conv.sub[i])
		ft_putchar_fd(conv.sub[i++], 1);
	if (conv.f_minus && !(conv.f_zero_f))
		while (i + j < conv.width)
			j += putchar_ret(' ');
	free(conv.sub);
	return (i + j);
}
