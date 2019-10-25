/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_torus_config.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:01:30 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/06 08:46:16 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static void		ft_torus_val_correction(t_torus **torus, t_data *data, int fd)
{
	(*torus)->axis = ft_vec4_normalize((*torus)->axis);
	if ((*torus)->texture.id > -1)
	{
		if (!ft_load_texture((*torus)->texture.id, &(*torus)->texture, data))
			ft_error_management(data, 11, (void **)torus, fd);
		if ((*torus)->texture.stretch_x == 0)
			(*torus)->texture.stretch_x = 1;
		if ((*torus)->texture.stretch_y == 0)
			(*torus)->texture.stretch_y = 1;
		if ((*torus)->texture.stretch_z == 0)
			(*torus)->texture.stretch_z = 1;
	}
}

static int		ft_stock_torus_config_next(char *line, t_torus *p, int *i)
{
	int	j;

	j = 0;
	if (!(*i & 2) || !(*i & 512))
		return (0);
	if (ft_expect_matrix(line, "\ttransfo ", &(p->axis)))
	{
		p->axis = ft_vec4_normalize(p->axis);
		j++;
	}
	if (ft_expect_matrix(line, "\ttransfo ", &(p->center)))
		j++;
	return (j == 2 ? 1 : 0);
}

static int		ft_sphere_values(int *i, t_torus *p, char *s)
{
	if (!(*i & 1) && ft_expect_value(s, "\tbig_radius", &p->br))
		*i += 1;
	else if (!(*i & 2) && ft_expect_vector(s, "\tcenter", &p->center))
		*i += 2;
	else if (!(*i & 4) && ft_expect_color(s, "\tcolor", &p->color))
		*i += 4;
	else if (!(*i & 8) && ft_expect_diffuse(s, "\tdiffuse", &p->diffuse))
		*i += 8;
	else if (!(*i & 16) && ft_expect_value(s, "\tspecular", &p->specular))
		*i += 16;
	else if (!(*i & 32) && ft_expect_ref(s, "\tref", &p->ref))
		*i += 32;
	else if (!(*i & 64) && ft_stock_torus_config_next(s, p, i))
		*i += 64;
	else if (!(*i & 128) && ft_expect_texture(s, "\ttexture", &p->texture))
		*i += 128;
	else if (!(*i & 256) && ft_expect_value(s, "\tsmall_radius", &p->sr))
		*i += 256;
	else if (!(*i & 512) && ft_expect_vector(s, "\taxis", &p->axis))
		*i += 512;
	else
		return (0);
	return (1);
}

static int		ft_stock_torus_config(int fd, t_torus *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_sphere_values(&i, p, s))
		{
			if ((i | 32) > i)
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
			break ;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return (((i == 799) || ((i & 799) == 799 && (i & 1023))) && j ? 1 : 0);
}

void			ft_get_torus_config(int fd, t_data *data)
{
	char		*line;
	t_torus		*torus;

	if (!(torus = (t_torus *)malloc(sizeof(t_torus))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_torus_config(fd, torus, 0, 0)))
			{
				ft_memdel((void **)&torus);
				ft_error_management(data, 18, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 18, (void **)&line, fd);
	}
	ft_torus_val_correction(&torus, data, fd);
	ft_lstadd(&(data->scene), ft_lstnew((void *)torus, TORUS));
}
