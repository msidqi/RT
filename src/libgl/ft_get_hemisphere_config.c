/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_hemisphere_config.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 09:05:40 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/06 08:45:35 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static void	ft_hemisphere_val_correction(t_h_sphere **hemisphere,
		t_data *data, int fd)
{
	if ((*hemisphere)->texture.id > -1)
	{
		if (!ft_load_texture((*hemisphere)->texture.id,
					&(*hemisphere)->texture, data))
			ft_error_management(data, 11, (void **)hemisphere, fd);
		if ((*hemisphere)->texture.stretch_x == 0)
			(*hemisphere)->texture.stretch_x = 1;
		if ((*hemisphere)->texture.stretch_y == 0)
			(*hemisphere)->texture.stretch_y = 1;
		if ((*hemisphere)->texture.stretch_z == 0)
			(*hemisphere)->texture.stretch_z = 1;
	}
}

static int	ft_hemisphere_values(int *i, t_h_sphere *p, char *s)
{
	if (!(*i & 1) && ft_expect_value(s, "\tradius", &p->radius))
		*i += 1;
	else if (!(*i & 2) && ft_expect_vector(s, "\tcenter", &p->center))
		*i += 2;
	else if (!(*i & 4) && ft_expect_color(s, "\tcolor", &p->color))
		*i += 4;
	else if (!(*i & 8) && ft_expect_diffuse(s, "\tdiffuse", &p->diffuse))
		*i += 8;
	else if (!(*i & 16) && ft_expect_value(s, "\tspecular", &p->specular))
		*i += 16;
	else if (!(*i & 32) && ft_expect_ref(s, "\tref", &p->ref))
		*i += 32;
	else if (!(*i & 64) && ft_expect_matrix(s, "\ttransfo ", &p->center))
		*i += 64;
	else if (!(*i & 128) && ft_expect_texture(s, "\ttexture", &p->texture))
		*i += 128;
	else if (!(*i & 256) && ft_expect_vector(s, "\tnormal", &p->normal))
		*i += 256;
	else
		return (0);
	return (1);
}

static int	ft_stock_hemisphere_config(int fd, t_h_sphere *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_hemisphere_values(&i, p, s))
		{
			if ((i | 32) > i)
				p->ref.w = 0;
			if ((i | 128) > i)
			{
				p->texture.img = NULL;
				p->texture.id = -1;
			}
		}
		else if ((j = ft_bracket_control(s, '}')))
			break ;
		else
			break ;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return ((i == 287 || (((i & 287) == 287) && i & 511)) && j ? 1 : 0);
}

void		ft_get_hemisphere_config(int fd, t_data *data)
{
	char		*line;
	t_h_sphere	*hemisphere;

	if (!(hemisphere = (t_h_sphere *)malloc(sizeof(t_h_sphere))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_hemisphere_config(fd, hemisphere, 0, 0)))
			{
				ft_memdel((void **)&hemisphere);
				ft_error_management(data, 7, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 7, (void **)&line, fd);
	}
	ft_hemisphere_val_correction(&hemisphere, data, fd);
	ft_lstadd(&(data->scene), ft_lstnew((void *)hemisphere, HSPHERE));
}
