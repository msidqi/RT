/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 16:01:26 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/16 00:33:48 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;

	tab = "";
	if (!s1 || !s2)
		return (NULL);
	if (!(tab = (char *)malloc(sizeof(char)
					* (ft_strlen(s1) + ft_strlen(s2)) + 1)))
		return (NULL);
	else
	{
		ft_strcpy(tab, s1);
		ft_strcat(tab, s2);
	}
	return (tab);
}
