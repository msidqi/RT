/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ellipsoid_function.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 11:53:44 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/04 12:12:21 by kdaou            ###   ########.fr       */
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

int				ft_ellipsoid_inter(t_ray *ray, t_ellipsoid *sp)
{
	t_vec4	oc;
	t_solve	s;
	double	t[2];

	oc = ft_vec4_sub(ray->origin, sp->center);
	s.a = ((ray->dir.x * ray->dir.x) / (sp->axis.x * sp->axis.x)) +
		((ray->dir.y * ray->dir.y) / (sp->axis.y * sp->axis.y)) +
		((ray->dir.z * ray->dir.z) / (sp->axis.z * sp->axis.z));
	s.b = ((2.0 * oc.x * ray->dir.x) / (sp->axis.x * sp->axis.x))
		+ ((2.0 * oc.y * ray->dir.y) / (sp->axis.y * sp->axis.y))
		+ ((2.0 * oc.z * ray->dir.z) / (sp->axis.z * sp->axis.z));
	s.c = ((oc.x * oc.x) / (sp->axis.x * sp->axis.x))
		+ ((oc.y * oc.y) / (sp->axis.y * sp->axis.y))
		+ ((oc.z * oc.z) / (sp->axis.z * sp->axis.z))
		- 1.0;
	s.tmp = s.b * s.b - 4 * s.a * s.c;
	if (s.tmp < 0 || s.a == 0 || s.b == 0 || s.c == 0)
		return (0);
	s.tmp = sqrt(s.tmp);
	t[0] = (-s.b + s.tmp) / (2 * s.a);
	t[1] = (-s.b - s.tmp) / (2 * s.a);
	t[0] = t[0] < t[1] && t[0] > NEAR ? t[0] : t[1];
	return (ft_solve_inter(t[0], ray));
}

static t_vec4	ft_get_ellipsoid_normal(t_ray *ray, t_ellipsoid *sp)
{
	t_vec4	p;
	t_vec4	normal;

	p = ft_vec4_add(ray->origin, ft_vec4_scalar(ray->dir, ray->t));
	normal = ft_vec4_sub(p, sp->center);
	normal.x = 2.0 * normal.x / (sp->axis.x * sp->axis.x);
	normal.y = 2.0 * normal.y / (sp->axis.y * sp->axis.y);
	normal.z = 2.0 * normal.z / (sp->axis.z * sp->axis.z);
	normal.w = 0.0;
	normal = ft_vec4_normalize(normal);
	return (normal);
}

int				ft_ellipsoid_shader(t_data *data, t_ray *ray, t_ellipsoid *sp)
{
	t_shader_x	sh_x;
	t_vec4		sp_nor;
	t_vec4		ds[2];
	int			c;

	c = 0x0;
	sp_nor = ft_get_ellipsoid_normal(ray, sp);
	ds[0] = sp->diffuse;
	ds[1] = (t_vec4){sp->specular, sp->specular,
			sp->specular, sp->specular};
	if (sp->ref.w == 1 && ray->refl_depth > 0)
	{
		ray->refl_depth--;
		c = ft_reflected_ray(data, sp_nor, ray, sp->ref);
	}
	if (sp->ref.w == 2)
		c = ft_refracted_ray(data, sp_nor, ray, sp->ref);
	if ((sp->ref.w == 2 || sp->ref.w == 1) && sp->ref.noshading)
		return (c);
	sh_x = ft_ray_inter_lights(data, sp_nor, ray, ds);
	return (ft_compute_shader(ft_color_add(sp->color, c), &sh_x, data));
}
