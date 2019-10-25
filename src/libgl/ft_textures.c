/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:20:01 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/06 20:55:37 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

const char	g_xt_ids[28][20] =
{
	"textures/earth_.xpm",
	"textures/future.xpm",
	"textures/arezok.xpm",
	"textures/logo__.xpm",
	"textures/mario_.xpm",
	"textures/pepe__.xpm",
	"textures/plane_.xpm",
	"textures/wood__.xpm",
	"textures/kirby_.xpm",
	"textures/sky___.xpm",
	"textures/sans1_.xpm",
	"textures/sans2_.xpm",
	"textures/golf__.xpm",
	"textures/planet.xpm",
	"textures/city__.xpm",
	"textures/indoor.xpm",
	"textures/team__.xpm",
	"textures/royal_.xpm",
	"textures/bridge.xpm",
	"textures/space2.xpm",
	"textures/space_.xpm",
	"textures/death4.xpm",
	"textures/80ssun.xpm",
	"textures/80grid.xpm",
	"textures/81grid.xpm",
	"textures/m_____.xpm",
	"textures/rock__.xpm",
	"textures/wood2_.xpm",
};

int			ft_load_texture(int id, t_texture *t, t_data *data)
{
	int		bpp;
	int		size_l;
	int		endian;

	if (id < 0 || id > (int)STATIC_ARRAY_SIZE(g_xt_ids) ||
	!(t->img = mlx_xpm_file_to_image(data->mlx, (char *)g_xt_ids[id],
			&t->width, &t->height)))
		return (0);
	t->buff = (int *)mlx_get_data_addr(t->img, &bpp, &size_l, &endian);
	return (1);
}

int			ft_texture_correction(t_texture *texture, t_data *data)
{
	if (texture->id == 100 || texture->id == 101)
	{
		texture->id = texture->id == 100 ? 100 : 101;
		texture->img = NULL;
	}
	else if (texture->id == 102)
	{
		texture->id = 102;
		texture->img = NULL;
	}
	else if (texture->id > (int)STATIC_ARRAY_SIZE(g_xt_ids)
			|| !ft_load_texture(texture->id, texture, data))
		return (0);
	if (texture->stretch_x == 0)
		texture->stretch_x = 1;
	if (texture->stretch_y == 0)
		texture->stretch_y = 1;
	if (texture->stretch_z == 0)
		texture->stretch_z = 1;
	return (1);
}

void		ft_sphere_val_correction(t_sphere **sphere, t_data *data, int fd)
{
	if ((*sphere)->texture.id > -1)
	{
		if ((*sphere)->texture.id == 100)
		{
			(*sphere)->texture.id = 100;
			(*sphere)->texture.img = NULL;
		}
		else if ((*sphere)->texture.id > (int)STATIC_ARRAY_SIZE(g_xt_ids)
		|| !ft_load_texture((*sphere)->texture.id, &(*sphere)->texture, data))
			ft_error_management(data, 11, (void **)sphere, fd);
		if ((*sphere)->texture.stretch_x == 0)
			(*sphere)->texture.stretch_x = 1;
		if ((*sphere)->texture.stretch_y == 0)
			(*sphere)->texture.stretch_y = 1;
		if ((*sphere)->texture.stretch_z == 0)
			(*sphere)->texture.stretch_z = 1;
	}
}

/*
** xy[2] : edge
*/

int			ft_pick_proc_texture(double *uv, t_texture *txt)
{
	int		xy[2];

	xy[0] = (int)uv[0] * txt->stretch_x;
	xy[1] = (int)uv[1] * txt->stretch_y;
	if (txt->id == 101)
	{
		return (
			((sin(uv[1] * 10) > 0) ^ (sin(uv[0] * 10) > 0)) ? 0xFFFFFF : 0x0);
	}
	if (txt->id == 102)
		return (ft_fractal_texture(uv));
	if (txt->id == 100)
		return ((sin(uv[0] * 100) > 0) ? 0x8a49a2 : 0xd7edbf);
	return (0);
}
