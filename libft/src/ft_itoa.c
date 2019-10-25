/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 00:00:04 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/16 12:59:11 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_counter(unsigned int y)
{
	int x;

	x = 0;
	while (y > 9)
	{
		y = y / 10;
		x++;
	}
	return (x);
}

char			*ft_itoa(int nb)
{
	char			*tab;
	int				x;
	unsigned int	y;
	int				sign;

	sign = 0;
	if (nb < 0)
	{
		nb *= -1;
		sign++;
	}
	x = ft_counter((unsigned int)nb);
	if (!(tab = ft_strnew(x + 1 + sign)))
		return (NULL);
	if (sign == 1)
		tab[0] = '-';
	y = nb;
	while (x >= 0)
	{
		tab[x-- + sign] = (y % 10 + '0');
		y = y / 10;
	}
	return (tab);
}
