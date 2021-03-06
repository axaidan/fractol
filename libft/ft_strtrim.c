/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <axaidan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 19:27:23 by axaidan           #+#    #+#             */
/*   Updated: 2021/07/08 15:50:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(const char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	find_end(char const *s, char const *set, int i)
{
	int	end;

	while (s[i])
	{
		while (!(is_set(s[i], set)) && s[i])
			i++;
		end = i;
		while (is_set(s[i], set) && s[i])
			i++;
	}
	return (end);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*trimmed;

	if (!s || !set)
		return (NULL);
	start = 0;
	while (s[start] && is_set(s[start], set))
		start++;
	if (s[start] == '\0')
		end = start;
	else
		end = find_end(s, set, start);
	trimmed = malloc(sizeof(char) * (end - start + 1));
	if (trimmed == NULL)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		trimmed[i] = s[start + i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
