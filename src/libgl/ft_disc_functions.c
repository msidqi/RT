/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_disc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 00:50:20 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/03 00:51:18 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int				ft_disc_inter(t_ray *ray, t_disc *disc)
{
	t_vec4	inter_point;

	if (!ft_plane_inter(ray, (t_plane *)disc))
		return (0);
	inter_point = ft_vec4_add(ray->origin, ft_vec4_scalar(ray->dir, ray->t));
	if (ft_vec4_mag(inter_point) < disc->radius)
		return (1);
	return (0);
}

static t_vec4	ft_get_disc_normal(t_ray *ray, t_disc *disc)
{
	return (ft_vec4_dot_product(ray->dir,
				disc->normal) < 0 ?
			disc->normal : ft_vec4_scalar(disc->normal, -1));
}

int				ft_disc_shader(t_data *data, t_ray *ray, t_disc *disc)
{
	t_shader_x	sh_x;
	t_vec4		disc_nor;
	t_vec4		ds[2];
	int			c;

	c = 0x0;
	disc_nor = ft_get_disc_normal(ray, disc);
	ds[0] = disc->diffuse;
	ds[1] = (t_vec4){disc->specular, disc->specular,
			disc->specular, disc->specular};
	if (disc->ref.w == 1 && ray->refl_depth > 0)
	{
		ray->refl_depth--;
		c = ft_reflected_ray(data, disc_nor, ray, disc->ref);
		if (disc->ref.noshading)
			return (c);
	}
	if (disc->ref.w == 2)
		c = ft_refracted_ray(data, disc_nor, ray, disc->ref);
	sh_x = ft_ray_inter_lights(data, disc_nor, ray, ds);
	if (disc->texture.id > -1)
		return (ft_compute_shader(ft_color_add(c,
		ft_color_add(disc->color, ft_texture_disc(ray, disc))), &sh_x, data));
		return (ft_compute_shader(ft_color_add(disc->color, c), &sh_x, data));
}
