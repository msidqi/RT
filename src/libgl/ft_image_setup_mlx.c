/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 04:50:04 by msidqi            #+#    #+#             */
/*   Updated: 2019/04/25 04:50:06 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
** creates an image in memory, return (void *)
**	if (!(data->img_ptr = mlx_new_image(data->mlx, data->winwidth,
**		data->winheight)))
**        return (0);
**
** takes ptr to the image and returns details about it + (char *) to 1st byte
**	if (!(data->image = (int *)mlx_get_data_addr(data->img_ptr, &data->bpp,
**                                          &data->size_line, &data->endian)))
**        return (0);
** casted to int to make defining colors easier by using Hex numbers for
** RGBA instead of each byte on its own
*/

int		ft_image_setup(t_data *data)
{
	if (!data || !data->mlx || data->winwidth < 1 || data->winheight < 1
	|| !(data->img_ptr = mlx_new_image(data->mlx,
										data->winwidth, data->winheight))
	|| !(data->image = (int *)mlx_get_data_addr(data->img_ptr, &data->bpp,
										&data->size_line, &data->endian)))
		return (0);
	return (1);
}

void	ft_image_fill(t_data *data, int x, int y, int color)
{
	if (y <= data->winheight && x <= data->winwidth)
		data->image[y * data->winwidth + x] = color;
	else
		ft_putstr_fd("Error : buffer overflow\n", 2);
}

int		ft_window_setup(t_data *data, char *win_name,
									int winheight, int winwidth)
{
	if (!data || winheight < 1 || winwidth < 1
							|| !win_name || !(data->mlx = mlx_init()))
		return (0);
	data->winheight = winheight;
	data->winwidth = winwidth;
	if (!(data->win = mlx_new_window(data->mlx, data->winwidth,
											data->winheight, win_name)))
		return (0);
	return (1);
}
