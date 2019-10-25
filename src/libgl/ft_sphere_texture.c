/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 22:40:45 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/05 22:42:40 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int	ft_pick_sphere_texture(t_texture *txt, double *uv)
{
	int		xy[2];
	int		odd;
	int		edge;

	if (txt->id == 100)
	{
		xy[0] = uv[0] * txt->stretch_x;
		xy[1] = uv[1] * txt->stretch_y;
		odd = (xy[0] & 0x01) == (xy[1] & 0x01);
		edge = ((txt->stretch_x * uv[0] - xy[0] < 0.1) && odd)
						|| (txt->stretch_y * uv[1] - xy[1] < 0.1);
		return (edge ? 0xFFFFFF : 0x933A16);
	}
	else if (txt->id > -1)
	{
		xy[0] = uv[0] * txt->width;
		xy[1] = uv[1] * txt->height;
	}
	return (txt->buff[xy[0] + xy[1] * txt->width]);
}

int			ft_texture_sphere(t_ray *ray, t_sphere *sp)
{
	double	phi_theta[2];
	double	uv[2];
	t_vec4	p;

	p = ft_vec4_sub(sp->center,
	ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t), ray->origin));
	phi_theta[0] = atan2(p.z, p.x);
	phi_theta[1] = acos(-(p.y) / sp->radius);
	uv[0] = ((phi_theta[0] + PI) / (2 * PI));
	uv[1] = 1 - phi_theta[1] / PI;
	if (uv[0] < 0)
		uv[0] = 0;
	if (uv[1] < 0)
		uv[1] = 0;
	if (uv[0] > 1.0)
		uv[0] = 1.0;
	if (uv[1] > 1.0)
		uv[1] = 1.0;
	return (ft_pick_sphere_texture(&sp->texture, uv));
}

/*
** angle[0] = phi || angle[1] = theta
** phi = angle between x axis and X around sphere latitude
** theta angle between y axis and X long the longititude
** axe[0] = x || axe [1] = y
*/

int			ft_texture_hemisphere(t_ray *ray, t_h_sphere *sp)
{
	double	phi_theta[2];
	double	u;
	double	v;
	int		xy[2];
	t_vec4	exe;

	phi_theta[0] = 0;
	phi_theta[1] = 0;
	exe = ft_vec4_sub(sp->center, ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t),
				ray->origin));
	phi_theta[0] = atan2(exe.z, exe.x);
	phi_theta[1] = acos(-(exe.y) / sp->radius);
	u = ((phi_theta[0] + PI) / (2 * PI));
	v = 1 - phi_theta[1] / PI;
	if (u < 0)
		u = 0;
	if (v < 0)
		v = 0;
	if (u > 1.0)
		u = 1.0;
	if (v > 1.0)
		v = 1.0;
	xy[0] = u * sp->texture.width;
	xy[1] = v * sp->texture.height;
	return (sp->texture.buff[xy[0] + xy[1] * sp->texture.width]);
}
