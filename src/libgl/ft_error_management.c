/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 08:08:09 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/06 08:56:22 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

void		ft_del(void *content, size_t size)
{
	(void)size;
	free(content);
}

static void	ft_free_lights(t_data *data)
{
	t_list	*tmp;

	tmp = data->light_list;
	while (tmp)
	{
		if (((t_light *)tmp->content)->type == AREA_LIGHT ||
			((t_light *)tmp->content)->type == AREA_SPOT_LIGHT)
			ft_lstdel(&((t_light *)tmp->content)->lst, &ft_del);
		tmp = tmp->next;
	}
	ft_lstdel(&data->light_list, &ft_del);
}

static void	ft_delete_image(t_data *data)
{
	if (data->scene->content_size == SPHERE &&
			((t_sphere *)data->scene->content)->texture.img != NULL)
		mlx_destroy_image(data->mlx,
				((t_sphere *)data->scene->content)->texture.img);
	else if (data->scene->content_size == PLANE
			&& ((t_plane *)data->scene->content)->texture.img != NULL)
		mlx_destroy_image(data->mlx,
				((t_plane *)data->scene->content)->texture.img);
	else if (data->scene->content_size == CONE &&
			((t_cone *)data->scene->content)->texture.img != NULL)
		mlx_destroy_image(data->mlx,
				((t_cone *)data->scene->content)->texture.img);
	else if (data->scene->content_size == CYLINDER &&
			((t_cylinder *)data->scene->content)->texture.img != NULL)
		mlx_destroy_image(data->mlx,
				((t_cylinder *)data->scene->content)->texture.img);
	else if (data->scene->content_size == DISC
			&& ((t_disc *)data->scene->content)->texture.img != NULL)
		mlx_destroy_image(data->mlx,
				((t_disc *)data->scene->content)->texture.img);
}

void		ft_free_objects(t_data *data)
{
	t_list	*tmp;

	while (data->scene)
	{
		tmp = data->scene->next;
		ft_delete_image(data);
		free(data->scene->content);
		free(data->scene);
		data->scene = tmp;
	}
}

void		ft_error_management(t_data *data, int error, void **to_free, int fd)
{
	if (fd != -1)
		close(fd);
	ft_memdel(to_free);
	ft_putendl_fd(ft_error_type(error), 2);
	if (error == 0)
		ft_putendl_fd("usage : \n./RT config file (read the manual for"
				" the config file syntax)", 2);
	ft_free_lights(data);
	ft_free_objects(data);
	exit(1);
}
