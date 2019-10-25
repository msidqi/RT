/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_limits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:09:59 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/05 13:46:28 by arezouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int		ft_pick_distance(double *t, t_ray *ray, t_limits *limits)
{
	if (((t[1] <= t[0] || t[0] < NEAR) && t[1] > NEAR) && (t[1] < ray->t))
	{
		if (limits->islimited && ft_limit_axis(t[1], ray, limits))
			return (false);
		ray->t = t[1];
		return (true);
	}
	else if (((t[0] < t[1] || t[1] < NEAR) && t[0] > NEAR) && (t[0] < ray->t))
	{
		if (limits->islimited && ft_limit_axis(t[0], ray, limits))
			return (false);
		ray->t = t[0];
		return (true);
	}
	return (false);
}

int		ft_check_distance(double *t, t_ray *ray)
{
	if (((t[1] <= t[0] || t[0] < NEAR) && t[1] > NEAR) && (t[1] < ray->t))
	{
		ray->t = t[1];
		return (true);
	}
	else if (((t[0] < t[1] || t[1] < NEAR) && t[0] > NEAR) && (t[0] < ray->t))
	{
		ray->t = t[0];
		return (true);
	}
	return (false);
}

int		ft_limit_axis(double t, t_ray *ray, t_limits *limits)
{
	t_vec4 p;

	p = ft_vec4_add(ft_vec4_scalar(ray->dir, t), ray->origin);
	if ((((p.x > 0 && limits->x > 0 && p.x > limits->x)
		|| (p.x < 0 && limits->x < 0 && p.x < limits->x))
		|| ((p.y > 0 && limits->y > 0 && p.y > limits->y)
		|| (p.y < 0 && limits->y < 0 && p.y < limits->y))
		|| ((p.z > 0 && limits->z > 0 && p.z > limits->z)
		|| (p.z < 0 && limits->z < 0 && p.z < limits->z))))
		return (true);
	return (false);
}

/*
** for limited cylinder and cone
*/

int		ft_islimited(t_ray *ray, double *t, t_cylinder *cyl)
{
	t_vec4	x;
	double	m;
	double	m1;

	x = ft_vec4_sub(ray->origin, cyl->point);
	m = ft_vec4_dot_product(ray->dir,
	ft_vec4_scalar(cyl->axis, t[0])) + ft_vec4_dot_product(x, cyl->axis);
	m1 = ft_vec4_dot_product(ray->dir,
	ft_vec4_scalar(cyl->axis, t[1])) + ft_vec4_dot_product(x, cyl->axis);
	if (cyl->limits.limit && ((m > cyl->limits.limit && m1 > cyl->limits.limit)
	|| (m < -1 * cyl->limits.limit && m1 < -1 * cyl->limits.limit)))
		return (false);
	return (true);
}
