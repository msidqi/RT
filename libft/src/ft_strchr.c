/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 15:49:33 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/12 16:33:26 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*tab;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			tab = (char *)(s + i);
			return (tab);
		}
		i++;
	}
	if (c == 0)
	{
		tab = (char *)(s + i);
		return (tab);
	}
	else
		return (NULL);
}
