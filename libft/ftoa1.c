/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <axaidan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:50:02 by axaidan           #+#    #+#             */
/*   Updated: 2020/12/03 15:52:18 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		count_int_p(double d, int neg)
{
	int			chars;
	long long	temp;

	temp = (long long)d;
	chars = 0;
	if (temp == 0)
		chars++;
	if (neg)
		chars++;
	while (temp)
	{
		temp /= 10;
		chars++;
	}
	return (chars);
}

static void		make_i_str(char **str, long long n, int neg)
{
	if (neg)
	{
		n = -n;
		*((*str)++) = '-';
		neg = 0;
	}
	if (n < 10)
		*((*str)++) = n + '0';
	if (n >= 10)
	{
		make_i_str(str, n / 10, neg);
		*((*str)++) = n % 10 + '0';
	}
}

static char		*make_f_str(long double d, int afterpoint)
{
	char		*s;
	int			len;
	int			i;

	if (d < 0)
		d = -d;
	d = d - (long long)d;
	len = (afterpoint == 0) ? afterpoint : afterpoint + 1;
	if (!(s = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (i == 0)
			s[i++] = '.';
		else
		{
			d = (d - (long long)d) * 10;
			s[i++] = ((long long)d) % 10 + '0';
		}
	}
	s[i] = '\0';
	return (s);
}

static char		*make_dbl_str(double d, int afterpoint, int neg)
{
	char	*s_i;
	char	*s_f;
	char	*str;
	int		int_len;

	int_len = count_int_p(d, neg);
	if (!(s_i = malloc(sizeof(char) * (int_len + 1))))
		return (NULL);
	str = s_i;
	make_i_str(&s_i, (long long)d, neg);
	str[int_len] = '\0';
	if (!(s_f = make_f_str((long double)d, afterpoint)))
	{
		free(str);
		return (NULL);
	}
	s_i = str;
	str = ft_strjoin(s_i, s_f);
	free(s_i);
	free(s_f);
	if (!str)
		return (NULL);
	return (str);
}

char			*ftoa(double d, int afterpoint)
{
	char	*str;
	int		neg;

	if (afterpoint < 0)
		afterpoint = 6;
	if (d != 0.0)
		neg = (d < 0) ? 1 : 0;
	else
		neg = zero_is_signed((long double)d);
	if (afterpoint == 0)
		d = roundup_p_zero(d);
	if (!(str = make_dbl_str(d, afterpoint, neg)))
		return (NULL);
	if (afterpoint != 0 && get_relevant((long double)d, afterpoint))
		roundup_str(&str, ft_strlen(str) - 1);
	return (str);
}
