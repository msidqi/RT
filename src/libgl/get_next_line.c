/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 14:43:01 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/04 19:24:57 by arezouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libgl.h"

static int		fill_next_line(int fd, char **line, char **ch, int rvalue)
{
	char		*stock;
	int			i;

	i = 0;
	while (ch[fd][i] != '\n' && ch[fd][i])
		i++;
	if (ch[fd][i] == '\n')
	{
		*line = ft_strsub(ch[fd], 0, i);
		stock = ft_strdup(ch[fd] + i + 1);
		free(ch[fd]);
		ch[fd] = stock;
		if (ch[fd][0] == '\0')
			ft_strdel(&ch[fd]);
	}
	else if (ch[fd][i] == '\0')
	{
		if (rvalue == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(ch[fd]);
		ft_strdel(&ch[fd]);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*ch[4096];
	char		buff[BUFF_SIZE + 1];
	char		*stock;
	int			rvalue;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((rvalue = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[rvalue] = '\0';
		if (ch[fd] == NULL)
			ch[fd] = ft_strnew(1);
		stock = ft_strjoin(ch[fd], buff);
		free(ch[fd]);
		ch[fd] = stock;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (rvalue == -1)
		return (-1);
	else if (rvalue == 0 && (ch[fd] == NULL || ch[fd][0] == '\0'))
		return (0);
	return (fill_next_line(fd, line, ch, rvalue));
}
