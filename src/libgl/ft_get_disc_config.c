/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_disc_config.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 10:44:31 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/06 08:55:44 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static void	ft_disc_val_correction(t_disc **d, t_data *data, int fd)
{
	t_vec4	up;
	double	dot_prod;

	up = (t_vec4){0, 1, 0, 0};
	(*d)->normal = ft_vec4_normalize((*d)->normal);
	dot_prod = ft_vec4_dot_product((*d)->normal, up);
	if (dot_prod <= 1 + NEAR && dot_prod >= 1 - NEAR)
		up = (t_vec4){1, 0, 0, 0};
	(*d)->left = ft_vec4_normalize(
			ft_vec4_cross_product((*d)->normal, up));
	(*d)->forw = ft_vec4_normalize(
			ft_vec4_cross_product((*d)->left, (*d)->normal));
	if ((*d)->texture.id > -1)
		if (!ft_texture_correction(&(*d)->texture, data))
			ft_error_management(data, 11, (void **)d, fd);
}

static int	ft_stock_disc_config_transfo(char *line, t_disc *p, int *i)
{
	int j;

	j = 0;
	if (!(*i & 1) || !(*i & 16))
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

static int	ft_disc_values(int *i, t_disc *p, char *s)
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
	else if (!(*i & 32) && ft_stock_disc_config_transfo(s, p, i))
		*i += 32;
	else if (!(*i & 64) && ft_expect_ref(s, "\tref", &p->ref))
		*i += 64;
	else if (!(*i & 128) && ft_expect_texture(s, "\ttexture", &p->texture))
		*i += 128;
	else if (!(*i & 256) && ft_expect_value(s, "\tradius", &p->radius))
		*i += 256;
	else
		return (0);
	return (1);
}

static int	ft_stock_disc_config(int fd, t_disc *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_disc_values(&i, p, s))
		{
			if ((i | 64) > i)
				p->ref.w = 0;
			if ((i | 128) > i)
			{
				p->texture.img = NULL;
				p->texture.id = -1;
			}
		}
		else if ((j = ft_bracket_control(s, '}')))
			break ;
		else
			i = 0;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return ((i == 287 || (((i & 287) == 287 && i & 511))) && j ? 1 : 0);
}

void		ft_get_disc_config(int fd, t_data *data)
{
	char	*line;
	t_disc	*disc;

	if (!(disc = (t_disc *)malloc(sizeof(t_disc))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_disc_config(fd, disc, 0, 0)))
			{
				ft_memdel((void **)&disc);
				ft_error_management(data, 15, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 15, (void **)&line, fd);
	}
	ft_disc_val_correction(&disc, data, fd);
	ft_lstadd(&(data->scene), ft_lstnew((void *)disc, DISC));
}
