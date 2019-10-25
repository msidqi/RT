/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 17:38:12 by msidqi            #+#    #+#             */
/*   Updated: 2019/02/03 09:00:03 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_strjoinndel(char *s1, char c)
{
	int		i;
	char	*tab;
	int		len;
	int		j;

	j = 0;
	i = 1;
	len = 1 + ft_strlen(s1);
	if (!(tab = (char *)malloc(sizeof(char) * len + 1)))
		return (0);
	tab[len] = '\0';
	tab[0] = c;
	while (s1[j])
	{
		tab[i] = s1[j];
		i++;
		j++;
	}
	free(s1);
	return (tab);
}

static void		ft_rev(int *a, int *value)
{
	*a = 1;
	*value = *value * (-1);
}

char			*ft_itoa_base(int value, int base)
{
	char	*tab;
	char	c;
	int		a;

	a = 0;
	if (value == INT_MIN && base == 10)
		return ("-2147483648");
	if (value == 0)
		return ("0");
	value = ((base != 10 && value < 0) ? (-value) : value);
	if (base == 10 && value < 0)
		ft_rev(&a, &value);
	tab = ft_strnew(1);
	while (value > 0)
	{
		if (value % base >= 10)
			c = '0' + value % base + 7;
		else
			c = '0' + value % base;
		value = value / base;
		tab = ft_strjoinndel(tab, c);
	}
	tab = (a == 1 ? ft_strjoinndel(tab, '-') : tab);
	return (tab);
}
