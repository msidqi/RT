/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 16:34:24 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/12 17:15:15 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*tab;

	i = 0;
	while (s[i])
		i++;
	if (c == 0)
	{
		tab = (char *)(s + i);
		return (tab);
	}
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			tab = (char *)(s + i);
			return (tab);
		}
		i--;
	}
	return (NULL);
}
