/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 20:37:23 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/12 20:26:25 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char			*strdst;
	unsigned const char		*strsrc;
	size_t					i;

	strdst = (unsigned char *)dst;
	strsrc = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		strdst[i] = strsrc[i];
		if (strsrc[i] == (unsigned char)c)
		{
			i++;
			dst = (void *)(strdst + i);
			return (dst);
		}
		i++;
	}
	return (NULL);
}
