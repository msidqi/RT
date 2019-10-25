/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_light_config.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:01:45 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/06 09:10:58 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int		ft_light_value(t_light *l, int *i, char *s)
{
	if ((*i | 1) > *i && ft_expect_vector(s, "\tposition", &(l->origin)))
		*i = *i | 1;
	else if ((*i | 2) > *i && ft_expect_intensity(s, "\tintensity", l))
		*i = *i | 2;
	else if ((*i | 4) > *i && ft_expect_area_uv(s, "\tarea_u", &(l->u_dir),
		&(l->u_nodes)))
		*i = *i | 4;
	else if ((*i | 8) > *i && ft_expect_area_uv(s, "\tarea_v", &(l->v_dir),
		&(l->v_nodes)))
		*i = *i | 8;
	else if ((*i | 16) > *i && ft_expect_spot_dot(s, "\tspot_dot",
		&(l->spot_dot)))
		*i = *i | 16;
	else if ((*i | 32) > *i && ft_expect_vector(s, "\tdirection", &(l->dir)))
		*i = *i | 32;
	else
		return (0);
	return (1);
}

static int		ft_stock_light_config(int fd, t_light *l, int i, int j)
{
	char *s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_light_value(l, &i, s))
			(void)s;
		else if ((j = ft_bracket_control(s, '}')))
			break ;
		else
			break ;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return ((l->type = ft_light_type(i)) >= 0 && j ? 1 : 0);
}

static t_vec4	ft_node_pos(t_light *light, int *i_j)
{
	return (ft_vec4_add(light->origin,
		ft_vec4_add(ft_vec4_scalar(light->u_dir,
			(i_j[1] + (float)(rand() % 10) / light->u_nodes)
							* 0.05 - (light->u_nodes * 0.05 / 2)),
		ft_vec4_scalar(light->v_dir,
			(i_j[0] + (float)(rand() % 10) / light->v_nodes)
							* 0.05 - (light->v_nodes * 0.05 / 2)))));
}

static void		ft_create_area_lightlst(t_data *data, int fd, t_light *l)
{
	t_light *new;
	int		i_j[2];

	if (l->type == AREA_LIGHT || l->type == AREA_SPOT_LIGHT)
	{
		i_j[0] = -1;
		l->lst = NULL;
		while (++i_j[0] < l->v_nodes)
		{
			i_j[1] = -1;
			while (++i_j[1] < l->u_nodes)
			{
				if (!(new = (t_light *)malloc(sizeof(t_light))))
					ft_error_management(data, 10, NULL, fd);
				if (l->type == AREA_SPOT_LIGHT)
				{
					new->spot_dot = l->spot_dot;
					new->dir = l->dir;
				}
				new->origin = ft_node_pos(l, i_j);
				new->type = (l->type == AREA_LIGHT) ? POINT_LIGHT : SPOT_LIGHT;
				ft_lstadd(&l->lst, ft_lstnew((void *)new, 0));
			}
		}
	}
}

void			ft_get_light_config(int fd, t_data *data)
{
	char	*line;
	t_light	*light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_light_config(fd, light, 0, 0)))
			{
				ft_memdel((void **)&light);
				ft_error_management(data, 6, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 6, (void **)&line, fd);
	}
	ft_create_area_lightlst(data, fd, light);
	ft_lstadd(&(data->light_list), ft_lstnew((void *)light, 0));
}
