/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reflected_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:23:03 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/06 16:30:03 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

const t_obj_function g_t_obj_functions[13] =
{
	{ SPHERE, &ft_sphere_inter, &ft_sphere_shader },
	{ PLANE, &ft_plane_inter, &ft_plane_shader },
	{ CONE, &ft_cone_inter, &ft_cone_shader },
	{ CYLINDER, &ft_cylinder_inter, &ft_cylinder_shader },
	{ BOX, &ft_box_inter, &ft_box_shader },
	{ DISC, &ft_disc_inter, &ft_disc_shader },
	{ HSPHERE, &ft_hemisphere_inter, &ft_hemisphere_shader},
	{ TORUS, &ft_torus_inter, &ft_torus_shader},
	{ H_CUBE, &ft_h_cube_inter, &ft_h_cube_shader},
	{ PARAB, &ft_paraboloid_inter, &ft_paraboloid_shader},
	{ HYPER, &ft_hyperboloid_inter, &ft_hyperboloid_shader},
	{ ELLIPSOID, &ft_ellipsoid_inter, &ft_ellipsoid_shader},
	{ TRIANGLE, &ft_triangle_inter, &ft_triangle_shader},
};

/*
** step 3 -loop check if ray is blocked by any another
** 							object in scene, towards light source.
*/

double				ft_ray_inter_objs(t_list *list, t_ray *sh_ray,
		double distance_to_light, t_light *li)
{
	t_list			*scene;
	unsigned int	i;

	scene = list;
	while (scene != NULL)
	{
		sh_ray->t = FAR;
		i = -1;
		while (++i < (unsigned int)STATIC_ARRAY_SIZE(g_t_obj_functions))
		{
			if (g_t_obj_functions[i].type == scene->content_size &&
					g_t_obj_functions[i].call(sh_ray, scene->content) &&
					distance_to_light > ft_vec4_mag(ft_vec4_scalar(sh_ray->dir,
							sh_ray->t)))
				return (0);
		}
		scene = scene->next;
	}
	return (ft_light_intensity(list, li, &sh_ray->origin, &sh_ray->dir));
}

/*
** the return means that the ray reached the light
*/

int					ft_reflected_ray(t_data *data, t_vec4 nr, t_ray *ray,
		t_ref refl)
{
	unsigned int	i;
	t_list			*s;
	int				color;
	t_ray			refl_ray;

	color = 0x222222;
	refl_ray.origin = ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t),
			ray->origin);
	refl_ray.dir = ft_vec4_normalize(ft_vec4_add(ft_vec4_scalar(nr,
					-2 * ft_vec4_dot_product(ray->dir, nr)), ray->dir));
	refl_ray.t = FAR;
	refl_ray.refl_depth = ray->refl_depth;
	s = data->scene;
	while (s != NULL)
	{
		i = -1;
		while (++i < (unsigned int)STATIC_ARRAY_SIZE(g_t_obj_functions))
			if (g_t_obj_functions[i].type == s->content_size
				&& g_t_obj_functions[i].call(&refl_ray, s->content))
				color = g_t_obj_functions[i].call2(data, &refl_ray, s->content);
		s = s->next;
	}
	return (ft_color_rgb_scalar(color, refl.x, refl.y, refl.z));
}

/*
** reflection = -2 * (V.N) * N + V
*/

static t_ray		ft_ray_create(t_ray *ray, t_vec4 r)
{
	t_ray	new;
	t_vec4	tmp;

	tmp = ft_vec4_scalar(ray->dir, ray->t);
	new.origin = ft_vec4_add(ray->origin, tmp);
	new.dir = ft_vec4_normalize(r);
	new.t = FAR;
	new.refl_depth = ray->refl_depth;
	return (new);
}

static t_vec4		ft_reflection_vector(t_vec4 dir, t_vec4 normal, t_ref refr)
{
	t_vec4	r;
	double	dot;
	double	n;
	double	c[2];
	t_vec4	nref;

	nref = normal;
	dot = ft_vec4_dot_product(dir, normal);
	n = 1 / fabs(refr.n);
	if (dot < 0)
		dot = -dot;
	else
	{
		n = fabs(refr.n);
		nref = ft_vec4_scalar(normal, -1);
	}
	c[0] = ft_vec4_dot_product(nref, dir);
	c[1] = sqrt(ft_min(0, 1 - (n * n) * (1 - (dot * dot))));
	r = ft_vec4_add(ft_vec4_scalar(dir, n),
			ft_vec4_scalar(nref, n * c[0] - c[1]));
	r = ft_vec4_normalize(r);
	return (r);
}

int					ft_refracted_ray(t_data *data, t_vec4 normal,
		t_ray *ray, t_ref refr)
{
	t_vec4			r;
	t_ray			refracted_ray;
	int				color;
	t_list			*s;
	unsigned int	i;

	color = 0x0;
	r = ft_reflection_vector(ray->dir, normal, refr);
	refracted_ray = ft_ray_create(ray, r);
	s = data->scene;
	while (s != NULL)
	{
		i = -1;
		while (++i < (unsigned int)STATIC_ARRAY_SIZE(g_t_obj_functions))
			if (g_t_obj_functions[i].type == s->content_size
					&& g_t_obj_functions[i].call(&refracted_ray, s->content))
				color = g_t_obj_functions[i].call2(data, &refracted_ray,
						s->content);
		s = s->next;
	}
	return (ft_color_rgb_scalar(color, refr.x, refr.y, refr.z));
}
