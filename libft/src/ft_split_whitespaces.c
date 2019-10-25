/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 03:29:15 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/19 03:14:16 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_char(char *s, int i)
{
	int p;

	p = 0;
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	while (!(s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\0'))
	{
		p++;
		i++;
	}
	p++;
	return (p);
}

static int			ft_mrch(char *s)
{
	int c;
	int i;

	c = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && (s[i - 1] >= 33))
			c++;
		i++;
	}
	if ((s[i - 1] == ' ' || s[i - 1] == '\t' || s[i - 1] == '\n'))
		c -= 1;
	c += 1;
	return (c);
}

char				**ft_split_whitespaces(char *str)
{
	char	**tab;
	int		i;
	int		j;
	int		k;
	int		l;

	l = 0;
	i = 0;
	k = 0;
	if (!str || !(tab = (char **)malloc(sizeof(char*) * (ft_mrch(str) + 1))))
		return (NULL);
	while (str[i] != '\0')
	{
		while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		j = 0;
		tab[k] = (char *)malloc(sizeof(char) * (ft_char(str, i)));
		l = ft_char(str, i);
		while (j < l)
			tab[k][j++] = str[i++];
		tab[k++][j] = '\0';
		i++;
	}
	tab[k] = 0;
	return (tab);
}
