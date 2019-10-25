/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_paraboloid_config.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 09:05:40 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/06 00:52:23 by arezouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int	ft_stock_parab_config_next(char *line, t_parab *p, int *i)
{
	int	j;

	j = 0;
	if (!(*i & 2) || !(*i & 128))
		return (0);
	if (ft_expect_matrix(line, "\ttransfo ", &(p->center)))
		j++;
	return (j == 1 ? 1 : 0);
}

static int	ft_parab_values(int *i, t_parab *p, char *s)
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
	else if (!(*i & 64) && ft_stock_parab_config_next(s, p, i))
		*i += 64;
	else if (!(*i & 128) && ft_expect_vector(s, "\tnormal", &p->normal))
		*i += 128;
	else
		return (0);
	return (1);
}

static int	ft_stock_parab_config(int fd, t_parab *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_parab_values(&i, p, s))
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
	return (((i == 159 || (((i & 159) == 159) && i & 255))) && j ? 1 : 0);
}

void		ft_get_parab_config(int fd, t_data *data)
{
	char	*line;
	t_parab	*parab;

	if (!(parab = (t_parab *)malloc(sizeof(t_parab))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_parab_config(fd, parab, 0, 0)))
			{
				ft_memdel((void **)&parab);
				ft_error_management(data, 19, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 19, (void **)&line, fd);
	}
	parab->normal = ft_vec4_normalize(parab->normal);
	ft_lstadd(&(data->scene), ft_lstnew((void *)parab, PARAB));
}
