/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 11:32:35 by msidqi            #+#    #+#             */
/*   Updated: 2019/02/14 11:34:47 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(int nb)
{
	int odd;
	int result;

	odd = 1;
	result = 0;
	while (nb > 1)
	{
		nb = nb - odd;
		odd = odd + 2;
		result++;
	}
	if (nb == 0)
		return (result);
	return (result);
}
