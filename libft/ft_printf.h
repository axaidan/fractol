/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 15:59:11 by axaidan           #+#    #+#             */
/*   Updated: 2020/12/03 15:47:42 by axaidan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_conv
{
	int				i;
	unsigned int	u;
	unsigned char	c;
	char			*str;
	void			*ptr;
	double			d;
	int				width;
	int				preci;
	int				f_zero;
	int				f_zero_f;
	int				f_minus;
	char			*sub;
}				t_conv;

char			*zero_pad_int(t_conv conv);
int				print_int(t_conv conv, va_list args);
char			*utoa(unsigned int n);
int				print_unsigned_int(t_conv conv, va_list args);

int				print_char(t_conv conv, va_list args, char c);

int				print_str(t_conv conv, va_list args);

char			*utox(unsigned int n, char c);
int				print_hexa(t_conv conv, va_list args, char c);

char			*ltox(unsigned long n, char c);
int				print_addr(t_conv conv, va_list args);

t_conv			init_struct(void);
int				putchar_ret(char c);
int				putstr_ret(char *s);
void			ft_putchar_fd(char c, int fd);
int				ft_printf(const char *fmt, ...);

int				ft_isdigit(int c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s);
char			*ft_itoa(int x);
size_t			ft_strlen(const char *s);

int				get_relevant(long double d, int afterpoint);
double			roundup_p_zero(double d);
char			*roundup_str(char **str, int i);
int				zero_is_signed(long double lf);
char			*ftoa(double d, int afterpoint);
int				print_double(t_conv conv, va_list args);

#endif
