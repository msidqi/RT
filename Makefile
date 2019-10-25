# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arezouk <arezouk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/23 00:08:25 by msidqi            #+#    #+#              #
#    Updated: 2019/10/11 12:15:24 by msidqi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
LIBFT = libft.a
LIBGL = libgl.a
LIBMLX = libmlx.a
LIBFTL = libft/libft.a
LIBGLL = src/libgl/libgl.a
LIBMLXL = src/minilibx_macos/libmlx.a
SRC_PATH = src
GLSRC_PATH = src/libgl
SRC = connect_dotss.c ft_cone_functions.c ft_event_system_mlx.c  \
ft_get_cone_config.c ft_get_hyperboloid_config.c  ft_get_sphere_config.c \
ft_light_intersection.c ft_parsing_tools.c ft_torus_function.c ft_vec_scalar.c \
drawline.c ft_cube_troue_function.c ft_events_keyboard.c ft_get_config.c \
ft_get_light_config.c ft_light_type.c ft_get_torus_config.c ft_limits.c  ft_plane_functions.c \
ft_triangle_functions.c ft_vector_add.c drawsquares.c ft_cylinder_functions.c \
ft_expect.c ft_get_cube_troue_config.c ft_matrix.c ft_get_triangle_config.c \
ft_reflected_ray.c  ft_utils_func.c ft_atof.c ft_vector_operations.c \
ft_disc_functions.c ft_expect_matrix.c ft_image_setup_mlx.c \
ft_get_cylinder_config.c ft_get_paraboloid_config.c ft_hemisphere_functions.c \
ft_min_max.c ft_screenshot.c ft_vec_create.c ft_vector_sub.c ft_box_functions.c  \
ft_draw_scene.c ft_filters.c ft_get_disc_config.c   ft_get_plane_config.c  \
ft_multi_thread.c ft_solve_equation_4.c ft_solve_equation_3.c \
ft_vec_cross_dot_prod.c get_next_line.c ft_camera.c ft_ellipsoid_function.c \
ft_get_box_config.c ft_get_ellispoid_config.c  ft_shadow_ray.c  \
ft_sphere_functions.c ft_color_operations.c ft_error_management.c ft_error_type.c\
ft_get_camera_config.c ft_get_hemisphere_config.c ft_get_scene_config.c ft_expect_values.c \
ft_light_intensity.c ft_paraboloid_functions.c ft_textures.c ft_vec_normalize_magnitude.c \
ft_hyperboloid_functions.c ft_fractal_texture.c ft_sphere_texture.c ft_shape_textures.c
INCLUDE = include
INC = include/libft.h include/libgl.h
OBJS_DIR = .objs
CC = gcc -Wall -Wextra -Werror 
FLAGS_LINUX = -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11 -lm -lpthread
FLAGS = -framework OpenGl -framework Appkit -lmlx
OBJ = $(addprefix $(OBJS_DIR)/,$(SRC:.c=.o))

all : $(NAME)

$(OBJ) : $(OBJS_DIR)/%.o : $(GLSRC_PATH)/%.c $(INC) | $(OBJS_DIR)
	$(CC) -c $< -o $@ -I$(INCLUDE)
$(LIBGLL) : $(OBJ)
	ar rc $@ $^
	ranlib $@
$(LIBFTL) :
	make -C libft
$(NAME) : $(LIBFTL) $(LIBGLL) $(SRC_PATH)/main.c
	$(CC) -o $@ $< $(word 2,$^) $(word 3,$^) $(FLAGS) -I$(INCLUDE)

clean :
	rm -rf $(OBJ) $(LIBGLL) $(LIBFTL)
	make clean -C libft
fclean : clean
	rm -rf $(NAME)
	make fclean -C libft
re : fclean all

$(OBJS_DIR):
	mkdir $(OBJS_DIR)
