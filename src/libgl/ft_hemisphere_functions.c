/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hemisphere_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 11:00:24 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/04 12:01:25 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int		ft_calcule_intersection(t_ray *ray, double t0, double t1)
{
	double	t;

	if (t0 < 0.0)
		t0 = t1;
	if (t1 < 0.0)
		t1 = t0;
	t = ft_max(t0, t1);
	if (t > NEAR && t < ray->t)
	{
		ray->t = t;
		return (1);
	}
	return (0);
}

int				ft_hemisphere_inter(t_ray *ray, t_h_sphere *hp)
{
	double	dsq;
	t_vec4	dist;
	double	abc[3];
	double	t[2];
	t_vec4	v2;

	abc[0] = ft_vec4_dot_product(ray->dir, ray->dir);
	dist = ft_vec4_sub(ray->origin, hp->center);
	abc[1] = 2 * ft_vec4_dot_product(dist, ray->dir);
	abc[2] = ft_vec4_dot_product(dist, dist) - hp->radius * hp->radius;
	dsq = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (dsq < 0)
		return (0);
	dsq = sqrt(dsq);
	t[0] = (-abc[1] + dsq) / (2 * abc[0]);
	t[1] = (-abc[1] - dsq) / (2 * abc[0]);
	v2 = ft_vec4_add(ray->origin, ft_vec4_sub(ft_vec4_scalar(ray->dir, t[0]),
				hp->center));
	if (ft_vec4_dot_product(hp->normal, v2) > 0.0)
		t[0] = -1.0;
	v2 = ft_vec4_add(ray->origin, ft_vec4_sub(ft_vec4_scalar(ray->dir, t[1]),
				hp->center));
	if (ft_vec4_dot_product(hp->normal, v2) > 0.0)
		t[1] = -1.0;
	return (ft_calcule_intersection(ray, t[0], t[1]));
}

static t_vec4	ft_get_hemisphere_normal(t_ray *ray, t_h_sphere *hp)
{
	return (ft_vec4_normalize(
		ft_vec4_sub(ft_vec4_add(ray->origin,
			ft_vec4_scalar(ray->dir, ray->t)), hp->center)));
}

int				ft_hemisphere_shader(t_data *data, t_ray *ray, t_h_sphere *sp)
{
	t_shader_x	sh_x;
	t_vec4		sp_nor;
	t_vec4		ds[2];
	int			c;

	c = 0x0;
	sp_nor = ft_get_hemisphere_normal(ray, sp);
	ds[0] = sp->diffuse;
	ds[1] = (t_vec4){sp->specular, sp->specular, sp->specular, sp->specular};
	if ((sp->ref.w == 3 || sp->ref.w == 1) && ray->refl_depth > 0)
	{
		ray->refl_depth--;
		c = ft_reflected_ray(data, sp_nor, ray, sp->ref);
	}
	if (sp->ref.w == 3)
		c = ft_color_add(c, ft_refracted_ray(data, sp_nor, ray, sp->ref));
	else if (sp->ref.w == 2)
		c = ft_refracted_ray(data, sp_nor, ray, sp->ref);
	if ((sp->ref.w >= 1 && sp->ref.w <= 3) && sp->ref.noshading)
		return (c);
	sh_x = ft_ray_inter_lights(data, sp_nor, ray, ds);
	if (sp->texture.id > -1)
		return (ft_compute_shader(ft_color_add(c,
		ft_color_add(sp->color, ft_texture_hemisphere(ray, sp))), &sh_x, data));
		return (ft_compute_shader(ft_color_add(sp->color, c), &sh_x, data));
}
