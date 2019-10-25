/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:19:41 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/19 01:48:22 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	int		e;
	int		r;

	e = len;
	i = 0;
	if (to_find[i] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && e > 0)
	{
		if (str[i] == to_find[0])
		{
			r = e;
			j = 0;
			while (str[i + j] == to_find[j] && to_find[j] != '\0' && r-- > 0)
				j++;
			if (to_find[j] == '\0')
				return ((char *)(str + i));
		}
		i++;
		e--;
	}
	return (NULL);
}
