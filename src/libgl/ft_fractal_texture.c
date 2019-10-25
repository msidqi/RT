/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 00:15:42 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/04 20:11:22 by arezouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int			burning_ship(t_fract *data, double c_x, double c_y)
{
	double	real;
	double	imaginary;
	double	tmpreal;
	int		i;

	i = 0;
	imaginary = 0;
	real = 0;
	while (i < data->max_iter)
	{
		tmpreal = ABS(real * real - imaginary * imaginary + c_x);
		imaginary = ABS(2 * real * imaginary + c_y);
		real = tmpreal;
		if (real * real + imaginary * imaginary > 4)
			return (i);
		i++;
	}
	return (0);
}

static int			mandelbrot_set(t_fract *data, double c_x, double c_y)
{
	double	real;
	double	imaginary;
	double	tmpreal;
	int		i;

	i = 0;
	imaginary = 0;
	real = 0;
	while (i < data->max_iter)
	{
		tmpreal = real * real - imaginary * imaginary + c_x;
		imaginary = 2 * real * imaginary + c_y;
		real = tmpreal;
		if (real * real + imaginary * imaginary > 4)
			return (i);
		i++;
	}
	return (0);
}

static int			ft_checkif_in_set(t_fract *data, double a, double b)
{
	if (data->set == 'm')
		return (mandelbrot_set(data, a / data->zoom, b / data->zoom));
	if (data->set == 'b')
		return (burning_ship(data, a / data->zoom, b / data->zoom));
	return (0);
}

static void			ft_color_change(int *col, t_fract *data)
{
	int				tmp;
	unsigned char	*ptr;

	tmp = *col;
	ptr = (unsigned char*)col;
	ptr[0] = data->color.blue * (tmp) / MAX_ITER;
	ptr[1] = data->color.green * (tmp) / MAX_ITER;
	ptr[2] = data->color.red * (tmp) / MAX_ITER;
}

int					ft_fractal_texture(double *uv)
{
	int				c;
	t_fract			d;

	c = 0x0;
	d.set = 'm';
	d.zoom = 3;
	d.max_iter = MAX_ITER;
	d.color.red = 0;
	d.color.green = 255;
	d.color.blue = 0;
	c = ft_checkif_in_set(&d, uv[0], uv[1]);
	ft_color_change(&c, &d);
	return (c);
}
