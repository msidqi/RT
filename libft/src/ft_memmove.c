/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 22:13:24 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/15 17:09:40 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*tab1;
	unsigned char	*tab2;

	i = 0;
	tab1 = (unsigned char *)dst;
	tab2 = (unsigned char *)src;
	if (dst > src)
	{
		while (len)
		{
			tab1[len - 1] = tab2[len - 1];
			len--;
		}
		return (dst);
	}
	else
		while (i < len)
		{
			tab1[i] = tab2[i];
			i++;
		}
	return (dst);
}
