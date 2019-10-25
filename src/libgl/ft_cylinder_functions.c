/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:11:54 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/05 20:59:49 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
** const = ray.origin - cylinder.point;
** a = ray.dir ⋅ ray.dir - (ray.dir ⋅ axis)**2
**
** b/2 = ray.dir ⋅ const - (ray.dir ⋅ axiis) * (const ⋅ axis)
**
** c = const ⋅ const - (const ⋅ axis)**2 - radius**2
*/

int				ft_cylinder_inter(t_ray *ray, t_cylinder *cyl)
{
	double t[2];
	double discr;
	double abc[3];
	t_vec4 tmp;

	tmp = ft_vec4_sub(ray->origin, cyl->point);
	abc[0] = ft_vec4_dot_product(ray->dir, ray->dir)
		- pow(ft_vec4_dot_product(ray->dir, cyl->axis), 2);
	abc[1] = (ft_vec4_dot_product(ray->dir, tmp)
			- ft_vec4_dot_product(ray->dir, cyl->axis)
			* ft_vec4_dot_product(tmp, cyl->axis)) * 2;
	abc[2] = ft_vec4_dot_product(tmp, tmp) - pow(ft_vec4_dot_product(tmp,
								cyl->axis), 2) - cyl->radius * cyl->radius;
	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discr < 0)
		return (0);
	t[0] = (-abc[1] + sqrt(discr)) / (2 * abc[0]);
	t[1] = (-abc[1] - sqrt(discr)) / (2 * abc[0]);
	if (cyl->limits.islimited && !ft_islimited(ray, t, cyl))
		return (false);
	return (ft_pick_distance(t, ray, &cyl->limits));
}

/*
** 1- P = intersection point = O + t * D;
**
** 2- A = C + m * axis; => where vector (P - A) is
** 		perpendicular to normal = the point where ((P - A) ⋅ axis) is 0;
**
** 3- (P - (C + m * axis)) ⋅ axis == 0
** (P - C - m * axis) ⋅ axis == 0
** (P - C) ⋅ axis == m * (axis ⋅ axis)     &&    (axis ⋅ axis == 1)
** m == (P - C) ⋅ axis;
**
** ==> A == C + ((P - C) ⋅ axis) * axis
**
**
** normal == P - A;
** normal == O + t * D - (C + ((P - C) ⋅ axis) * axis)
**
** normal == O + t * D - C - ((P - C) ⋅ axis) * axis)
** normal = P - C - ((P - C) . axe ) * axe;
**
** => normal = (sh_ray.origin) - (cylinder.point
** 			+ ft_vec4_dot_product(ft_vec4_sub(sh_ray.origin, cylinder.point),
**												cylinder.axis) * cylinder.axis)
*/

static t_vec4	ft_get_cylinder_normal(t_ray *ray, t_vec4 axis, t_vec4 c)
{
	t_vec4	p_sub_c;
	double	m;
	t_vec4	x;

	x = ft_vec4_sub(ray->origin, c);
	m = ft_vec4_dot_product(ray->dir, ft_vec4_scalar(axis, ray->t)) +
		ft_vec4_dot_product(x, axis);
	p_sub_c = ft_vec4_sub(ft_vec4_add(ray->origin,
				ft_vec4_scalar(ray->dir, ray->t)), c);
	return (ft_vec4_normalize(ft_vec4_sub(p_sub_c, ft_vec4_scalar(axis, m))));
}

int				ft_cylinder_shader(t_data *data, t_ray *ray, t_cylinder *cy)
{
	t_shader_x	sh_x;
	t_vec4		cyl_nor;
	t_vec4		ds[2];
	int			c;

	c = 0x0;
	cyl_nor = ft_get_cylinder_normal(ray, cy->axis, cy->point);
	ds[0] = cy->diffuse;
	ds[1] = (t_vec4){cy->specular, cy->specular, cy->specular, cy->specular};
	if ((cy->ref.w == 3 || cy->ref.w == 1) && ray->refl_depth > 0)
	{
		ray->refl_depth--;
		c = ft_reflected_ray(data, cyl_nor, ray, cy->ref);
	}
	if (cy->ref.w == 3)
		c = ft_color_add(c, ft_refracted_ray(data, cyl_nor, ray, cy->ref));
	else if (cy->ref.w == 2)
		c = ft_refracted_ray(data, cyl_nor, ray, cy->ref);
	if ((cy->ref.w >= 1 && cy->ref.w <= 3) && cy->ref.noshading)
		return (c);
	sh_x = ft_ray_inter_lights(data, cyl_nor, ray, ds);
	if (cy->texture.id > -1)
		return (ft_compute_shader(ft_color_add(c,
		ft_color_add(cy->color, ft_texture_cylinder(ray, cy))), &sh_x, data));
		return (ft_compute_shader(ft_color_add(cy->color, c), &sh_x, data));
}
