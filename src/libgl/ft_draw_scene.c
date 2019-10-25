/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:57:55 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/05 15:33:28 by arezouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

const				t_obj_function g_t_obj_ft2[13] =
{
	{ SPHERE, &ft_sphere_inter, &ft_sphere_shader },
	{ PLANE, &ft_plane_inter, &ft_plane_shader },
	{ CONE, &ft_cone_inter, &ft_cone_shader },
	{ CYLINDER, &ft_cylinder_inter, &ft_cylinder_shader },
	{ BOX, &ft_box_inter, &ft_box_shader },
	{ DISC, &ft_disc_inter, &ft_disc_shader },
	{ HSPHERE, &ft_hemisphere_inter, &ft_hemisphere_shader },
	{ TORUS, &ft_torus_inter, &ft_torus_shader },
	{ H_CUBE, &ft_h_cube_inter, &ft_h_cube_shader },
	{ PARAB, &ft_paraboloid_inter, &ft_paraboloid_shader },
	{ HYPER, &ft_hyperboloid_inter, &ft_hyperboloid_shader},
	{ ELLIPSOID, &ft_ellipsoid_inter, &ft_ellipsoid_shader},
	{ TRIANGLE, &ft_triangle_inter, &ft_triangle_shader},
};

/*
** JNUM : rays_number && jitter_number
*/

static void			ft_compute_pixel(t_data *data, int *colors, int *xy)
{
	int				ij[2];
	t_list			*s;
	t_ray			ray;

	ij[1] = -1;
	while (++ij[1] < JNUM)
	{
		if (data->depthoffield == 1)
			ft_camera_ray_dof(&ray, data, xy, ij[1]);
		else
			ft_camera_ray_aa(&ray, data, xy, ij[1]);
		s = data->scene;
		colors[ij[1]] = 0;
		while (s != NULL)
		{
			ij[0] = -1;
			while (++ij[0] < (int)STATIC_ARRAY_SIZE(g_t_obj_ft2))
				if (g_t_obj_ft2[ij[0]].type == s->content_size
					&& g_t_obj_ft2[ij[0]].call(&ray, s->content))
					colors[ij[1]] = ft_filters_aa(data,
			g_t_obj_ft2[ij[0]].call2(data, &ray, s->content));
			s = s->next;
		}
	}
}

void				ft_draw_scene(t_data *data)
{
	int				xy[2];
	int				colors[JNUM];

	xy[1] = data->thread_range.start.y - 1;
	while (++xy[1] < data->thread_range.end.y)
	{
		xy[0] = data->thread_range.start.x - 1;
		while (++xy[0] < data->thread_range.end.x)
		{
			ft_compute_pixel(data, colors, xy);
			ft_image_fill(data, xy[0], xy[1],
					ft_color_avg(colors, (size_t)JNUM));
		}
	}
}
