/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hyperboloid_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 12:05:20 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/05 13:15:24 by arezouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int				ft_hyperboloid_inter(t_ray *ray, t_hyper *hyper)
{
	t_vec4	dist;
	double	dsq;
	double	abc[3];
	double	t[2];

	abc[0] = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z -
		ray->dir.y * ray->dir.y;
	dist = ft_vec4_sub(ray->origin, hyper->center);
	abc[1] = 2 * (dist.x * ray->dir.x + dist.z * ray->dir.z -
			dist.y * ray->dir.y);
	abc[2] = (dist.x * dist.x + dist.z * dist.z - dist.y * dist.y) - hyper->k;
	dsq = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (dsq < 0)
		return (0);
	dsq = sqrt(dsq);
	t[0] = (-abc[1] + dsq) / (2 * abc[0]);
	t[1] = (-abc[1] - dsq) / (2 * abc[0]);
	return (ft_check_distance(t, ray));
}

static t_vec4	ft_get_hyperboloid_normal(t_ray *ray)
{
	t_vec4	normal;
	t_vec4	intersect_point;

	intersect_point = ft_vec4_add(ray->origin,
			ft_vec4_scalar(ray->dir, ray->t));
	normal = (t_vec4){2 * intersect_point.x, -2 * intersect_point.y,
		2 * intersect_point.z, 0};
	return (ft_vec4_normalize(normal));
}

int				ft_hyperboloid_shader(t_data *data, t_ray *ray, t_hyper *hyper)
{
	t_shader_x	sh_x;
	t_vec4		hyper_nor;
	t_vec4		ds[2];
	int			c;

	c = 0x0;
	hyper_nor = ft_get_hyperboloid_normal(ray);
	ds[0] = hyper->diffuse;
	ds[1] = (t_vec4){hyper->specular, hyper->specular,
	hyper->specular, hyper->specular};
	if ((hyper->ref.w == 3 || hyper->ref.w == 1) && ray->refl_depth > 0)
	{
		ray->refl_depth--;
		c = ft_reflected_ray(data, hyper_nor, ray, hyper->ref);
	}
	if (hyper->ref.w == 3)
		c = ft_color_add(c, ft_refracted_ray(data, hyper_nor, ray, hyper->ref));
	else if (hyper->ref.w == 2)
		c = ft_refracted_ray(data, hyper_nor, ray, hyper->ref);
	if ((hyper->ref.w >= 1 && hyper->ref.w <= 3) && hyper->ref.noshading)
		return (c);
	sh_x = ft_ray_inter_lights(data, hyper_nor, ray, ds);
	return (ft_compute_shader(ft_color_add(hyper->color, c), &sh_x, data));
}
