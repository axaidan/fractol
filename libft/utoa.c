/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <axaidan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:33:48 by axaidan           #+#    #+#             */
/*   Updated: 2020/12/03 15:48:21 by axaidan          ###   ########.fr       */
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
		n /= 10;
		chars++;
	}
	return (chars);
}

static void		make_str(char *str, unsigned long n, int *i)
{
	if (n >= 10)
	{
		make_str(str, n / 10, i);
		str[(*i)++] = n % 10 + '0';
	}
	if (n < 10)
		str[(*i)++] = n + '0';
}

char			*utoa(unsigned int x)
{
	unsigned long	n;
	char			*str;
	int				chars;
	int				i;

	n = x;
	chars = count_chars(n);
	if (!(str = malloc(sizeof(char) * (chars + 1))))
		return (NULL);
	i = 0;
	make_str(str, n, &i);
	str[chars] = '\0';
	return (str);
}
