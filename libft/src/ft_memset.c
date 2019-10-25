/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 19:51:49 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/10 12:44:25 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int				i;
	unsigned char	*tab;

	tab = (unsigned char *)b;
	i = 0;
	while ((unsigned long)i < len)
	{
		tab[i] = (unsigned char)c;
		i++;
	}
	return (b = (void *)tab);
}
