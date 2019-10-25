/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_triangle_config.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 11:56:02 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/06 08:52:34 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int	ft_triangle_values(int *i, t_triangle *p, char *s)
{
	if (!(*i & 1) && ft_expect_vector(s, "\tvertex0", &p->vertex0))
		*i += 1;
	else if (!(*i & 2) && ft_expect_vector(s, "\tvertex1", &p->vertex1))
		*i += 2;
	else if (!(*i & 4) && ft_expect_color(s, "\tcolor", &p->color))
		*i += 4;
	else if (!(*i & 8) && ft_expect_diffuse(s, "\tdiffuse", &p->diffuse))
		*i += 8;
	else if (!(*i & 16) && ft_expect_value(s, "\tspecular", &p->specular))
		*i += 16;
	else if (!(*i & 32) && ft_expect_ref(s, "\tref", &p->ref))
		*i += 32;
	else if (!(*i & 64) && ft_expect_vector(s, "\tvertex2", &p->vertex2))
		*i += 64;
	else if (!(*i & 64) && ft_expect_vector(s, "\tvertex2", &p->vertex2))
		*i += 64;
	else
		return (0);
	return (1);
}

static int	ft_stock_triangle_config(int fd, t_triangle *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_triangle_values(&i, p, s))
		{
			if ((i | 32) > i)
				p->ref.w = 0;
		}
		else if ((j = ft_bracket_control(s, '}')))
			break ;
		else
			break ;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return ((i == 95 || i == 127) && j ? 1 : 0);
}

void		ft_get_triangle_config(int fd, t_data *data)
{
	char		*line;
	t_triangle	*triangle;

	if (!(triangle = (t_triangle *)malloc(sizeof(t_triangle))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_triangle_config(fd, triangle, 0, 0)))
			{
				ft_memdel((void **)&triangle);
				ft_error_management(data, 21, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 21, (void **)&line, fd);
	}
	ft_lstadd(&(data->scene), ft_lstnew((void *)triangle, TRIANGLE));
}
