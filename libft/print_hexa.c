/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 16:15:03 by axaidan           #+#    #+#             */
/*   Updated: 2020/12/03 15:45:38 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*precise_hex(t_conv conv)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	len = ft_strlen(conv.sub);
	if (conv.preci < 0 || len >= conv.preci)
		return (conv.sub);
	if (!(temp = malloc(sizeof(char) * (conv.preci + 1))))
	{
		free(conv.sub);
		return (NULL);
	}
	i = 0;
	while (len++ < conv.preci)
		temp[i++] = '0';
	j = 0;
	while (conv.sub[j])
		temp[i++] = conv.sub[j++];
	temp[i] = '\0';
	free(conv.sub);
	return (temp);
}

static char		*zero_pad_hex(t_conv conv)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	len = ft_strlen(conv.sub);
	if (len >= conv.width)
		return (conv.sub);
	if (!(temp = malloc(sizeof(char) * (conv.width + 1))))
	{
		free(conv.sub);
		return (NULL);
	}
	i = 0;
	while (len++ < conv.width)
		temp[i++] = '0';
	j = 0;
	while (conv.sub[j])
		temp[i++] = conv.sub[j++];
	temp[i] = '\0';
	free(conv.sub);
	return (temp);
}

int				print_hexa(t_conv conv, va_list args, char c)
{
	int	hex_len;
	int	i;
	int	j;

	conv.u = va_arg(args, unsigned int);
	conv.sub = (!conv.u && !conv.preci) ? ft_strdup("") : utox(conv.u, c);
	if (!conv.sub)
		return (-1);
	if (!(conv.sub = (conv.f_zero) ? zero_pad_hex(conv) : precise_hex(conv)))
		return (-1);
	hex_len = (int)ft_strlen(conv.sub);
	hex_len = (hex_len < conv.preci) ? conv.preci : hex_len;
	j = 0;
	if (!(conv.f_minus) && !(conv.f_zero))
		while (j < conv.width - hex_len)
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
