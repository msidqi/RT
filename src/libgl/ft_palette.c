/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_palette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 01:38:04 by msidqi            #+#    #+#             */
/*   Updated: 2018/12/10 22:04:01 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static	void	ft_palette3(t_palette *palette)
{
	if (palette->palette_choice == 4)
	{
		palette->palette[0] = 0x30b1c3;
		palette->palette[1] = 0xabe9f0;
		palette->palette[2] = 0x9a4e00;
		palette->palette[3] = 0xba7e00;
		palette->palette[4] = 0xff6700;
		palette->palette[5] = 0xffa700;
		palette->palette[6] = 0xffF700;
		palette->palette[7] = 0xfcffcd;
	}
	else if (palette->palette_choice == 5)
	{
		palette->palette[0] = 0xb9c1d1;
		palette->palette[1] = 0xe9d1e1;
		palette->palette[2] = 0x909cb5;
		palette->palette[3] = 0xa0bcd5;
		palette->palette[4] = 0x707a8a;
		palette->palette[5] = 0x7f7b81;
		palette->palette[6] = 0x9f9ba1;
		palette->palette[7] = 0xc2bdb7;
	}
}

static	void	ft_palette2(t_palette *palette)
{
	if (palette->palette_choice == 2)
	{
		palette->palette[0] = 0xe5c883;
		palette->palette[1] = 0xf5f8b3;
		palette->palette[2] = 0xfffef2;
		palette->palette[3] = 0xff8080;
		palette->palette[4] = 0xffa0a0;
		palette->palette[5] = 0xf4d8ac;
		palette->palette[6] = 0xffA16c;
		palette->palette[7] = 0xf0d38c;
	}
	else if (palette->palette_choice == 3)
	{
		palette->palette[0] = 0x8bd9f0;
		palette->palette[1] = 0xabe9f0;
		palette->palette[2] = 0xa2e7f6;
		palette->palette[3] = 0xb2d7f6;
		palette->palette[4] = 0xb5f2fb;
		palette->palette[5] = 0xbb813c;
		palette->palette[6] = 0x77f6f5;
		palette->palette[7] = 0x33f455;
	}
	else if (palette->palette_choice >= 4)
		ft_palette3(palette);
}

void			ft_palette(t_palette *palette)
{
	if (palette->palette_choice == 0)
	{
		palette->palette[0] = 0x0000e6;
		palette->palette[1] = 0x4ddbff;
		palette->palette[2] = 0xccff66;
		palette->palette[3] = 0xffff00;
		palette->palette[4] = 0xffcc00;
		palette->palette[5] = 0xff9933;
		palette->palette[6] = 0xff6600;
		palette->palette[7] = 0xFFFFFE;
	}
	else if (palette->palette_choice == 1)
	{
		palette->palette[0] = 0x230827;
		palette->palette[1] = 0x491647;
		palette->palette[2] = 0x7c265e;
		palette->palette[3] = 0xff5454;
		palette->palette[4] = 0xff9494;
		palette->palette[5] = 0xff813c;
		palette->palette[6] = 0xffA16c;
		palette->palette[7] = 0xfff400;
	}
	else if (palette->palette_choice >= 2)
		ft_palette2(palette);
}

/*
** change current palette to 0 if u change the palette type
*/

void			ft_palette_rotation(t_palette *palette)
{
	int size;

	size = sizeof(palette->palette) / sizeof(palette->palette[0]);
	palette->palette_choice++;
	if (palette->palette_choice > (size - 1))
		palette->palette_choice = 0;
	ft_palette(palette);
}
