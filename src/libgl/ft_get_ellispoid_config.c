/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_ellispoid_config.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 11:49:23 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/06 00:53:44 by arezouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static void	ft_ellipsoid_val_correction(t_ellipsoid **ellipsoid,
		t_data *data, int fd)
{
	if ((*ellipsoid)->texture.id > -1)
	{
		if (!ft_load_texture((*ellipsoid)->texture.id,
					&(*ellipsoid)->texture, data))
			ft_error_management(data, 11, (void **)ellipsoid, fd);
		if ((*ellipsoid)->texture.stretch_x == 0)
			(*ellipsoid)->texture.stretch_x = 1;
		if ((*ellipsoid)->texture.stretch_y == 0)
			(*ellipsoid)->texture.stretch_y = 1;
		if ((*ellipsoid)->texture.stretch_z == 0)
			(*ellipsoid)->texture.stretch_z = 1;
	}
}

static int	ft_stock_ellip_matrix(char *line, t_ellipsoid *p, int *i)
{
	int	j;

	j = 0;
	if (!(*i & 1) || !(*i & 16))
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

static int	ft_ellipsoid_values(int *i, t_ellipsoid *p, char *s)
{
	if (!(*i & 1) && ft_expect_vector(s, "\tcenter", &p->center))
		*i += 1;
	else if (!(*i & 2) && ft_expect_color(s, "\tcolor", &p->color))
		*i += 2;
	else if (!(*i & 4) && ft_expect_diffuse(s, "\tdiffuse", &p->diffuse))
		*i += 4;
	else if (!(*i & 8) && ft_expect_value(s, "\tspecular", &p->specular))
		*i += 8;
	else if (!(*i & 16) && ft_expect_vector(s, "\taxis", &p->axis))
		*i += 16;
	else if (!(*i & 32) && ft_expect_ref(s, "\tref", &p->ref))
		*i += 32;
	else if (!(*i & 64) && ft_stock_ellip_matrix(s, p, i))
		*i += 64;
	else if (!(*i & 128) && ft_expect_texture(s, "\ttexture", &p->texture))
		*i += 128;
	else
		return (0);
	return (1);
}

static int	ft_stock_ellipsoid_config(int fd, t_ellipsoid *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_ellipsoid_values(&i, p, s))
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
	return (((i == 31 || (((i & 31) == 31) && i & 255))) && j ? 1 : 0);
}

void		ft_get_ellipsoid_config(int fd, t_data *data)
{
	char		*line;
	t_ellipsoid	*ellipsoid;

	if (!(ellipsoid = (t_ellipsoid *)malloc(sizeof(t_ellipsoid))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_ellipsoid_config(fd, ellipsoid, 0, 0)))
			{
				ft_memdel((void **)&ellipsoid);
				ft_error_management(data, 17, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 17, (void **)&line, fd);
	}
	ft_ellipsoid_val_correction(&ellipsoid, data, fd);
	ft_lstadd(&(data->scene), ft_lstnew((void *)ellipsoid, ELLIPSOID));
}
