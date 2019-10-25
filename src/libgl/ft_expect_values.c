/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:55:33 by arezouk           #+#    #+#             */
/*   Updated: 2019/10/04 20:01:03 by arezouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int			ft_expect_spot_dot(char *line, char *name, float *spot_dot)
{
	char	**tab;
	float	val;

	if (!line || !(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 2 ||
			ft_strncmp(tab[0], name, ft_strlen(name)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	val = ft_atof(tab[1]);
	if (!ft_is_numeric(tab[1]) || val >= 0.0 || val <= -1.0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	*spot_dot = val;
	ft_free_tab(&tab);
	return (1);
}

int			ft_expect_intensity(char *line, char *name, t_light *light)
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
		if (!ft_is_numeric(tab[i]) || !ft_is_limited(ft_atof(tab[i])))
		{
			ft_free_tab(&tab);
			return (0);
		}
	light->r = ft_atof(tab[1]);
	light->g = ft_atof(tab[2]);
	light->b = ft_atof(tab[3]);
	ft_free_tab(&tab);
	return (1);
}

int			ft_expect_diffuse(char *line, char *name, t_vec4 *vector)
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
		if (!ft_is_numeric(tab[i]) || !ft_is_limited(ft_atof(tab[i])))
		{
			ft_free_tab(&tab);
			return (0);
		}
	*vector = (t_vec4){ft_atof(tab[1]), ft_atof(tab[2]),
			ft_atof(tab[3]), 0};
	ft_free_tab(&tab);
	return (1);
}

int			ft_expect_color(char *line, char *name, int *color)
{
	char	**tab;

	if (!line)
		return (0);
	if (!(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 4 ||
			ft_strncmp(tab[0], name, ft_strlen(name)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	if (!ft_is_numeric(tab[1]))
	{
		ft_free_tab(&tab);
		return (0);
	}
	*color = (ft_atoi(tab[1]) << 16) | (ft_atoi(tab[2]) << 8) | ft_atoi(tab[3]);
	ft_free_tab(&tab);
	return (1);
}

int			ft_expect_texture(char *line, char *name, t_texture *t)
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
	t->id = ft_atoi(tab[1]);
	t->stretch_x = ft_atof(tab[2]);
	t->stretch_y = ft_atof(tab[3]);
	t->stretch_z = ft_atof(tab[4]);
	ft_free_tab(&tab);
	return (1);
}
