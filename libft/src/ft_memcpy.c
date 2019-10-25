/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:34:24 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/12 12:05:49 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*tab1;
	const unsigned char	*tab2;

	i = 0;
	tab1 = (unsigned char *)dst;
	tab2 = (const unsigned char *)src;
	while (i < n)
	{
		tab1[i] = tab2[i];
		i++;
	}
	return (dst);
}
