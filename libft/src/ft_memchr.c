/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 10:06:31 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/12 12:05:05 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const unsigned char *tab;
	size_t				i;

	tab = (const unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (tab[i] == (const unsigned char)c)
		{
			tab = str + i;
			return ((void *)tab);
		}
		i++;
	}
	return (NULL);
}
