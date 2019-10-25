/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 11:54:53 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/18 22:56:58 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int i;
	unsigned int j;

	j = 0;
	if (!s || !f)
		return ;
	i = ft_strlen(s);
	while (j < i)
	{
		f(j, &s[j]);
		j++;
	}
}
