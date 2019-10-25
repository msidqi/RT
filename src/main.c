/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 12:48:35 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/11 12:07:18 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgl.h"

void	*ft_ray_trace(void *param)
{
	t_data *data;

	data = (t_data *)param;
	ft_camera(data, data->cam.pos, data->cam.to);
	ft_draw_scene(data);
	return (NULL);
}

void	ft_loadingscreen(void *mlx, void *win, char *path)
{
	t_texture		t;
	int				endian;
	int				size_line;
	int				bpp;

	if (!
	(t.img = mlx_xpm_file_to_image(mlx, (char *)path, &t.width, &t.height)))
		return ;
	t.buff = (int *)mlx_get_data_addr(t.img, &bpp, &size_line, &endian);
	mlx_put_image_to_window(mlx, win, t.img, 0, 0);
	mlx_destroy_image(mlx, t.img);
	mlx_do_sync(mlx);
}

int		main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl_fd("Invalid number of config file\n"
				"usage : \n./RTv1 config file", 2);
		return (1);
	}
	if (!ft_window_setup(&data, "RocketTeam", HEIGHT, WIDTH)
			|| !ft_image_setup(&data))
		return (1);
	ft_loadingscreen(data.mlx, data.win, "textures/loading3.xpm");
	data.filter = 0;
	data.light_list = NULL;
	data.scene = NULL;
	data.cam.focal_length = 2;
	data.cam.f_dist = 15;
	data.cam.refl_depth = 3;
	ft_get_config(argv[1], &data);
	srand(time(NULL));
	random_jitter(&data, (size_t)JNUM);
	ft_multi_thread(&data, &ft_ray_trace);
	mlx_put_image_to_window(data.mlx, data.win, data.img_ptr, 0, 0);
	ft_mlx_hooks(&data, RED_BUTTON_HOOK | KEY_PRESS_HOOK);
	return (0);
}

/*
**	macro up : 1;
**	macro down  : 2;
**	macro left : 4;
**	macro right  : 8;
**	(left | up | left | right)
**
** Vec P(x,y,z,w) , Vec C(5,5,5,1)
**
** |P - C|² = r²
** 	P - C² 	= r²
**
** magnitude A =  ||A|| = P-C
** magnitude B =  ||B|| = V = 1
**
** B is normalazed
**
** angle  entre (vec4 A et vec4 B)  ==    dotprod(A , B)
**
** dot(A, B )  =   cos (A , B) * ||A||  * ||1||
** cos (A , B) =   dot(A, B )  / ||A||  * ||1||
*/
