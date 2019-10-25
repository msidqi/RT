/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_hyperboloid_config.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 09:05:40 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/05 22:32:16 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int	ft_hyper_values(int *i, t_hyper *p, char *s)
{
	if (!(*i & 1) && ft_expect_value(s, "\tkernel", &p->k))
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
	else if (!(*i & 64) && ft_expect_matrix(s, "\ttransfo ", &p->center))
		*i += 64;
	else
		return (0);
	return (1);
}

static int	ft_stock_hyper_config(int fd, t_hyper *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_hyper_values(&i, p, s))
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
	return (((i == 31 || (((i & 31) == 31) && i & 127))) && j ? 1 : 0);
}

void		ft_get_hyperboloid_config(int fd, t_data *data)
{
	char	*line;
	t_hyper	*hyper;

	if (!(hyper = (t_hyper *)malloc(sizeof(t_hyper))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_hyper_config(fd, hyper, 0, 0)))
			{
				ft_memdel((void **)&hyper);
				ft_error_management(data, 20, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 20, (void **)&line, fd);
	}
	ft_lstadd(&(data->scene), ft_lstnew((void *)hyper, HYPER));
}
