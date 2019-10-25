/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 08:53:36 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/06 08:53:45 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

char		*ft_error_type(int error)
{
	char *str[22];

	str[0] = "Error invalid config file";
	str[1] = "Config file syntax error in : Camera";
	str[2] = "Config file syntax error in : Sphere";
	str[3] = "Config file syntax error in : Plane";
	str[4] = "Config file syntax error in : Cone";
	str[5] = "Config file syntax error in : Cylinder";
	str[6] = "Config file syntax error in : Light";
	str[7] = "Config file syntax error in hemisphere";
	str[8] = "Error scene require one camera";
	str[9] = "Error 1 object at least";
	str[10] = "Error allocating memory";
	str[11] = "Error while loading the texture image";
	str[12] = "Config file syntax error in : Box";
	str[13] = "Config file syntax error in : Scene";
	str[14] = "Exited with no error.";
	str[15] = "Config file syntax error in : Disc";
	str[16] = "Config file syntax error in : h_cube";
	str[17] = "Config file syntax error in : ellipsoid";
	str[18] = "Config file syntax error in : torus";
	str[19] = "Config file syntax error in : paraboloid";
	str[20] = "Config file syntax error in : hyperboloid";
	str[21] = "Config file syntax error in : Triangle";
	return (str[error]);
}
