/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paraboloid_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:47:32 by arezouk           #+#    #+#             */
/*   Updated: 2019/10/04 11:08:02 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int		ft_solve_inter(double t, t_ray *ray)
{
	if (t > NEAR && t < ray->t)
	{
		ray->t = t;
		return (1);
	}
	return (0);
}

int				ft_paraboloid_inter(t_ray *ray, t_parab *parab)
{
	t_vec4	dist;
	double	dsq;
	double	abc[3];
	double	t[2];

	abc[0] = ft_vec4_dot_product(ray->dir, ray->dir) -
		pow(ft_vec4_dot_product(ray->dir, parab->normal), 2);
	dist = ft_vec4_sub(ray->origin, parab->center);
	abc[1] = 2 * (ft_vec4_dot_product(ray->dir, dist) -
			ft_vec4_dot_product(ray->dir, parab->normal)
			* (ft_vec4_dot_product(dist, parab->normal) + 2 * parab->k));
	abc[2] = ft_vec4_dot_product(dist, dist) -
		ft_vec4_dot_product(dist, parab->normal)
		* (ft_vec4_dot_product(dist, parab->normal) + 4 * parab->k);
	dsq = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (dsq < 0)
		return (0);
	dsq = sqrtf(dsq);
	t[0] = (-abc[1] + dsq) / (2 * abc[0]);
	t[1] = (-abc[1] - dsq) / (2 * abc[0]);
	t[0] = t[0] < t[1] && t[0] > NEAR ? t[0] : t[1];
	return (ft_solve_inter(t[0], ray));
}

static t_vec4	ft_get_paraboloid_normal(t_ray *ray, t_parab *parab)
{
	double	m;
	t_vec4	normal;
	t_vec4	intersect_point;

	intersect_point = ft_vec4_add(ray->origin,
			ft_vec4_scalar(ray->dir, ray->t));
	m = ft_vec4_dot_product(ft_vec4_sub(intersect_point,
				parab->center), parab->normal);
	normal = ft_vec4_sub(ft_vec4_sub(intersect_point, parab->center),
			ft_vec4_scalar(parab->normal, (m + parab->k)));
	return (ft_vec4_normalize(normal));
}

int				ft_paraboloid_shader(t_data *data, t_ray *ray, t_parab *parab)
{
	t_shader_x	sh_x;
	t_vec4		parab_nor;
	t_vec4		ds[2];
	int			c;

	c = 0x0;
	parab_nor = ft_get_paraboloid_normal(ray, parab);
	ds[0] = parab->diffuse;
	ds[1] = (t_vec4){parab->specular, parab->specular,
		parab->specular, parab->specular};
	if (parab->ref.w == 1 && ray->refl_depth > 0)
	{
		ray->refl_depth--;
		c = ft_reflected_ray(data, parab_nor, ray, parab->ref);
	}
	if (parab->ref.w == 2)
		c = ft_refracted_ray(data, parab_nor, ray, parab->ref);
	if ((parab->ref.w == 2 || parab->ref.w == 1) && parab->ref.noshading)
		return (c);
	sh_x = ft_ray_inter_lights(data, parab_nor, ray, ds);
	return (ft_compute_shader(ft_color_add(parab->color, c), &sh_x, data));
}
