/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_addr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:36:27 by axaidan           #+#    #+#             */
/*   Updated: 2020/12/03 15:45:10 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*precise_addr(t_conv conv)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	len = ft_strlen(conv.sub);
	if (!conv.preci || conv.preci < 0 || len >= conv.preci)
		return (conv.sub);
	if (!(temp = malloc(sizeof(char) * (conv.preci + 1))))
		return (NULL);
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

static char	*make_addr_str(t_conv conv, va_list args)
{
	char			*temp;
	unsigned long	addr;

	addr = (unsigned long)va_arg(args, void *);
	if (!(conv.sub = ltox(addr, 'x')))
		return (NULL);
	if (!conv.preci && !addr)
		*(conv.sub) = '\0';
	temp = conv.sub;
	if (!(conv.sub = precise_addr(conv)))
	{
		free(temp);
		return (NULL);
	}
	temp = conv.sub;
	if (!(conv.sub = ft_strjoin("0x", conv.sub)))
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (conv.sub);
}

int			print_addr(t_conv conv, va_list args)
{
	int		len;
	int		i;
	int		j;

	if (!(conv.sub = make_addr_str(conv, args)))
		return (-1);
	len = (int)ft_strlen(conv.sub);
	j = 0;
	if (!(conv.f_minus))
		while (j < conv.width - len)
			j += putchar_ret(' ');
	i = putstr_ret(conv.sub);
	if (conv.f_minus)
		while (i + j < conv.width)
			j += putchar_ret(' ');
	free(conv.sub);
	return (i + j);
}
