/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_plane_config.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:31:36 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/06 08:40:59 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static void	ft_plane_val_correction(t_plane **pl, t_data *data, int fd)
{
	t_vec4 up;
	double dot_prod;

	up = (t_vec4){0, 1, 0, 0};
	(*pl)->normal = ft_vec4_normalize((*pl)->normal);
	dot_prod = ft_vec4_dot_product((*pl)->normal, up);
	if (dot_prod <= 1 + NEAR && dot_prod >= 1 - NEAR)
		up = (t_vec4){1, 0, 0, 0};
	(*pl)->left = ft_vec4_normalize(ft_vec4_cross_product((*pl)->normal, up));
	(*pl)->forw = ft_vec4_normalize(
						ft_vec4_cross_product((*pl)->left, (*pl)->normal));
	if ((*pl)->texture.id > -1)
		if (!ft_texture_correction(&(*pl)->texture, data))
		{
			ft_error_management(data, 11, (void **)pl, fd);
		}
}

static int	ft_stock_plane_config_transfo(char *line, t_plane *p, int *i)
{
	int j;

	j = 0;
	if (!(*i & 16))
		return (0);
	if (ft_expect_matrix(line, "\ttransfo ", &(p->normal)))
	{
		p->normal = ft_vec4_normalize(p->normal);
		j++;
	}
	if (ft_expect_matrix(line, "\ttransfo ", &(p->point)))
		j++;
	return (j == 2 ? 1 : 0);
}

static int	ft_plane_values(int *i, t_plane *p, char *s)
{
	if (!(*i & 1) && ft_expect_vector(s, "\tposition", &(p->point)))
		*i += 1;
	else if (!(*i & 2) && ft_expect_color(s, "\tcolor", &(p->color)))
		*i += 2;
	else if (!(*i & 4) && ft_expect_diffuse(s, "\tdiffuse", &(p->diffuse)))
		*i += 4;
	else if (!(*i & 8) && ft_expect_value(s, "\tspecular", &(p->specular)))
		*i += 8;
	else if (!(*i & 16) && ft_expect_vector(s, "\tnormal", &(p->normal)))
		*i += 16;
	else if (!(*i & 32) && ft_stock_plane_config_transfo(s, p, i))
		*i += 32;
	else if (!(*i & 64) && ft_expect_ref(s, "\tref", &p->ref))
		*i += 64;
	else if (!(*i & 128) && ft_expect_texture(s, "\ttexture", &p->texture))
		*i += 128;
	else
		return (0);
	return (1);
}

static int	ft_stock_plane_config(int fd, t_plane *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_plane_values(&i, p, s))
		{
			p->ref.w = (i | 64) > i ? 0 : p->ref.w;
			if ((i | 128) > i)
			{
				p->texture.img = NULL;
				p->texture.id = -1;
			}
		}
		else if ((j = ft_bracket_control(s, '}')))
			break ;
		else
			break ;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return ((i == 31 || (((i & 31) == 31 && i & 255))) && j ? 1 : 0);
}

void		ft_get_plane_config(int fd, t_data *data)
{
	char	*line;
	t_plane	*plane;

	if (!(plane = (t_plane *)malloc(sizeof(t_plane))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_plane_config(fd, plane, 0, 0)))
			{
				ft_memdel((void **)&plane);
				ft_error_management(data, 3, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 3, (void **)&line, fd);
	}
	ft_plane_val_correction(&plane, data, fd);
	ft_lstadd(&(data->scene), ft_lstnew((void *)plane, PLANE));
}
