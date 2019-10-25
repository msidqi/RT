/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:15:56 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/04 11:25:24 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
** 1/ Vec1 ⋅ Vec2 = ||Vec1| * ||Vec2|| * cosθ ;
**										where θ is angle between the vectors
** Vec1 == Vector from cone center to intersection point
**									 		which is the vector (P - Center);
** Vec2 == normalized Axis;
** 2/ P = Origin + t * Dir;
** 3/ Solve for t;
**
** a = (Dir ⋅ Axis)**2 - cos**2(θ)
** b = 2 * ((Dir ⋅ Axis)(CO ⋅ Axis) - Dir ⋅ CO * cos**2(θ))
** c = (CO ⋅ Axis)**2 - CO ⋅ CO * cos**2(θ)
*/

int				ft_cone_inter(t_ray *ray, t_cone *co)
{
	double	abc[3];
	double	t[2];
	double	discr_k[2];
	t_vec4	x;

	discr_k[1] = 1 + pow(tan(co->half_angle), 2);
	x = ft_vec4_sub(ray->origin, co->center);
	abc[0] = ft_vec4_dot_product(ray->dir, ray->dir) -
		discr_k[1] * pow(ft_vec4_dot_product(ray->dir, co->axis), 2);
	abc[1] = 2 * (ft_vec4_dot_product(ray->dir, x) - discr_k[1] *
	ft_vec4_dot_product(ray->dir, co->axis) * ft_vec4_dot_product(x, co->axis));
	abc[2] = ft_vec4_dot_product(x, x) - discr_k[1]
	* pow(ft_vec4_dot_product(x, co->axis), 2);
	discr_k[0] = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discr_k[0] < 0)
		return (0);
	t[0] = (-abc[1] + sqrt(discr_k[0])) / (2 * abc[0]);
	t[1] = (-abc[1] - sqrt(discr_k[0])) / (2 * abc[0]);
	if (co->limits.islimited && !ft_islimited(ray, t, (t_cylinder *)co))
		return (false);
	return (ft_pick_distance(t, ray, &co->limits));
}

static t_vec4	ft_get_cone_normal(t_ray *ray, t_vec4 axis,
		t_vec4 c, double half_angle)
{
	t_vec4	p_sub_c;

	p_sub_c = ft_vec4_sub(ft_vec4_add(ray->origin,
				ft_vec4_scalar(ray->dir, ray->t)), c);
	return (ft_vec4_normalize(ft_vec4_sub(p_sub_c,
					ft_vec4_scalar(axis,
						(1 + half_angle * half_angle)
						* ft_vec4_dot_product(p_sub_c, axis)))));
}

int				ft_cone_shader(t_data *data, t_ray *ray, t_cone *co)
{
	t_shader_x	sh_x;
	t_vec4		co_nor;
	t_vec4		ds[2];
	int			c;

	c = 0x0;
	co_nor = ft_get_cone_normal(ray, co->axis, co->center, co->half_angle);
	ds[0] = co->diffuse;
	ds[1] = (t_vec4){co->specular, co->specular, co->specular, co->specular};
	if ((co->ref.w == 3 || co->ref.w == 1) && ray->refl_depth > 0)
	{
		ray->refl_depth--;
		c = ft_reflected_ray(data, co_nor, ray, co->ref);
	}
	if (co->ref.w == 3)
		c = ft_color_add(c, ft_refracted_ray(data, co_nor, ray, co->ref));
	else if (co->ref.w == 2)
		c = ft_refracted_ray(data, co_nor, ray, co->ref);
	if ((co->ref.w >= 1 && co->ref.w <= 3) && co->ref.noshading)
		return (c);
	sh_x = ft_ray_inter_lights(data, co_nor, ray, ds);
	if (co->texture.id > -1)
		return (ft_compute_shader(ft_color_add(c,
		ft_color_add(co->color, ft_texture_cone(ray, co))), &sh_x, data));
		return (ft_compute_shader(ft_color_add(co->color, c), &sh_x, data));
}
