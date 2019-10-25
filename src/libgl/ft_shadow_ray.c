/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:53:39 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/05 15:42:04 by arezouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
** tmp, calculating position vector from camera to inter_point
** intersection point calculated
** 							(pos vec of cam + cam_to_inter = inter_vec_pos)
*/

t_ray	ft_get_shadow_ray(t_ray *ray, t_light *light)
{
	t_ray	sh_ray;

	if (light->type == POINT_LIGHT ||
		light->type == AREA_LIGHT || light->type == AREA_SPOT_LIGHT)
	{
		sh_ray.origin = ft_vec4_add(ray->origin,
				ft_vec4_scalar(ray->dir, ray->t));
		sh_ray.dir = ft_vec4_normalize(ft_vec4_sub(light->origin,
															sh_ray.origin));
	}
	else if (light->type == DIRECTIONAL_LIGHT)
	{
		sh_ray.origin = ft_vec4_add(ray->origin,
				ft_vec4_scalar(ray->dir, ray->t));
		sh_ray.dir = ft_vec4_normalize(ft_vec4_scalar(light->dir, -1));
	}
	if (light->type == SPOT_LIGHT)
	{
		sh_ray.origin = ft_vec4_add(ray->origin,
				ft_vec4_scalar(ray->dir, ray->t));
		sh_ray.dir = ft_vec4_normalize(ft_vec4_sub(light->origin,
					sh_ray.origin));
	}
	return (sh_ray);
}
