/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:39:02 by axaidan           #+#    #+#             */
/*   Updated: 2020/12/02 17:38:48 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_conv	parse_flags(t_conv conv, const char **fmt)
{
	while ((**fmt == '-') || (**fmt == '0'))
	{
		if (**fmt == '-')
		{
			conv.f_minus = 1;
			conv.f_zero_f = 0;
			conv.f_zero = 0;
		}
		if (**fmt == '0' && !(conv.f_minus))
		{
			conv.f_zero = 1;
			conv.f_zero_f = 1;
		}
		(*fmt)++;
	}
	return (conv);
}

t_conv	parse_preci(t_conv conv, const char **fmt, va_list args)
{
	if (**fmt == '.')
	{
		conv.preci = 0;
		conv.f_zero = 0;
		(*fmt)++;
	}
	if (**fmt == '*')
	{
		conv.preci = va_arg(args, int);
		if (conv.preci < 0)
		{
			conv.preci = -1;
			if (!conv.f_minus)
				conv.f_zero = conv.f_zero_f;
			else
				conv.f_zero = 0;
		}
		(*fmt)++;
	}
	else
		while (ft_isdigit(**fmt))
			conv.preci = conv.preci * 10 + *((*fmt)++) - '0';
	return (conv);
}

t_conv	parse_width(t_conv conv, const char **fmt, va_list args)
{
	if (**fmt == '*')
	{
		conv.width = va_arg(args, int);
		if (conv.width < 0)
		{
			conv.f_minus = 1;
			conv.f_zero = 0;
			conv.f_zero_f = 0;
			conv.width = -conv.width;
		}
		(*fmt)++;
	}
	else
		while (ft_isdigit(**fmt))
			conv.width = conv.width * 10 + *((*fmt)++) - '0';
	return (conv);
}

int		convert(const char **fmt, va_list args)
{
	t_conv	conv;
	int		printed;

	printed = 0;
	conv = init_struct();
	conv = parse_flags(conv, fmt);
	conv = parse_preci(parse_width(conv, fmt, args), fmt, args);
	if (**fmt == 'c' || **fmt == '%')
		printed = print_char(conv, args, **fmt);
	else if (**fmt == 's')
		printed = print_str(conv, args);
	else if (**fmt == 'd' || **fmt == 'i')
		printed = print_int(conv, args);
	else if (**fmt == 'u')
		printed = print_unsigned_int(conv, args);
	else if (**fmt == 'x' || **fmt == 'X')
		printed = print_hexa(conv, args, **fmt);
	else if (**fmt == 'p')
		printed = print_addr(conv, args);
	else if (**fmt == 'f')
		printed = print_double(conv, args);
	else
		return (-1);
	return (printed);
}

int		ft_printf(const char *fmt, ...)
{
	va_list		args;
	int			printed;
	int			ret;

	va_start(args, fmt);
	printed = 0;
	while (*fmt)
	{
		if (*fmt != '%')
			printed += putchar_ret(*fmt);
		else
		{
			fmt++;
			if ((ret = convert(&fmt, args)) < 0)
			{
				va_end(args);
				return (-1);
			}
			printed += ret;
		}
		fmt++;
	}
	va_end(args);
	return (printed);
}
