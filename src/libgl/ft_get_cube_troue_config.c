/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cube_troue_config.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 09:05:40 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/05 22:21:06 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static void	ft_h_cube_val_correction(t_h_cube **h_cube, t_data *data, int fd)
{
	if ((*h_cube)->texture.id > -1)
	{
		if (!ft_load_texture((*h_cube)->texture.id, &(*h_cube)->texture, data))
			ft_error_management(data, 11, (void **)h_cube, fd);
		if ((*h_cube)->texture.stretch_x == 0)
			(*h_cube)->texture.stretch_x = 1;
		if ((*h_cube)->texture.stretch_y == 0)
			(*h_cube)->texture.stretch_y = 1;
		if ((*h_cube)->texture.stretch_z == 0)
			(*h_cube)->texture.stretch_z = 1;
	}
}

static int	ft_h_cube_values(int *i, t_h_cube *p, char *s)
{
	if (!(*i & 1) && ft_expect_value(s, "\tradius", &p->radius))
		*i += 1;
	else if (!(*i & 2) && ft_expect_color(s, "\tcolor", &p->color))
		*i += 2;
	else if (!(*i & 4) && ft_expect_diffuse(s, "\tdiffuse", &p->diffuse))
		*i += 4;
	else if (!(*i & 8) && ft_expect_value(s, "\tspecular", &p->specular))
		*i += 8;
	else if (!(*i & 16) && ft_expect_ref(s, "\tref", &p->ref))
		*i += 16;
	else
		return (0);
	return (1);
}

static int	ft_stock_h_cube_config(int fd, t_h_cube *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_h_cube_values(&i, p, s))
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
	return ((i == 15 || (((i & 15) == 15 && i & 31))) && j ? 1 : 0);
}

void		ft_get_h_cube_config(int fd, t_data *data)
{
	char		*line;
	t_h_cube	*h_cube;

	if (!(h_cube = (t_h_cube *)malloc(sizeof(t_h_cube))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_h_cube_config(fd, h_cube, 0, 0)))
			{
				ft_memdel((void **)&h_cube);
				ft_error_management(data, 16, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 16, (void **)&line, fd);
	}
	ft_h_cube_val_correction(&h_cube, data, fd);
	ft_lstadd(&(data->scene), ft_lstnew((void *)h_cube, H_CUBE));
}
