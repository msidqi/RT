/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:28:37 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/12 12:08:17 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	int				i;
	unsigned char	*tab;

	tab = (unsigned char *)s;
	i = 0;
	if (n == 0)
		return ;
	else
	{
		while ((unsigned long)i < n)
		{
			tab[i] = '\0';
			i++;
		}
	}
}
