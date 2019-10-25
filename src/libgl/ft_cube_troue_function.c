/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube_troue_function.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 14:25:26 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/04 11:09:55 by kdaou            ###   ########.fr       */
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

static t_vec4	ft_get_h_cube_normal(t_ray *ray)
{
	t_vec4	normal;
	t_vec4	p;

	p = ft_vec4_add(ray->origin, ft_vec4_scalar(ray->dir, ray->t));
	normal = (t_vec4){4 * pow(p.x, 3) - 10 * p.x, 4 *
	pow(p.y, 3) - 10 * p.y, 4 * pow(p.z, 3) - 10 * p.z, 0};
	normal = ft_vec4_normalize(normal);
	return (normal);
}

int				ft_h_cube_inter(t_ray *ray, t_h_cube *c)
{
	t_solve	s;

	s.tmp = pow(ray->dir.x, 4) + pow(ray->dir.y, 4) + pow(ray->dir.z, 4);
	s.a = 4.0 * (pow(ray->dir.x, 3) * ray->origin.x +
	pow(ray->dir.y, 3) * ray->origin.y + pow(ray->dir.z, 3) * ray->origin.z);
	s.b = 6.0 * (pow(ray->dir.x, 2) * pow(ray->origin.x, 2)
	+ pow(ray->dir.y, 2) * pow(ray->origin.y, 2)
			+ pow(ray->dir.z, 2) * pow(ray->origin.z, 2)) - 5.0
			* ft_vec4_dot_product(ray->dir, ray->dir);
	s.c = 4.0 * (pow(ray->origin.x, 3) * ray->dir.x + pow(ray->origin.y, 3)
	* ray->dir.y + pow(ray->origin.z, 3) * ray->dir.z) - 10.0
	* ft_vec4_dot_product(ray->dir, ray->origin);
	s.d = pow(ray->origin.x, 4) + pow(ray->origin.y, 4) + pow(ray->origin.z, 4)
	- 5.0 * ft_vec4_dot_product(ray->origin, ray->origin) + c->radius;
	s.a = s.a / s.tmp;
	s.b = s.b / s.tmp;
	s.c = s.c / s.tmp;
	s.d = s.d / s.tmp;
	return (ft_solve_equation(s, ray));
}

int				ft_h_cube_shader(t_data *data, t_ray *ray, t_h_cube *box)
{
	t_shader_x	sh_x;
	t_vec4		box_nor;
	t_vec4		ds[2];
	int			c;

	c = 0x0;
	box_nor = ft_get_h_cube_normal(ray);
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
