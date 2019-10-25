/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 11:59:14 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/16 00:33:27 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	int		j;
	char	*tab;

	j = 0;
	tab = "";
	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (!(tab = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (j < i)
	{
		tab[j] = f(s[j]);
		j++;
	}
	tab[j] = '\0';
	return (tab);
}
