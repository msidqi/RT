/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 12:08:08 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/04 12:13:29 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
** det : disc[0] discriminant
** invdet : disc[1] invert discriminant
** t0 : disc[2] solution
** u : disc[3]
** v : disc[4]
**
** diff_vert[0] : v0v1
** diff_vert[0] : v0v2
** diff_vert[0] : pvec
** diff_vert[0] : tvec
** diff_vert[0] : qvec
*/

static int		ft_solve_inter(double t, t_ray *ray)
{
	if (t > NEAR && t < ray->t)
	{
		ray->t = t;
		return (1);
	}
	return (0);
}

int				ft_triangle_inter(t_ray *ray, t_triangle *triangle)
{
	t_vec4	diff_vert[5];
	double	disc[5];

	diff_vert[0] = ft_vec4_sub(triangle->vertex1, triangle->vertex0);
	diff_vert[1] = ft_vec4_sub(triangle->vertex2, triangle->vertex0);
	diff_vert[2] = ft_vec4_cross_product(ray->dir, diff_vert[1]);
	disc[0] = ft_vec4_dot_product(diff_vert[0], diff_vert[2]);
	if (disc[0] > NEAR)
	{
		disc[1] = 1 / disc[0];
		diff_vert[3] = ft_vec4_sub(ray->origin, triangle->vertex0);
		disc[3] = ft_vec4_dot_product(diff_vert[3], diff_vert[2]) * disc[1];
		if (disc[3] < 0 || disc[3] > 1)
			return (0);
		diff_vert[4] = ft_vec4_cross_product(diff_vert[3], diff_vert[0]);
		disc[4] = ft_vec4_dot_product(ray->dir, diff_vert[4]) * disc[1];
		if (disc[4] < 0 || disc[3] + disc[4] > 1)
			return (0);
		disc[2] = ft_vec4_dot_product(diff_vert[1], diff_vert[4]) * disc[1];
		return (ft_solve_inter(disc[2], ray));
	}
	return (0);
}

static t_vec4	ft_get_triangle_normal(t_triangle *triangle)
{
	t_vec4	u;
	t_vec4	v;

	u = ft_vec4_sub(triangle->vertex1, triangle->vertex0);
	v = ft_vec4_sub(triangle->vertex2, triangle->vertex0);
	return (ft_vec4_normalize(ft_vec4_cross_product(u, v)));
}

int				ft_triangle_shader(t_data *data, t_ray *ray,
		t_triangle *triangle)
{
	t_shader_x	sh_x;
	t_vec4		triangle_nor;
	t_vec4		ds[2];
	int			c;

	c = 0x0;
	triangle_nor = ft_get_triangle_normal(triangle);
	ds[0] = triangle->diffuse;
	ds[1] = (t_vec4){triangle->specular, triangle->specular,
		triangle->specular, triangle->specular};
	if ((triangle->ref.w == 3 || triangle->ref.w == 1) && ray->refl_depth > 0)
	{
		ray->refl_depth--;
		c = ft_reflected_ray(data, triangle_nor, ray, triangle->ref);
	}
	if (triangle->ref.w == 3)
		c = ft_color_add(c,
		ft_refracted_ray(data, triangle_nor, ray, triangle->ref));
	else if (triangle->ref.w == 2)
		c = ft_refracted_ray(data, triangle_nor, ray, triangle->ref);
	if ((triangle->ref.w >= 1 && triangle->ref.w <= 3) &&
			triangle->ref.noshading)
		return (c);
	sh_x = ft_ray_inter_lights(data, triangle_nor, ray, ds);
	return (ft_compute_shader(ft_color_add(triangle->color, c), &sh_x, data));
}
