/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_scene_config.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 11:53:44 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/05 23:04:23 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int	ft_scene_values(int *i, t_data *data, char *s)
{
	if (!(*i & 1) && ft_expect_value(s, "\tfilter", &data->filter))
		*i += 1;
	else if (!(*i & 2) && ft_expect_vector(s, "\tambient", &data->ambient))
		*i += 2;
	else if (!(*i & 4) && ft_expect_value(s, "\tdepthoffield",
				&data->depthoffield))
		*i += 4;
	else
		return (0);
	return (1);
}

static int	ft_stock_scene_config(int fd, t_data *data, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_scene_values(&i, data, s))
		{
			if ((i | 1) > i)
				data->filter = 0;
			if ((i | 2) > i)
				data->ambient.w = 0;
			if ((i | 4) > i)
				data->depthoffield = 0;
		}
		else if ((j = ft_bracket_control(s, '}')))
			break ;
		else
			break ;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return ((i & 7) && j ? 1 : 0);
}

void		ft_get_scene_config(int fd, t_data *data)
{
	char		*line;

	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_scene_config(fd, data, 0, 0)))
				ft_error_management(data, 13, (void **)&line, fd);
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 13, (void **)&line, fd);
	}
}
