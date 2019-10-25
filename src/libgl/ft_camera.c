/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:56:57 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/06 17:44:54 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static double	ft_map(int x_or_y, double size, int width_or_height)
{
	return (x_or_y * size / width_or_height - (size / 2));
}

void			random_jitter(t_data *data, size_t size)
{
	size_t i;

	i = 0;
	while (i < size * 2)
	{
		data->aa_jitter[i] = (double)(((int)i - (int)size) / (double)size);
		i++;
	}
}

void			ft_camera_ray_dof(t_ray *ray, t_data *d, int *xy, int jitter)
{
	t_vec4	new_left;
	t_vec4	new_up;
	t_vec4	forw_left_up[2];
	t_vec4	i_aim[2];
	double	r_du_dv[2];

	r_du_dv[0] = rand() / (double)(RAND_MAX) + 2;
	r_du_dv[1] = rand() / (double)(RAND_MAX) + 2;
	new_left = ft_vec4_scalar(d->cam.left, ft_map(xy[0] +
	d->aa_jitter[2 * jitter] - ((WIDTH - HEIGHT) / 2), d->cam.bigl,
	(double)(WIDTH * ASPECT_RATIO)));
	new_up = ft_vec4_scalar(d->cam.up, ft_map(xy[1] +
	d->aa_jitter[2 * jitter + 1], d->cam.l, HEIGHT));
	forw_left_up[0] = ft_vec4_scalar(d->cam.forward, d->cam.focal_length);
	forw_left_up[1] = ft_vec4_add(new_up, new_left);
	i_aim[0] = ft_vec4_add(d->cam.pos,
	ft_vec4_add(ft_vec4_scalar(ft_vec4_scalar(d->cam.left, 0.3), r_du_dv[0]),
	ft_vec4_scalar(ft_vec4_scalar(d->cam.up, 0.3), r_du_dv[1])));
	ray->dir = ft_vec4_add(forw_left_up[1], forw_left_up[0]);
	i_aim[1] = ft_vec4_add(d->cam.pos, ft_vec4_scalar(ray->dir, d->cam.f_dist));
	ray->origin = (t_vec4){i_aim[0].x, i_aim[0].y, i_aim[0].z, 0};
	ray->dir = ft_vec4_normalize(ft_vec4_sub(i_aim[1], i_aim[0]));
	ray->t = FAR;
	ray->refl_depth = d->cam.refl_depth;
}

void			ft_camera_ray_aa(t_ray *ray, t_data *data, int *xy, int jitter)
{
	t_vec4 new_left;
	t_vec4 new_up;
	t_vec4 new_forw;
	t_vec4 left_up;

	new_left = ft_vec4_scalar(data->cam.left, ft_map(xy[0] +
	data->aa_jitter[2 * jitter] - ((WIDTH - HEIGHT) / 2), data->cam.bigl,
	(double)(WIDTH * ASPECT_RATIO)));
	new_up = ft_vec4_scalar(data->cam.up, ft_map(xy[1] +
	data->aa_jitter[2 * jitter + 1], data->cam.l, HEIGHT));
	new_forw = ft_vec4_scalar(data->cam.forward, data->cam.focal_length);
	left_up = ft_vec4_add(new_up, new_left);
	ray->dir = ft_vec4_normalize(ft_vec4_add(left_up, new_forw));
	ray->origin = (t_vec4){data->cam.pos.x, data->cam.pos.y,
	data->cam.pos.z, 0};
	ray->t = FAR;
	ray->refl_depth = data->cam.refl_depth;
}

void			ft_camera(t_data *data, t_vec4 position, t_vec4 lookat)
{
	t_vec4 forward;
	t_vec4 camera_up;
	t_vec4 camera_left;
	t_vec4 up;

	data->cam.l = 1;
	data->cam.bigl = 3;
	data->cam.bigl = data->cam.bigl * (data->cam.l / data->cam.bigl);
	data->cam.pos = position;
	data->cam.to = lookat;
	forward = ft_vec4_normalize(ft_vec4_sub(data->cam.to, data->cam.pos));
	if (forward.x == 0 && forward.y == 1 && forward.z == 0)
		up = ft_vec4_normalize((t_vec4){1, 0, 0, 0});
	else
		up = ft_vec4_normalize((t_vec4){0, 1, 0, 0});
	camera_left = ft_vec4_cross_product(up, forward);
	camera_up = ft_vec4_cross_product(forward, camera_left);
	data->cam.up = ft_vec4_normalize(camera_up);
	data->cam.left = ft_vec4_normalize(camera_left);
	data->cam.forward = forward;
}
