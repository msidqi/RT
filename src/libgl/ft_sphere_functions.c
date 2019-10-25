/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:20:01 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/06 08:39:47 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
** a=dot(B,B)
** b=2⋅dot(B,A−C)
** c=dot(A−C,A−C)−r2
** With the above parameterization, the quadratic formula is:
** t = (−b±b2−4ac) / (√2a)
*/

int				ft_sphere_inter(t_ray *ray, t_sphere *sp)
{
	double	t[2];
	double	discr;
	double	abc[3];
	t_vec4	k;

	k = ft_vec4_sub(ray->origin, sp->center);
	abc[0] = ft_vec4_dot_product(ray->dir, ray->dir);
	abc[1] = 2 * ft_vec4_dot_product(ray->dir, k);
	abc[2] = ft_vec4_dot_product(k, k) - sp->radius * sp->radius;
	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discr < 0)
		return (0);
	t[0] = (-abc[1] + sqrt(discr)) / (2 * abc[0]);
	t[1] = (-abc[1] - sqrt(discr)) / (2 * abc[0]);
	return (ft_pick_distance(t, ray, &sp->limits));
}

/*
** called foreach pixel
**	foreach light
**	get r_light and normal_sphere(calculate once)
**	check intersection with all objects,
** 		if : (hidden from light source by an obj) then :(its spec/diffuse += 0)
**	else : computed specular,
**		diffuse (light pixel, if : distance to light < (distance to obj == t))
**	ADD to return value
**
**	after foreach loop, add ambient
*/

static t_vec4	ft_get_sphere_normal(t_ray *ray, t_sphere *sp)
{
	return (ft_vec4_normalize(
		ft_vec4_sub(ft_vec4_add(ray->origin,
			ft_vec4_scalar(ray->dir, ray->t)), sp->center)));
}

int				ft_sphere_shader(t_data *data, t_ray *ray, t_sphere *sp)
{
	t_shader_x	sh_x;
	t_vec4		sp_nor;
	t_vec4		ds[2];
	int			c;

	c = 0x0;
	sp_nor = ft_get_sphere_normal(ray, sp);
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
		ft_color_add(sp->color, ft_texture_sphere(ray, sp))), &sh_x, data));
		return (ft_compute_shader(ft_color_add(sp->color, c), &sh_x, data));
}
