/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 22:10:42 by msidqi            #+#    #+#             */
/*   Updated: 2018/08/01 16:55:06 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int k;

	if (power == 0)
		return (1);
	if (power < 0)
		return (0);
	else
	{
		k = nb;
		while (power > 1)
		{
			nb = k * nb;
			power--;
		}
		return (nb);
	}
}
