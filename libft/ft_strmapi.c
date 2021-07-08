/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 18:30:09 by axaidan           #+#    #+#             */
/*   Updated: 2021/07/08 15:58:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mapped;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	mapped = malloc(sizeof(char) * (i + 1));
	if (mapped == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		mapped[i] = (*f)(i, s[i]);
		i++;
	}
	mapped[i] = '\0';
	return (mapped);
}
