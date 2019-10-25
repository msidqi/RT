/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_camera_config.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 08:28:46 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/06 08:36:52 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int	ft_stock_camera_config(int fd, t_data *data)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_expect_vector(line, "\tposition", &(data->cam.pos)))
			i += 1;
		else if (ft_expect_vector(line, "\tlook_at", &(data->cam.to)))
			i -= 2;
		else if ((j = ft_bracket_control(line, '}')))
			break ;
		else
		{
			i = 0;
			break ;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (i == -1 && j ? 1 : 0);
}

void		ft_get_camera_config(int fd, t_data *data)
{
	char *line;

	if (data->cam.n > 1)
		ft_error_management(data, 8, NULL, fd);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_camera_config(fd, data)))
				ft_error_management(data, 1, (void **)&line, fd);
			else
			{
				data->cam.n += 1;
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 8, (void **)&line, fd);
	}
}
