/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 08:58:11 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/06 08:58:24 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

short	ft_light_type(int i)
{
	if (i == 3)
		return (POINT_LIGHT);
	if (i == 15)
		return (AREA_LIGHT);
	if (i == 51)
		return (SPOT_LIGHT);
	if (i == 35)
		return (DIRECTIONAL_LIGHT);
	if (i == 63)
		return (AREA_SPOT_LIGHT);
	return (-1);
}
