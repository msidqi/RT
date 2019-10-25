/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 08:06:23 by kdaou             #+#    #+#             */
/*   Updated: 2019/07/16 17:22:23 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

size_t	ft_table_size(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		ft_is_limited(double n)
{
	if (n < 0 || n > 1)
		return (0);
	return (1);
}

int		ft_is_numeric(char *str)
{
	int	float_point;
	int	i;

	i = 0;
	float_point = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
			float_point++;
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (float_point > 1 ? 0 : 1);
}

int		ft_bracket_control(char *str, char c)
{
	if (!str)
		return (0);
	if (str[0] != c || ft_strlen(str) != 1)
		return (0);
	return (1);
}

void	ft_cheak_data(t_data *data)
{
	if (!data->scene)
		ft_error_management(data, 9, NULL, -1);
	if (data->cam.n != 1)
		ft_error_management(data, 7, NULL, -1);
}
