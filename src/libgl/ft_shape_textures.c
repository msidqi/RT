/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shape_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 22:33:02 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/05 22:36:14 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int	ft_pick_texture(t_texture *txt, double *uv)
{
	int		xy[2];

	if (txt->id == 100 || txt->id == 101 || txt->id == 102)
		return (ft_pick_proc_texture(uv, txt));
	xy[0] = (int)(uv[0] * (txt->width - 1)) + txt->stretch_z;
	xy[1] = (int)(uv[1] * (txt->height - 1));
	if (xy[0] >= txt->width)
		xy[0] = xy[0] % (txt->width - 1);
	if (xy[0] <= 0)
		xy[0] = (txt->width - 1) - (abs(xy[0]) % (txt->width - 1));
	if (xy[1] >= txt->height)
		xy[1] = xy[1] % (txt->height - 1);
	if (xy[1] <= 0)
		xy[1] = (txt->height - 1) - (abs(xy[1]) % (txt->height - 1));
	if (xy[0] >= txt->width)
		xy[0] = txt->width - 1;
	if (xy[1] >= txt->height)
		xy[1] = txt->height - 1;
	return (txt->buff[xy[0] + xy[1] * txt->width]);
}

int			ft_texture_plane(t_ray *ray, t_plane *pl)
{
	double		uv[2];
	t_vec4		inter_point;
	t_vec4		dir;

	inter_point = ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t), ray->origin);
	dir = ft_vec4_sub(inter_point, pl->point);
	uv[0] = ft_vec4_dot_product(pl->left, dir) / pl->texture.stretch_x;
	uv[1] = ft_vec4_dot_product(pl->forw, dir) / pl->texture.stretch_y;
	return (ft_pick_texture(&pl->texture, uv));
}

int			ft_texture_cylinder(t_ray *ray, t_cylinder *cyl)
{
	double		uv[2];
	t_vec4		p;
	t_vec4		cross;

	p = ft_vec4_sub(
	ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t), ray->origin), cyl->point);
	cross = ft_vec4_cross_product(cyl->axis, p);
	uv[0] = ft_vec4_dot_product(cross, cyl->left) / cyl->texture.stretch_x;
	uv[1] = ft_vec4_dot_product(p, cyl->axis) / cyl->texture.stretch_y;
	return (ft_pick_texture(&cyl->texture, uv));
}

int			ft_texture_cone(t_ray *ray, t_cone *cone)
{
	double		uv[2];
	t_vec4		p;
	t_vec4		cross;

	p = ft_vec4_sub(ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t), ray->origin),
			cone->center);
	cross = ft_vec4_cross_product(cone->axis, p);
	uv[0] = ft_vec4_dot_product(cross, cone->left) / cone->texture.stretch_x;
	uv[1] = ft_vec4_dot_product(p, cone->axis) / cone->texture.stretch_y;
	return (ft_pick_texture(&cone->texture, uv));
}

/*
** bigger value for disc->texture.stretch to stretch the texture
*/

int			ft_texture_disc(t_ray *ray, t_disc *disc)
{
	double		uv[2];
	t_vec4		inter_point;
	t_vec4		dir;

	inter_point = ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t), ray->origin);
	dir = ft_vec4_sub(inter_point, disc->point);
	uv[0] = ft_vec4_dot_product(disc->left, dir) / disc->texture.stretch_x;
	uv[1] = ft_vec4_dot_product(disc->forw, dir) / disc->texture.stretch_y;
	return (ft_pick_texture(&disc->texture, uv));
}
