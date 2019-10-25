/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 12:14:31 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/16 00:34:32 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	j;
	char			*tab;

	j = 0;
	tab = "";
	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (!(tab = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (j < i)
	{
		tab[j] = f(j, s[j]);
		j++;
	}
	tab[j] = '\0';
	return (tab);
}
