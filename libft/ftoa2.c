/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <axaidan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:48:00 by axaidan           #+#    #+#             */
/*   Updated: 2020/12/02 19:23:09 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_relevant(long double d, int afterpoint)
{
	long double		f_p;
	int				i;
	long double		relevant;

	d = (d < 0) ? -d : d;
	f_p = d;
	i = 0;
	while (i < afterpoint + 1)
	{
		f_p = f_p - (long long)f_p;
		if (i == afterpoint)
			relevant = f_p;
		else
			f_p *= 10;
		i++;
	}
	relevant = relevant - (long long)relevant;
	if (relevant >= 0.5)
		return (1);
	else
		return (0);
}

char	*shift_str(char **str)
{
	int		neg;
	char	*temp;
	char	*buf;

	temp = *str;
	neg = ((*str)[0] == '-') ? 1 : 0;
	buf = (neg) ? "-1" : "1";
	temp = ft_strjoin(buf, (*str) + neg);
	free(*str);
	if (!temp)
		return (NULL);
	*str = temp;
	return (*str);
}

char	*roundup_str(char **str, int i)
{
	if ((*str)[i] >= '0' && (*str)[i] <= '8')
		(*str)[i]++;
	else if ((*str)[i] == '9')
	{
		(*str)[i] = '0';
		roundup_str(str, i - 1);
	}
	else if ((*str)[i] == '.')
		roundup_str(str, i - 1);
	else if ((*str)[i] == '-' || i == -1)
		if (!(shift_str(str)))
			return (NULL);
	return (*str - i);
}

double	roundup_p_zero(double d)
{
	int		sign;
	double	f_p;

	sign = (d < 0) ? -1 : 1;
	d = (d < 0) ? -d : d;
	f_p = d - (long long)d;
	if (f_p == 0.5)
		d = ((long long)d % 2 == 0) ? (long long)d : (long long)d + 1;
	else if (f_p > 0.5)
		d = (long long)d + 1;
	return (((double)d) * sign);
}

int		zero_is_signed(long double lf)
{
	return ((1.0 / lf) != (1.0 / ((lf < 0) ? 1 : 0)));
}
