/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:23:03 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/05 14:02:23 by arezouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static double		ft_specular(t_ray *ray, double dot_prod, t_vec4 nr,
		t_vec4 sh_ray)
{
	t_vec4			v;
	t_vec4			r;

	if (dot_prod == 0)
		return (0);
	v = ft_vec4_scalar(ray->dir, -1);
	r = ft_vec4_sub(ft_vec4_scalar(nr, 2 * dot_prod), sh_ray);
	return (pow(ft_min(ft_vec4_dot_product(r, v), 0), SPECULAR_POW));
}

static	void		ft_diffuse(t_shader_x *shx, double *dp_a, t_vec4 *ds,
		t_light *li)
{
	shx->diff.x += dp_a[0] * ds[0].x * li->r * dp_a[1];
	shx->diff.y += dp_a[0] * ds[0].y * li->g * dp_a[1];
	shx->diff.z += dp_a[0] * ds[0].z * li->b * dp_a[1];
}

int					ft_compute_shader(int color, t_shader_x *sh_x, t_data *data)
{
	t_shader		shader;

	shader.specular = ft_color_rgb_scalar(0xfff4d6,
			sh_x->spec.x, sh_x->spec.y, sh_x->spec.z);
	shader.diffuse = ft_color_rgb_scalar(color,
			sh_x->diff.x, sh_x->diff.y, sh_x->diff.z);
	shader.ambient = ft_color_rgb_scalar(color,
			data->ambient.x, data->ambient.y, data->ambient.z);
	return (ft_color_add(shader.specular,
						ft_color_add(shader.diffuse, shader.ambient)));
}

double				ft_distance_to_light(t_light *li, t_ray *sh_ray)
{
	if (li->type == POINT_LIGHT || li->type == SPOT_LIGHT)
		return (ft_vec4_mag(ft_vec4_sub(li->origin, sh_ray->origin)));
	else if (li->type == DIRECTIONAL_LIGHT)
		return (DISTANT_LIGHT);
	return (0);
}

/*
** rl : shadow_ray
** dp_a : 0 => dot_product, 1 => area_intensity
** ds diffuse && specular
** send ray to light
** loop through all lights
** if ray reached light, add value to shader
*/

t_shader_x			ft_ray_inter_lights(t_data *data, t_vec4 nr, t_ray *r,
		t_vec4 *d)
{
	t_ray			y;
	t_shader_x		s;
	t_list			*l;
	double			a[2];
	t_light			*i;

	l = data->light_list;
	s.diff = (t_vec4){0.0, 0.0, 0.0, 0.0};
	s.spec = (t_vec4){0.0, 0.0, 0.0, 0.0};
	while (l)
	{
		i = l->content;
		y = ft_get_shadow_ray(r, l->content);
		a[0] = ft_min(ft_vec4_dot_product(y.dir, nr), 0);
		if ((a[1] = ft_ray_inter_objs(data->scene, &y,
										ft_distance_to_light(i, &y), i)))
		{
			ft_diffuse(&s, a, d, i);
			s.spec.x += ft_specular(r, a[0], nr, y.dir) * d[1].x * i->r * a[1];
			s.spec.y += ft_specular(r, a[0], nr, y.dir) * d[1].y * i->g * a[1];
			s.spec.z += ft_specular(r, a[0], nr, y.dir) * d[1].z * i->b * a[1];
		}
		l = l->next;
	}
	return (s);
}
