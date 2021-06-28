/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltox.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <axaidan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:02:06 by axaidan           #+#    #+#             */
/*   Updated: 2020/12/03 15:44:55 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		count_chars(unsigned long n)
{
	int	chars;

	if (n == 0)
		return (1);
	chars = 0;
	while (n)
	{
		n /= 16;
		chars++;
	}
	return (chars);
}

static void		make_str(char *str, unsigned long n, int *i, char *base)
{
	if (n >= 16)
	{
		make_str(str, n / 16, i, base);
		str[(*i)++] = base[n % 16];
	}
	if (n < 16)
		str[(*i)++] = base[n];
}

char			*ltox(unsigned long n, char c)
{
	char			*str;
	int				chars;
	int				i;
	char			*base_hexa;

	base_hexa = (c == 'x') ? "0123456789abcdef" : "0123456789ABCDEF";
	chars = count_chars(n);
	if (!(str = malloc(sizeof(char) * (chars + 1))))
		return (NULL);
	i = 0;
	make_str(str, n, &i, base_hexa);
	str[chars] = '\0';
	return (str);
}
