/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 22:02:57 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/18 22:54:37 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		ft_islower(int c)
{
	if (c <= 'z' && c >= 'a')
		return (1);
	else
		return (0);
}

static int		ft_isupper(int c)
{
	if (c <= 'Z' && c >= 'A')
		return (1);
	else
		return (0);
}

int				ft_isalpha(int c)
{
	if (ft_islower(c))
		return (1);
	else if (ft_isupper(c))
		return (1);
	else
		return (0);
}
