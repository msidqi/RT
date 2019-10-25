/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_box_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:53:00 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/05 21:54:53 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
** t[4] => t[0]  x_min    t[1] x_max   t[2] y_min   t[3] y_max
*/

static t_vec4	ft_vec4_inv(t_vec4 v)
{
	t_vec4	new;

	new.x = 1 / v.x;
	new.y = 1 / v.y;
	new.z = 1 / v.z;
	new.w = 0;
	return (new);
}

static int		ft_get_t_bounds(double *t, t_vec4 vec, t_ray *ray, t_box *box)
{
	int	signe[3];

	signe[0] = (vec.x < 0.00001);
	signe[1] = (vec.y < 0.00001);
	signe[2] = (vec.z < 0.00001);
	t[0] = (((signe[0] ? box->bmax.x : box->bmin.x) - ray->origin.x) * vec.x);
	t[1] = (((signe[0] ? box->bmin.x : box->bmax.x) - ray->origin.x) * vec.x);
	t[2] = (((signe[1] ? box->bmax.y : box->bmin.y) - ray->origin.y) * vec.y);
	t[3] = (((signe[1] ? box->bmin.y : box->bmax.y) - ray->origin.y) * vec.y);
	if (t[0] > t[3] || t[2] > t[1])
		return (0);
	if (t[2] > t[0])
		t[0] = t[2];
	if (t[3] < t[1])
		t[1] = t[3];
	t[4] = (((signe[2] ? box->bmax.z : box->bmin.z) - ray->origin.z) * vec.z);
	t[5] = (((signe[2] ? box->bmin.z : box->bmax.z) - ray->origin.z) * vec.z);
	if ((t[0] > t[5]) || t[4] > t[1])
		return (0);
	if (t[4] > t[0])
		t[0] = t[4];
	if (t[5] < t[1])
		t[1] = t[5];
	return (ft_check_distance(t, ray));
}

int				ft_box_inter(t_ray *ray, t_box *sp)
{
	double	t[6];
	t_vec4	inv_dir;
	int		d;

	inv_dir = ft_vec4_inv(ray->dir);
	d = ft_get_t_bounds(t, inv_dir, ray, sp);
	return (d);
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

static t_vec4	ft_get_box_normal(t_ray *ray, t_box *sp)
{
	t_vec4	p;
	t_vec4	c;
	t_vec4	d;

	c = ft_vec4_scalar(ft_vec4_add(sp->bmin, sp->bmax), 0.5);
	p = ft_vec4_sub(ft_vec4_add(ray->origin,
	ft_vec4_scalar(ray->dir, ray->t)), c);
	d = (t_vec4){fabs(sp->bmin.x - sp->bmax.x) / 2,
							fabs(sp->bmin.y - sp->bmax.y) / 2,
							fabs(sp->bmin.z - sp->bmax.z) / 2
							, 0};
	return (ft_vec4_normalize(
		(t_vec4){(int)(p.x / d.x * 1.000001), (int)(p.y / d.y * 1.000001),
		(int)(p.z / d.z * 1.000001), 0}));
}

int				ft_box_shader(t_data *data, t_ray *ray, t_box *box)
{
	t_shader_x	sh_x;
	t_vec4		box_nor;
	t_vec4		ds[2];
	int			c;

	c = 0x0;
	box_nor = ft_get_box_normal(ray, box);
	ds[0] = box->diffuse;
	ds[1] = (t_vec4){box->specular, box->specular,
			box->specular, box->specular};
	if ((box->ref.w == 3 || box->ref.w == 1) && ray->refl_depth > 0)
	{
		ray->refl_depth--;
		c = ft_reflected_ray(data, box_nor, ray, box->ref);
	}
	if (box->ref.w == 3)
		c = ft_color_add(c, ft_refracted_ray(data, box_nor, ray, box->ref));
	else if (box->ref.w == 2)
		c = ft_refracted_ray(data, box_nor, ray, box->ref);
	if ((box->ref.w >= 1 && box->ref.w <= 3) && box->ref.noshading)
		return (c);
	sh_x = ft_ray_inter_lights(data, box_nor, ray, ds);
	return (ft_compute_shader(ft_color_add(box->color, c), &sh_x, data));
}
