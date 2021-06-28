/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <axaidan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:07:37 by axaidan           #+#    #+#             */
/*   Updated: 2020/12/03 15:48:10 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*precise_str(t_conv conv)
{
	int	i;
	int	len;

	len = ft_strlen(conv.str);
	len = (conv.preci < len) ? conv.preci : len;
	if (!(conv.sub = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		conv.sub[i] = conv.str[i];
		i++;
	}
	conv.sub[i] = '\0';
	return (conv.sub);
}

int			print_str(t_conv conv, va_list args)
{
	int		len;
	int		printed;

	conv.str = va_arg(args, char *);
	if (!(conv.str))
		conv.str = "(null)";
	conv.sub = (conv.preci >= 0) ? precise_str(conv) : ft_strdup(conv.str);
	if (!conv.sub)
		return (-1);
	len = (int)ft_strlen(conv.sub);
	printed = 0;
	if (!(conv.f_minus))
		while (printed < conv.width - len)
			printed += (conv.f_zero) ? putchar_ret('0') : putchar_ret(' ');
	printed += putstr_ret(conv.sub);
	if (conv.f_minus)
		while (printed < conv.width)
			printed += putchar_ret(' ');
	free(conv.sub);
	return (printed);
}
