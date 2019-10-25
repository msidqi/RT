/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 08:03:33 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/04 19:58:36 by arezouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int			ft_expect_vector(char *line, char *name, t_vec4 *vector)
{
	char	**tab;
	int		i;

	if (!line || !(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 4 ||
			ft_strncmp(tab[0], name, ft_strlen(name)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	i = 0;
	while (tab[++i])
		if (!ft_is_numeric(tab[i]))
		{
			ft_free_tab(&tab);
			return (0);
		}
	i = !ft_strcmp(tab[0], "\tnormal") ? 0 : 1;
	*vector = (t_vec4){ft_atof(tab[1]), ft_atof(tab[2]),
			ft_atof(tab[3]), i};
	ft_free_tab(&tab);
	return (1);
}

int			ft_expect_value(char *line, char *name, double *value)
{
	char	**tab;

	if (!line || !(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 2 || ft_strncmp(tab[0],
				name, ft_strlen(name)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	if (!ft_is_numeric(tab[1]))
	{
		ft_free_tab(&tab);
		return (0);
	}
	if (!ft_strcmp(tab[0], "\tspecular") && !ft_is_limited(ft_atof(tab[1])))
	{
		ft_free_tab(&tab);
		return (0);
	}
	*value = ft_atof(tab[1]);
	ft_free_tab(&tab);
	return (1);
}

int			ft_expect_ref(char *line, char *n, t_ref *ref)
{
	char	**tab;
	int		i;

	if (!line || !(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 7 || ft_strncmp(tab[0], n, ft_strlen(n)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	i = 0;
	while (tab[++i] && i < 3)
		if (!ft_is_numeric(tab[i]) || !ft_is_limited(ft_atof(tab[i])))
		{
			ft_free_tab(&tab);
			return (0);
		}
	ref->x = ft_atof(tab[1]);
	ref->y = ft_atof(tab[2]);
	ref->z = ft_atof(tab[3]);
	ref->w = (ft_atof(tab[4]) > 3 || ft_atof(tab[4]) < 0) ? 0 : ft_atof(tab[4]);
	ref->n = ft_atof(tab[5]);
	ref->noshading = ft_atoi(tab[6]);
	ft_free_tab(&tab);
	return (1);
}

int			ft_expect_area_uv(char *line, char *name, t_vec4 *uv_dir,
		unsigned short *uv_nodes)
{
	char	**tab;
	int		i;

	if (!line || !(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 5 ||
			ft_strncmp(tab[0], name, ft_strlen(name)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	i = 0;
	while (tab[++i])
		if (!ft_is_numeric(tab[i]))
		{
			ft_free_tab(&tab);
			return (0);
		}
	uv_dir->x = ft_atof(tab[1]);
	uv_dir->y = ft_atof(tab[2]);
	uv_dir->z = ft_atof(tab[3]);
	*uv_nodes = (unsigned short)ft_atoi(tab[4]);
	ft_free_tab(&tab);
	return (1);
}

int			ft_expect_limited(char *line, char *name, t_limits *l)
{
	char	**tab;
	int		i;

	if (!line || !(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 6 ||
			ft_strncmp(tab[0], name, ft_strlen(name)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	i = 0;
	while (tab[++i])
		if (!ft_is_numeric(tab[i]))
		{
			ft_free_tab(&tab);
			return (0);
		}
	l->islimited = ft_atoi(tab[1]) > 0 ? 1 : 0;
	l->limit = fabs(ft_atof(tab[2]));
	l->x = ft_atof(tab[3]);
	l->y = ft_atof(tab[4]);
	l->z = ft_atof(tab[5]);
	ft_free_tab(&tab);
	return (1);
}
