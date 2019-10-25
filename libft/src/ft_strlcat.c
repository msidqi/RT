/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 22:57:15 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/16 23:00:49 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t dlen;
	size_t i;
	size_t rdlen;

	rdlen = 0;
	dlen = ft_strlen(dst);
	if (size > dlen)
		rdlen = size - dlen - 1;
	i = 0;
	while (i < rdlen && src[i])
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	if (size > dlen)
		return (dlen + ft_strlen(src));
	else
		return (size + ft_strlen(src));
}
