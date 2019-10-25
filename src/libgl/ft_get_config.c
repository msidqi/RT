/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 08:26:04 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/05 20:25:15 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

const t_function g_t_function[16] =
{
	{ "=>camera :", &ft_get_camera_config },
	{ "=>light :", &ft_get_light_config },
	{ "=>sphere :", &ft_get_sphere_config },
	{ "=>plane :", &ft_get_plane_config },
	{ "=>cone :", &ft_get_cone_config },
	{ "=>cylinder :", &ft_get_cylinder_config },
	{ "=>box :", &ft_get_box_config },
	{ "=>disc :", &ft_get_disc_config },
	{ "=>hemisphere :", &ft_get_hemisphere_config},
	{ "=>torus :", &ft_get_torus_config},
	{ "=>hcube :", &ft_get_h_cube_config},
	{ "=>parab :", &ft_get_parab_config},
	{ "=>hyper :", &ft_get_hyperboloid_config},
	{ "=>ellipsoid :", &ft_get_ellipsoid_config},
	{ "=>triangle :", &ft_get_triangle_config},
	{ "=>scene :", &ft_get_scene_config}
};

static void	ft_scene_val_correction(t_data *data)
{
	if (data->ambient.w == 0 || !ft_is_limited(data->ambient.x)
		|| !ft_is_limited(data->ambient.y) || !ft_is_limited(data->ambient.z))
	{
		data->ambient.x = AMBIENT_R;
		data->ambient.y = AMBIENT_G;
		data->ambient.z = AMBIENT_B;
	}
	if (data->depthoffield > 100 || data->depthoffield < 0)
		data->depthoffield = 0;
	if (data->filter > 3 || data->filter < 0)
		data->filter = 0;
}

void		ft_get_config(char *conf_file, t_data *data)
{
	int				fd;
	char			*line;
	unsigned int	i;

	data->cam.n = 0;
	fd = open(conf_file, O_RDONLY);
	if (fd < 0)
		ft_error_management(data, 0, NULL, fd);
	while (get_next_line(fd, &line) > 0)
	{
		i = -1;
		while (++i < (unsigned int)STATIC_ARRAY_SIZE(g_t_function))
		{
			if (!ft_strcmp(g_t_function[i].type, line))
			{
				ft_strdel(&line);
				g_t_function[i].call(fd, data);
				break ;
			}
		}
	}
	close(fd);
	ft_scene_val_correction(data);
	ft_cheak_data(data);
}
