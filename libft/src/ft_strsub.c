/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:20:26 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/16 00:29:36 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*tab;
	size_t	i;

	i = 0;
	tab = "";
	if (!s)
		return (NULL);
	if (!(tab = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	else
	{
		while (len > 0)
		{
			tab[i] = s[start];
			i++;
			start++;
			len--;
		}
		tab[i] = '\0';
		return (tab);
	}
}
