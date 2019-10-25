/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_system.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 03:12:45 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/02 03:12:46 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int			red_button(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img_ptr);
	mlx_destroy_window(data->mlx, data->win);
	ft_lstdel(&data->scene, &ft_del);
	ft_lstdel(&data->light_list, &ft_del);
	exit(0);
	return (0);
}

void		ft_refresh_image(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img_ptr);
	data->img_ptr = mlx_new_image(data->mlx, data->winwidth, data->winheight);
	data->image = (int *)mlx_get_data_addr(data->img_ptr,
								&data->bpp, &data->size_line, &data->endian);
}

/*
** void		ft_refresh_image_no_event(t_data *data)
** {
** 	mlx_destroy_image(data->mlx, data->img_ptr);
** 	data->img_ptr = mlx_new_image(data->mlx, data->winwidth, data->winheight);
** 	data->image = (int *)mlx_get_data_addr(data->img_ptr,
** 								&data->bpp, &data->size_line, &data->endian);
** }
** 	mlx_loop_hook(data->mlx, &no_event_mouse_move, (void *)data);
*/

void		ft_mlx_hooks(t_data *data, int events)
{
	if ((events & MOUSE_MOVE_HOOK))
		mlx_hook(data->win, MOUSE_MOVE_CODE, 0, &mouse_move, (void *)data);
	if ((events & KEY_PRESS_HOOK))
		mlx_hook(data->win, KEY_PRESS_CODE, 0, &key_press, (void *)data);
	if ((events & MOUSE_PRESS_HOOK))
		mlx_hook(data->win, MOUSE_PRESS_CODE, 0, &mouse_press, (void *)data);
	if ((events & RED_BUTTON_HOOK))
		mlx_hook(data->win, RED_BUTTON_CODE, 0, &red_button, (void *)data);
	mlx_loop(data->mlx);
}
