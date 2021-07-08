/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axaidan <axaidan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:45:17 by axaidan           #+#    #+#             */
/*   Updated: 2021/07/08 15:55:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*alloc;

	alloc = malloc(size * nmemb);
	if (alloc == NULL)
		return (NULL);
	ft_bzero(alloc, size * nmemb);
	return (alloc);
}
