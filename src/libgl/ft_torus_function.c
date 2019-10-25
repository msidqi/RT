/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_torus_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:34:08 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/05 15:38:37 by arezouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int		ft_solve_equation(t_solve s, t_ray *ray)
{
	double	x[4];
	int		res;
	int		i;
	double	t;

	i = -1;
	t = FAR;
	res = ft_solve_equation_4(s, x);
	if (res == 0)
		return (0);
	while (++i < res)
	{
		if (x[i] < t && x[i] > NEAR)
			t = x[i];
	}
	if (t > NEAR && t < ray->t)
	{
		ray->t = t;
		return (1);
	}
	return (0);
}

static t_vec4	ft_get_torus_normal(t_ray *ray, t_torus *t)
{
	t_vec4	p;
	t_vec4	a;
	t_vec4	normal;
	double	dot;
	double	m;

	p = ft_vec4_add(ray->origin, ft_vec4_scalar(ray->dir, ray->t));
	dot = ft_vec4_dot_product(ft_vec4_sub(p, t->center), t->axis);
	a = ft_vec4_sub(p, ft_vec4_scalar(t->axis, dot));
	m = sqrt(t->sr * t->sr - dot * dot);
	normal = ft_vec4_normalize(ft_vec4_sub(p, ft_vec4_sub(a,
			ft_vec4_scalar(ft_vec4_sub(t->center, a), m / (t->br + m)))));
	return (normal);
}

int				ft_torus_inter(t_ray *ray, t_torus *t)
{
	t_solve	s;
	t_vec4	oc;

	oc = ft_vec4_sub(ray->origin, t->center);
	s.m = 1 - pow(ft_vec4_dot_product(t->axis, ray->dir), 2);
	s.n = 2 * (ft_vec4_dot_product(oc, ray->dir) -
	ft_vec4_dot_product(t->axis, oc) * ft_vec4_dot_product(t->axis, ray->dir));
	s.o = ft_vec4_dot_product(oc, oc) -
		pow(ft_vec4_dot_product(t->axis, oc), 2);
	s.p = ft_vec4_dot_product(oc, oc) + t->br * t->br - t->sr * t->sr;
	s.a = 4 * ft_vec4_dot_product(oc, ray->dir);
	s.b = 2 * s.p + s.a * s.a * 0.25 - 4 * s.m * t->br * t->br;
	s.c = s.a * s.p - 4 * s.n * t->br * t->br;
	s.d = s.p * s.p - 4 * t->br * t->br * s.o;
	return (ft_solve_equation(s, ray));
}

int				ft_torus_shader(t_data *data, t_ray *ray, t_torus *t)
{
	t_shader_x	sh_x;
	t_vec4		t_nor;
	t_vec4		ds[2];
	int			c;

	c = 0x0;
	t_nor = ft_get_torus_normal(ray, t);
	ds[0] = t->diffuse;
	ds[1] = (t_vec4){t->specular, t->specular, t->specular, t->specular};
	if ((t->ref.w == 3 || t->ref.w == 1) && ray->refl_depth > 0)
	{
		ray->refl_depth--;
		c = ft_reflected_ray(data, t_nor, ray, t->ref);
	}
	if (t->ref.w == 3)
		c = ft_color_add(c, ft_refracted_ray(data, t_nor, ray, t->ref));
	else if (t->ref.w == 2)
		c = ft_refracted_ray(data, t_nor, ray, t->ref);
	if ((t->ref.w >= 1 && t->ref.w <= 3) && t->ref.noshading)
		return (c);
	sh_x = ft_ray_inter_lights(data, t_nor, ray, ds);
	return (ft_compute_shader(ft_color_add(t->color, c), &sh_x, data));
}
