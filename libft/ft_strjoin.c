/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <axaidan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:43:48 by axaidan           #+#    #+#             */
/*   Updated: 2021/07/08 15:57:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*cat;

	if (!s1 || !s2)
		return (NULL);
	cat = malloc(sizeof(char) * (len(s1) + len(s2) + 1));
	if (cat == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		cat[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		cat[i + j] = s2[j];
		j++;
	}
	cat[i + j] = '\0';
	return (cat);
}
