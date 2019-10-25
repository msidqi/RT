/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:56:32 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/12 18:00:58 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t		i;
	const char	*tab;

	i = 0;
	tab = src;
	while (src[i])
	{
		if (src[i] != '\0')
			dst[i] = tab[i];
		else
			break ;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
