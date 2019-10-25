/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:51:58 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/17 15:53:27 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

t_vec4			ft_matrix_x_vector(t_matrix4 mat, t_vec4 vec)
{
	return ((t_vec4){mat.v[0][0] * vec.x + mat.v[0][1] * vec.y
			+ mat.v[0][2] * vec.z + mat.v[0][3] * vec.w,
			mat.v[1][0] * vec.x + mat.v[1][1] * vec.y + mat.v[1][2] * vec.z
			+ mat.v[1][3] * vec.w,
			mat.v[2][0] * vec.x + mat.v[2][1] * vec.y + mat.v[2][2] * vec.z
			+ mat.v[2][3] * vec.w,
			mat.v[3][0] * vec.x + mat.v[3][1] * vec.y + mat.v[3][2] * vec.z
			+ mat.v[3][3] * vec.w});
}

t_matrix4		ft_get_translation_matrix4(t_matrix4 mat, double x, double y,
		double z)
{
	mat.v[0][3] = x;
	mat.v[1][3] = y;
	mat.v[2][3] = z;
	return (mat);
}

/*
** pass identity matrix in mat for default value
*/

t_matrix4		ft_get_scaling_matrix4(t_matrix4 mat, double x, double y,
		double z)
{
	mat.v[0][0] *= x;
	mat.v[1][1] *= y;
	mat.v[2][2] *= z;
	return (mat);
}

t_matrix4		ft_get_rotation_matrix4(t_matrix4 mat, double x, double y,
		double z)
{
	mat.v[0][0] *= x;
	mat.v[1][1] *= y;
	mat.v[2][2] *= z;
	return (mat);
}

t_vec4			ft_translate_vec4(t_vec4 vec, double x, double y, double z)
{
	t_matrix4 tr_mat;

	tr_mat = ft_create_matrix4();
	tr_mat.v[0][3] = x;
	tr_mat.v[1][3] = y;
	tr_mat.v[2][3] = z;
	return (ft_matrix_x_vector(tr_mat, vec));
}
