/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:34:09 by axaidan           #+#    #+#             */
/*   Updated: 2020/12/03 15:47:09 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*precise_int(t_conv conv)
{
	int		i;
	int		neg;
	int		dgts;
	char	*temp;

	dgts = (conv.sub[0] == '-') ? ft_strlen(conv.sub) - 1 : ft_strlen(conv.sub);
	neg = (conv.sub[0] == '-') ? 1 : 0;
	if (conv.preci < 0 || dgts >= conv.preci)
		return (conv.sub);
	if (!(temp = malloc(sizeof(char) * (neg + conv.preci + 1))))
	{
		free(conv.sub);
		return (NULL);
	}
	i = 0;
	if (neg)
		temp[i++] = '-';
	while (dgts++ < conv.preci)
		temp[i++] = '0';
	while (conv.sub[neg])
		temp[i++] = conv.sub[neg++];
	temp[i] = '\0';
	free(conv.sub);
	conv.sub = temp;
	return (conv.sub);
}

char		*zero_pad_int(t_conv conv)
{
	int		i;
	int		neg;
	int		base_len;
	char	*temp;

	base_len = ft_strlen(conv.sub);
	neg = (conv.sub[0] == '-') ? 1 : 0;
	if (base_len >= conv.width)
		return (conv.sub);
	if (!(temp = malloc(sizeof(char) * (conv.width + 1))))
	{
		free(conv.sub);
		return (NULL);
	}
	i = 0;
	if (conv.sub[i] == '-')
		temp[i++] = '-';
	while (base_len++ < conv.width)
		temp[i++] = '0';
	while (conv.sub[neg])
		temp[i++] = conv.sub[neg++];
	temp[i] = 0;
	free(conv.sub);
	conv.sub = temp;
	return (conv.sub);
}

int			print_int(t_conv conv, va_list args)
{
	int		int_len;
	int		j;
	int		i;

	conv.i = va_arg(args, int);
	conv.sub = (!conv.i && !conv.preci) ? ft_strdup("") : ft_itoa(conv.i);
	if (!conv.sub)
		return (-1);
	if (!(conv.sub = (conv.f_zero) ? zero_pad_int(conv) : precise_int(conv)))
		return (-1);
	int_len = (int)ft_strlen(conv.sub);
	int_len = (int_len < conv.preci) ? conv.preci : int_len;
	j = 0;
	if (!(conv.f_minus) && !(conv.f_zero))
		while (j < conv.width - int_len)
			j += putchar_ret(' ');
	i = 0;
	while (conv.sub[i])
		ft_putchar_fd(conv.sub[i++], 1);
	if (conv.f_minus && !(conv.f_zero))
		while (i + j < conv.width)
			j += putchar_ret(' ');
	if (conv.sub)
		free(conv.sub);
	return (i + j);
}

int			print_unsigned_int(t_conv conv, va_list args)
{
	int		int_len;
	int		j;
	int		i;

	conv.u = va_arg(args, unsigned int);
	if (!(conv.sub = (!conv.u && !conv.preci) ? ft_strdup("") : utoa(conv.u)))
		return (-1);
	if (!(conv.sub = (conv.f_zero) ? zero_pad_int(conv) : precise_int(conv)))
		return (-1);
	int_len = (int)ft_strlen(conv.sub);
	int_len = (int_len < conv.preci) ? conv.preci : int_len;
	j = 0;
	if (!(conv.f_minus) && !(conv.f_zero))
		while (j < conv.width - int_len)
			j += putchar_ret(' ');
	i = 0;
	while (conv.sub[i])
		ft_putchar_fd(conv.sub[i++], 1);
	if (conv.f_minus && !(conv.f_zero))
		while (i + j < conv.width)
			j += putchar_ret(' ');
	if (conv.sub)
		free(conv.sub);
	return (i + j);
}
