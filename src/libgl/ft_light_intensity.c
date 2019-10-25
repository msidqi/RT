/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_intensity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:23:03 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/05 13:49:59 by arezouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static double	ft_area_intensity(t_list *sc, t_light *li, t_vec4 *inter_point)
{
	t_list	*new_light_list;
	t_ray	ray_to_each_uv;
	double	num;

	num = 0;
	new_light_list = li->lst;
	ray_to_each_uv.origin = *inter_point;
	while (new_light_list)
	{
		ray_to_each_uv.dir = ft_vec4_normalize(
			ft_vec4_sub(
				((t_light *)new_light_list->content)->origin, *inter_point));
		num += ft_ray_inter_objs(sc, &ray_to_each_uv,
				ft_distance_to_light(new_light_list->content, &ray_to_each_uv),
													new_light_list->content);
		new_light_list = new_light_list->next;
	}
	return (num / (li->v_nodes * li->u_nodes));
}

/*
** li->spot_dot : angle between shadow ray and light dir.
** if ray intersected with 1 point of the area light,
** check how many vertices of the area intersects with that intersection point.
** depending on that number return a value from 0.0 to 1.0;
*/

double			ft_light_intensity(t_list *scene, t_light *li,
									t_vec4 *inter_point, t_vec4 *shadow_ray)
{
	if (li->type == POINT_LIGHT)
		return (1);
	else if (li->type == DIRECTIONAL_LIGHT)
		return (1);
	else if (li->type == SPOT_LIGHT
	&& ft_vec4_dot_product(li->dir, *shadow_ray) < li->spot_dot)
		return (1);
	else if (li->type == AREA_LIGHT || li->type == AREA_SPOT_LIGHT)
		return (ft_area_intensity(scene, li, inter_point));
	return (0);
}
