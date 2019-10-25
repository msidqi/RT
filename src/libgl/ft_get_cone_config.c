/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cone_config.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:36:25 by kdaou             #+#    #+#             */
/*   Updated: 2019/10/06 08:46:28 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static void	ft_cone_val_correction(t_cone **cone, t_data *data, int fd)
{
	t_vec4 up;
	double dot_prod;

	up = (t_vec4){0, 1, 0, 0};
	(*cone)->axis = ft_vec4_normalize((*cone)->axis);
	dot_prod = ft_vec4_dot_product((*cone)->axis, up);
	if (dot_prod <= 1 + NEAR && dot_prod >= 1 - NEAR)
		up = (t_vec4){1, 0, 0, 0};
	(*cone)->left = ft_vec4_normalize(ft_vec4_cross_product((*cone)->axis, up));
	(*cone)->forw = ft_vec4_normalize(
					ft_vec4_cross_product((*cone)->left, (*cone)->axis));
	if ((*cone)->texture.id > -1)
		if (!ft_texture_correction(&(*cone)->texture, data))
			ft_error_management(data, 5, (void **)cone, fd);
	if ((*cone)->limits.islimited == 1 && (*cone)->limits.limit == 0)
		(*cone)->limits.islimited = 0;
}

static int	ft_stock_cone_config_next(char *line, t_cone *p, int *i)
{
	int	j;

	j = 0;
	if (!(*i & 1) || !(*i & 16))
		return (0);
	if (ft_expect_matrix(line, "\ttransfo ", &(p->axis)))
	{
		p->axis = ft_vec4_normalize(p->axis);
		j++;
	}
	if (ft_expect_matrix(line, "\ttransfo ", &(p->center)))
		j++;
	return (j == 2 ? 1 : 0);
}

static int	ft_cone_values(int *i, t_cone *p, char *s)
{
	if (!(*i & 1) && ft_expect_vector(s, "\tcenter", &(p->center)))
		*i += 1;
	else if (!(*i & 2) && ft_expect_color(s, "\tcolor", &(p->color)))
		*i += 2;
	else if (!(*i & 4) && ft_expect_diffuse(s, "\tdiffuse", &(p->diffuse)))
		*i += 4;
	else if (!(*i & 8) && ft_expect_value(s, "\tspecular", &(p->specular)))
		*i += 8;
	else if (!(*i & 16) && ft_expect_vector(s, "\tnormal", &(p->axis)))
		*i += 16;
	else if (!(*i & 32) && ft_expect_value(s, "\tangle", &(p->half_angle)))
		*i += 32;
	else if (!(*i & 64) && ft_stock_cone_config_next(s, p, i))
		*i += 64;
	else if (!(*i & 128) && ft_expect_ref(s, "\tref", &p->ref))
		*i += 128;
	else if (!(*i & 256) && ft_expect_texture(s, "\ttexture", &p->texture))
		*i += 256;
	else if (!(*i & 512) && ft_expect_limited(s, "\tlimited", &p->limits))
		*i += 512;
	else
		return (0);
	return (1);
}

static int	ft_stock_cone_config(int fd, t_cone *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_cone_values(&i, p, s))
		{
			if ((i | 128) > i)
				p->ref.w = 0;
			if ((i | 256) > i)
			{
				p->texture.img = NULL;
				p->texture.id = -1;
			}
			if ((i | 512) > i)
				p->limits.islimited = 0;
		}
		else if ((j = ft_bracket_control(s, '}')))
			break ;
		else
			break ;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return ((i == 63 || (((i & 63) == 63 && i & 1023))) && j ? 1 : 0);
}

void		ft_get_cone_config(int fd, t_data *data)
{
	char	*line;
	t_cone	*cone;

	if (!(cone = (t_cone *)malloc(sizeof(t_cone))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_cone_config(fd, cone, 0, 0)))
			{
				ft_memdel((void **)&cone);
				ft_error_management(data, 4, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 4, (void **)&line, fd);
	}
	ft_cone_val_correction(&cone, data, fd);
	ft_lstadd(&(data->scene), ft_lstnew((void *)cone, CONE));
}
