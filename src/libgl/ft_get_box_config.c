/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_box_config.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 11:40:21 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/06 08:43:21 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int	ft_stock_box_config_next(char *line, t_box *p, int *i)
{
	int	j;
	int	tmp;

	j = 0;
	tmp = 0;
	if (ft_expect_matrix(line, "\ttransfo ", &(p->bmax)))
		j++;
	if (ft_expect_matrix(line, "\ttransfo ", &(p->bmin)))
		j++;
	if (j == 2)
		*i += 32;
	return (j == 2 || tmp ? 1 : 0);
}

static int	ft_box_values(int *i, t_box *p, char *s)
{
	if (!(*i & 1) && ft_expect_vector(s, "\tbmax", &(p->bmax)))
		*i += 1;
	else if (!(*i & 2) && ft_expect_color(s, "\tcolor", &(p->color)))
		*i += 2;
	else if (!(*i & 4) && ft_expect_diffuse(s, "\tdiffuse", &(p->diffuse)))
		*i += 4;
	else if (!(*i & 8) && ft_expect_value(s, "\tspecular", &(p->specular)))
		*i += 8;
	else if (!(*i & 16) && ft_expect_vector(s, "\tbmin", &(p->bmin)))
		*i += 16;
	else if (!(*i & 32) && ft_stock_box_config_next(s, p, i))
		*i += 0;
	else if (!(*i & 64) && ft_expect_ref(s, "\tref", &p->ref))
		*i += 64;
	else
		return (0);
	return (1);
}

static int	ft_stock_box_config(int fd, t_box *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_box_values(&i, p, s))
		{
			if ((i | 64) > i)
				p->ref.w = 0;
		}
		else if ((j = ft_bracket_control(s, '}')))
			break ;
		else
			break ;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return ((i == 31 || i == 63 || i == 127 || i == 95) && j ? 1 : 0);
}

void		ft_get_box_config(int fd, t_data *data)
{
	char	*line;
	t_box	*box;

	if (!(box = (t_box *)malloc(sizeof(t_box))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_box_config(fd, box, 0, 0)))
			{
				ft_memdel((void **)&box);
				ft_error_management(data, 12, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 12, (void **)&line, fd);
	}
	ft_lstadd(&(data->scene), ft_lstnew((void *)box, BOX));
}
