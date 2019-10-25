/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expect_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 09:21:02 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/05 20:59:18 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int	ft_get_matrix(char *line, int i, t_vec4 *vec, double (*new)[4])
{
	char	**tab;
	int		j;

	j = -1;
	if (!(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 4)
	{
		ft_free_tab(&tab);
		return (0);
	}
	while (tab[++j])
		if (!ft_is_numeric(tab[j]))
		{
			ft_free_tab(&tab);
			return (0);
		}
	(*new)[i] = vec->x * ft_atof(tab[0]) + vec->y * atof(tab[1]) +
			vec->z * ft_atof(tab[2]) + vec->w * atof(tab[3]);
	return (1);
}

int			ft_expect_matrix(char *line, char *name, t_vec4 *vec)
{
	char	**tab;
	int		i;
	double	new[4];

	if (!line)
		return (0);
	if (!(tab = ft_strsplit(line, '|')))
		return (0);
	if (ft_table_size(tab) != 5 ||
			ft_strncmp(tab[0], name, ft_strlen(name)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	i = 0;
	while (tab[++i])
		if (!ft_get_matrix(tab[i], i - 1, vec, &new))
		{
			ft_free_tab(&tab);
			return (0);
		}
	*vec = (t_vec4){new[0], new[1], new[2], new[3]};
	ft_free_tab(&tab);
	return (1);
}
