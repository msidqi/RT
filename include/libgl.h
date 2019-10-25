/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:43:22 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/11 12:09:32 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGL_H
# define LIBGL_H

# include <mlx.h>
# include "libft.h"
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <time.h>
# include <stdio.h>
# include <fcntl.h>

# define ABS(Value) (Value >= 0) ? (Value) : -(Value)
# define STATIC_ARRAY_SIZE(ptr) (sizeof(ptr) / sizeof(ptr[0]))
# define MAX_ITER 30
# define VERTEX 0
# define VECTOR 1
# define DIRECTION 2
# define MATRIX 3
# define TRANSLATION_MATRIX 0
# define ROTATION_MATRIX 1
# define SCALING_MATRIX 2
# define NEAR 1e-6
# define FAR 1e+6
# define DISTANT_LIGHT 1e+6
# define RED 0xFF0000
# define GREEN 0xFF00
# define BLUE 0xFF
# define BLACK 0x0
# define WHITE 0xFFFFFF
# define AMBIENT_R 0.4
# define AMBIENT_G 0.4
# define AMBIENT_B 0.4
# define SPECULAR_POW 30
# define HEIGHT 720
# define WIDTH 1280
# define ASPECT_RATIO HEIGHT / WIDTH
# define MAX_ITER 30
# define PI 3.14159265358979323846
# define JNUM 1
# define N_THREADS 4

typedef enum		e_event_code
{
	MOUSE_PRESS_CODE = 4,
	MOUSE_MOVE_CODE = 6,
	KEY_PRESS_CODE = 2,
	RED_BUTTON_CODE = 17,
}					t_event_code;

typedef enum		e_ft_mlx_hooks
{
	NO_EVENT_HOOK = 0,
	MOUSE_PRESS_HOOK = 1,
	MOUSE_MOVE_HOOK = 2,
	KEY_PRESS_HOOK = 4,
	RED_BUTTON_HOOK = 8,
}					t_ft_mlx_hooks;

typedef enum		e_key_code
{
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5,
	ZOOM_IN = 69,
	ZOOM_OUT = 78,
	SPACE = 49,
	NUM_LOCK_9 = 92,
	NUM_LOCK_8 = 91,
	NUM_LOCK_7 = 89,
	NUM_LOCK_6 = 88,
	NUM_LOCK_5 = 87,
	NUM_LOCK_4 = 86,
	NUM_LOCK_3 = 85,
	NUM_LOCK_2 = 84,
	NUM_LOCK_1 = 83,
	NUM_LOCK_0 = 82,
	RIGHT_ARROW = 124,
	LEFT_ARROW = 123,
	UP_ARROW = 126,
	DOWN_ARROW = 125,
}					t_key_code;

typedef enum		e_light_type
{
	POINT_LIGHT = 0,
	DIRECTIONAL_LIGHT,
	SPOT_LIGHT,
	AREA_LIGHT,
	AREA_SPOT_LIGHT,
}					t_light_type;

typedef enum		e_object
{
	SPHERE = 0,
	PLANE,
	CONE,
	CYLINDER,
	BOX,
	DISC,
	HSPHERE,
	TORUS,
	H_CUBE,
	PARAB,
	HYPER,
	ELLIPSOID,
	TRIANGLE
}					t_object;

typedef struct		s_vec2
{
	double			x;
	double			y;
}					t_vec2;

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_matrix
{
	int				cols;
	int				rows;
	double			**v;
}					t_matrix;

typedef struct		s_vec4
{
	double			x;
	double			y;
	double			z;
	double			w;
}					t_vec4;

/*
** Homogenous Coordinates
**   F U R  T   (Forward/Up/Right/Translation Vector)
** [[1 0 0] 0]
** [[0 1 0] 0]
** [[0 0 1] 0]
** [ 0 0 0  1] 0 Direction Vector 1 Position Vector
** FUR == unit vectors describing object orientation. aka vector basis
*/

typedef struct		s_matrix4
{
	short			type;
	double			v[4][4];
}					t_matrix4;

typedef struct		s_startend
{
	t_vec2			start;
	t_vec2			end;
}					t_startend;

typedef struct		s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_color;

typedef enum		e_bool
{
	false, true
}					t_bool;

/*
** P(t) = origin + t * dir
** t_vec4 origin : vector to origin point
** t_vec4 dir : direction vector
** t_vec4 t : distance
*/

typedef struct		s_ray
{
	t_vec4			origin;
	t_vec4			dir;
	double			t;
	short			refl_depth;
}					t_ray;

/*
** r : intensity rgb(1.0, 0.0, 0.0) == red
** 	t_vec4	dir: direcional light && spot light
** 	t_vec4	u_dir: area light orientation vectors
** 	float	spot_dot: angle of the spot light ]-1, 0[
** 	unsigned short	u_nodes: number of nodes in area light
*/

typedef	struct		s_light
{
	short			type;
	double			r;
	double			g;
	double			b;
	t_vec4			origin;
	t_vec4			dir;
	unsigned short	u_nodes;
	unsigned short	v_nodes;
	t_vec4			u_dir;
	t_vec4			v_dir;
	t_list			*lst;
	float			spot_dot;
}					t_light;

typedef struct		s_camera
{
	t_vec4			to;
	t_vec4			pos;
	t_vec4			up;
	t_vec4			forward;
	t_vec4			left;
	double			l;
	double			bigl;
	double			focal_length;
	int				f_dist;
	int				n;
	short			refl_depth;
}					t_camera;

typedef	struct		s_data
{
	t_vec2			juliapos;
	t_bool			islocked;
	double			zoom;
	double			movex;
	double			movey;
	char			set;
	int				max_iter;
	double			filter;
	t_vec4			ambient;
	double			depthoffield;
	double			aa_jitter[JNUM * 2];
	t_list			*light_list;
	t_list			*scene;
	t_camera		cam;
	t_color			color;
	t_startend		thread_range;
	int				winwidth;
	int				winheight;
	void			*mlx;
	void			*win;
	void			*img_ptr;
	int				*image;
	int				endian;
	int				size_line;
	int				bpp;
}					t_data;

typedef	struct		s_fract
{
	double			zoom;
	char			set;
	int				max_iter;
	t_color			color;
}					t_fract;

typedef struct		s_limits
{
	int				islimited;
	double			limit;
	double			x;
	double			y;
	double			z;
}					t_limits;

typedef struct		s_ref
{
	double			x;
	double			y;
	double			z;
	double			w;
	double			n;
	int				noshading;
}					t_ref;

typedef struct		s_texture
{
	int				id;
	int				width;
	int				height;
	int				*buff;
	void			*img;
	double			stretch_x;
	double			stretch_y;
	double			stretch_z;
}					t_texture;

typedef	struct		s_h_cube
{
	t_texture		texture;
	t_ref			ref;
	double			specular;
	t_vec4			diffuse;
	double			radius;
	int				color;
}					t_h_cube;

typedef	struct		s_sphere
{
	t_texture		texture;
	t_ref			ref;
	double			specular;
	t_vec4			diffuse;
	t_vec4			center;
	t_limits		limits;
	double			radius;
	int				color;
}					t_sphere;

typedef	struct		s_ellipsoid
{
	t_texture		texture;
	t_ref			ref;
	t_vec4			axis;
	double			specular;
	t_vec4			diffuse;
	t_vec4			center;
	t_limits		limits;
	int				color;
}					t_ellipsoid;

typedef	struct		s_torus
{
	t_texture		texture;
	t_ref			ref;
	double			specular;
	t_vec4			diffuse;
	t_vec4			center;
	t_vec4			axis;
	t_limits		limits;
	double			br;
	double			sr;
	int				color;
}					t_torus;

typedef	struct		s_h_sphere
{
	t_texture		texture;
	t_ref			ref;
	double			specular;
	t_vec4			normal;
	t_vec4			diffuse;
	t_vec4			center;
	t_limits		limits;
	double			radius;
	int				color;
}					t_h_sphere;

/*
**	t_vect4 left && t_vect forw for applying texture
*/

typedef	struct		s_disc
{
	t_texture		texture;
	t_ref			ref;
	double			specular;
	t_vec4			diffuse;
	t_vec4			normal;
	t_limits		limits;
	t_vec4			left;
	t_vec4			forw;
	t_vec4			point;
	int				color;
	double			radius;
}					t_disc;

typedef	struct		s_plane
{
	t_texture		texture;
	t_ref			ref;
	double			specular;
	t_vec4			diffuse;
	t_vec4			normal;
	t_limits		limits;
	t_vec4			left;
	t_vec4			forw;
	t_vec4			point;
	int				color;
}					t_plane;

typedef	struct		s_box
{
	t_texture		texture;
	t_ref			ref;
	double			specular;
	t_vec4			diffuse;
	t_vec4			bmax;
	t_vec4			bmin;
	t_limits		limits;
	int				color;
}					t_box;

typedef	struct		s_hyper
{
	double			k;
	t_vec4			center;
	t_texture		texture;
	t_ref			ref;
	double			specular;
	t_vec4			diffuse;
	t_limits		limits;
	int				color;
}					t_hyper;

typedef	struct		s_parab
{
	double			k;
	t_vec4			center;
	t_vec4			normal;
	t_texture		texture;
	t_ref			ref;
	double			specular;
	t_vec4			diffuse;
	t_limits		limits;
	int				color;
}					t_parab;

typedef	struct		s_cone
{
	t_texture		texture;
	t_ref			ref;
	double			specular;
	t_vec4			diffuse;
	t_vec4			axis;
	t_limits		limits;
	t_vec4			left;
	t_vec4			forw;
	t_vec4			center;
	double			half_angle;
	int				color;
}					t_cone;

typedef	struct		s_cylinder
{
	t_texture		texture;
	t_ref			ref;
	double			specular;
	t_vec4			diffuse;
	t_vec4			axis;
	t_limits		limits;
	t_vec4			left;
	t_vec4			forw;
	t_vec4			point;
	double			radius;
	int				color;
}					t_cylinder;

typedef	struct		s_triangle
{
	double			specular;
	t_texture		texture;
	t_ref			ref;
	t_vec4			diffuse;
	t_vec4			normal;
	t_vec4			point;
	t_vec4			vertex0;
	t_vec4			vertex1;
	t_vec4			vertex2;
	int				color;
}					t_triangle;

typedef struct		s_shader_x
{
	t_vec4			diff;
	t_vec4			spec;
}					t_shader_x;

typedef struct		s_shader
{
	int				diffuse;
	int				specular;
	int				ambient;
}					t_shader;

typedef struct		s_palette
{
	int				palette[8];
	int				palette_choice;
}					t_palette;

typedef struct		s_obj_function
{
	size_t			type;
	int				(*call)();
	int				(*call2)();
}					t_obj_function;

int					ft_window_setup(t_data *data, char *win_name,
											int winheight, int winwidth);
int					ft_image_setup(t_data *data);
void				ft_image_fill(t_data *data, int x,
												int y, int color);
void				ft_loadingscreen(void *mlx, void *win, char *path);
double				lerp(double x1, double x2, double lerp);
double				ft_get_world_pos(double screen_coord,
								double widthheight, double zoom);
void				ft_refresh_image(t_data *data);
int					red_button(t_data *data);
void				ft_mlx_hooks(t_data *data, int flags);
int					no_event_mouse_move(t_data *data);
int					key_press(int key_code, t_data *data);
int					mouse_press(int button, int x, int y, t_data *data);
int					mouse_move(int x, int y, t_data *data);
int					unload(int key_code, t_data *data);
void				ft_multi_thread(t_data *data, void *(*f)(void *));
void				drawline(t_data *data, int startline,
		int nlines, int color);
void				drawnsquares(t_data *data, int onedlen);
void				connect_dotss(t_data *data, t_vec2 a, t_vec2 b, int color);
void				ft_create_vec2(t_vec2 *a, double x, double y);
void				ft_create_vec3(t_vec3 *a, double x, double y, double z);
t_vec2				ft_vec2_add(t_vec2 a, t_vec2 b);
t_vec3				ft_vec3_add(t_vec3 a, t_vec3 b);
t_vec2				ft_vec2_sub(t_vec2 a, t_vec2 b);
t_vec3				ft_vec3_sub(t_vec3 a, t_vec3 b);
t_vec2				ft_vec2_scalar(t_vec2 a, double factor);
t_vec3				ft_vec3_scalar(t_vec3 a, double factor);
double				ft_vec2_mag(t_vec2 a);
double				ft_vec3_mag(t_vec3 a);
double				ft_vec2_mag_cmp(t_vec2 a, t_vec2 b);
double				ft_vec3_mag_cmp(t_vec3 a, t_vec3 b);
t_vec2				ft_vec2_normalize(t_vec2 a);
t_vec3				ft_vec3_normalize(t_vec3 a);
double				ft_vec2_dot_product(t_vec2 a, t_vec2 b);
double				ft_vec3_dot_product(t_vec3 a, t_vec3 b);
t_vec2				ft_vec2_rotate_byangle(t_vec2 a, double angle);
t_vec2				ft_vec2_rotate_byaxis(t_vec2 a, t_vec2 x_axis,
		t_vec2 y_axis);
t_matrix			*ft_create_matrix(int rows, int cols);
t_matrix4			ft_create_matrix4();
int					ft_destroy_matrix(t_matrix *mat);
t_matrix4			ft_get_translation_matrix4(t_matrix4 mat, double x,
		double y, double z);
t_vec4				ft_create_vec4(double x, double y, double z, double w);
t_vec4				ft_matrix_x_vector(t_matrix4 mat, t_vec4 vec);
void				ft_printvec4(t_vec4 *vec);
t_vec4				ft_vec4_sub(t_vec4 vec1, t_vec4 vec2);
t_vec4				ft_vec4_normalize(t_vec4 a);
double				ft_vec4_mag(t_vec4 a);
double				ft_vec4_dot_product(t_vec4 a, t_vec4 b);
void				ft_draw_scene(t_data *data);
void				*ft_ray_trace(void *param);
t_vec4				ft_vec4_cross_product(t_vec4 vec1, t_vec4 vec2);
t_vec4				ft_vec4_add(t_vec4 vec1, t_vec4 vec2);
t_vec4				ft_vec4_scalar(t_vec4 a, double factor);

int					ft_plane_inter(t_ray *ray, t_plane *plane);
int					ft_sphere_inter(t_ray *ray, t_sphere *sphere);
int					ft_triangle_inter(t_ray *ray, t_triangle *triangle);
int					ft_ellipsoid_inter(t_ray *ray, t_ellipsoid *ellipse);
int					ft_hyperboloid_inter(t_ray *ray, t_hyper *hyper);
int					ft_paraboloid_inter(t_ray *ray, t_parab *t);
int					ft_h_cube_inter(t_ray *ray, t_h_cube *t);
int					ft_torus_inter(t_ray *ray, t_torus *t);
int					ft_hemisphere_inter(t_ray *ray, t_h_sphere *hp);
int					ft_cone_inter(t_ray *ray, t_cone *cone);
int					ft_cylinder_inter(t_ray *ray, t_cylinder *cylinder);
int					ft_disc_inter(t_ray *ray, t_disc *disc);

void				ft_camera(t_data *data, t_vec4 position, t_vec4 lookat);

t_ray				ft_get_shadow_ray(t_ray *ray, t_light *source);
int					ft_reflected_ray(t_data *data, t_vec4 nr,
		t_ray *ray, t_ref refl);
int					ft_refracted_ray(t_data *data, t_vec4 nr,
		t_ray *ray, t_ref refr);

int					ft_color_rgb_scalar(int color, double r, double g,
		double b);
int					ft_color_add(int color1, int color2);
int					ft_color_avg(int *colors, int size);

int					ft_triangle_shader(t_data *data, t_ray *ray,
		t_triangle *triangle);
int					ft_ellipsoid_shader(t_data *data, t_ray *ray,
		t_ellipsoid *sp);
int					ft_hyperboloid_shader(t_data *data, t_ray *ray,
		t_hyper *hyper);
int					ft_paraboloid_shader(t_data *data, t_ray *ray, t_parab *t);
int					ft_h_cube_shader(t_data *data, t_ray *ray, t_h_cube *t);
int					ft_torus_shader(t_data *data, t_ray *ray, t_torus *t);
int					ft_hemisphere_shader(t_data *data, t_ray *ray,
		t_h_sphere *hp);
int					ft_color_mix(int color1, int color2, float percent);
int					ft_sphere_shader(t_data *data, t_ray *ray,
		t_sphere *sphere);
int					ft_plane_shader(t_data *data, t_ray *ray, t_plane *plane);
int					ft_cylinder_shader(t_data *data, t_ray *ray,
		t_cylinder *cylinder);
int					ft_disc_shader(t_data *data, t_ray *ray, t_disc *disc);
int					ft_cone_shader(t_data *data, t_ray *ray, t_cone *cone);

void				ft_camera_ray_dof(t_ray *ray, t_data *data,
		int *xy, int jitter);
void				ft_camera_ray_aa(t_ray *ray, t_data *data,
		int *xy, int jitter);
double				ft_ray_inter_objs(t_list *list, t_ray *sh_ray,
									double distance_to_light, t_light *li);
int					ft_compute_shader(int color, t_shader_x *sh_x,
		t_data *data);
t_shader_x			ft_ray_inter_lights(t_data *data, t_vec4 nr,
		t_ray *ray, t_vec4 *ds);
double				ft_distance_to_light(t_light *li, t_ray *sh_ray);
double				ft_light_intensity(t_list *scene, t_light *li,
									t_vec4 *inter_point, t_vec4 *shadow_ray);
short				ft_light_type(int i);
double				ft_min(double val, double min);
double				ft_max(double val, double max);

int					ft_box_inter(t_ray *ray, t_box *box);
int					ft_box_shader(t_data *data, t_ray *ray, t_box *box);

int					ft_fractal_texture(double *uv);
int					ft_texture_hemisphere(t_ray *ray, t_h_sphere *sp);
int					ft_texture_cone(t_ray *ray, t_cone *cone);
int					ft_texture_cylinder(t_ray *ray, t_cylinder *cyl);
int					ft_texture_plane(t_ray *ray, t_plane *pl);
int					ft_texture_sphere(t_ray *ray, t_sphere *sp);
int					ft_load_texture(int id, t_texture *t, t_data *data);
int					ft_texture_disc(t_ray *ray, t_disc *disc);
int					ft_pick_proc_texture(double *uv, t_texture *txt);

void				ft_filters(t_data *data, int x, int y, int color);
int					ft_filters_aa(t_data *data, int color);

typedef struct		s_function
{
	char			*type;
	void			(*call)();
}					t_function;

int					get_next_line(int fd, char **line);
double				ft_atof(char *nbr);

int					ft_expect_limited(char *line, char *name, t_limits *l);
int					ft_expect_vector(char *line, char *name, t_vec4 *vector);
int					ft_expect_intensity(char *line, char *name, t_light *light);
int					ft_expect_diffuse(char *line, char *name, t_vec4 *vector);
int					ft_expect_value(char *line, char *name, double *n);
int					ft_expect_color(char *line, char *name, int *color);
int					ft_expect_matrix(char *line, char *str, t_vec4 *vec);
int					ft_expect_ref(char *line, char *name, t_ref *ref);
int					ft_expect_area_uv(char *line, char *name, t_vec4 *uv_dir,
		unsigned short *uv_nodes);
int					ft_expect_spot_dot(char *line, char *name, float *spot_dot);
int					ft_expect_texture(char *line, char *name, t_texture *t);

int					ft_is_numeric(char *str);
size_t				ft_table_size(char **tab);
int					ft_is_limited(double n);
int					ft_bracket_control(char *str, char c);
void				ft_cheak_data(t_data *data);

char				*ft_error_type(int error);
void				ft_error_management(t_data *data, int error, void **to_free,
									int fd);

void				ft_get_scene_config(int fd, t_data *data);
void				ft_get_triangle_config(int fd, t_data *data);
void				ft_get_ellipsoid_config(int fd, t_data *data);
void				ft_get_hyperboloid_config(int fd, t_data *data);
void				ft_get_parab_config(int fd, t_data *data);
void				ft_get_h_cube_config(int fd, t_data *data);
void				ft_get_torus_config(int fd, t_data *data);
void				ft_get_hemisphere_config(int fd, t_data *data);
void				ft_get_camera_config(int fd, t_data *data);
void				ft_get_sphere_config(int fd, t_data *data);
void				ft_get_light_config(int fd, t_data *data);
void				ft_get_plane_config(int fd, t_data *data);
void				ft_get_cone_config(int fd, t_data *data);
void				ft_get_box_config(int fd, t_data *data);
void				ft_get_cylinder_config(int fd, t_data *data);
void				ft_get_disc_config(int fd, t_data *data);
void				ft_get_config(char *conf_file, t_data *data);
void				ft_del(void *content, size_t size);

void				ft_sphere_val_correction(t_sphere **sphere, t_data *data,
		int fd);
int					ft_texture_correction(t_texture *texture, t_data *data);
void				*ft_screenshot(void *param);
void				random_jitter(t_data *data, size_t size);
int					ft_islimited(t_ray *ray, double *t, t_cylinder *cyl);
int					ft_pick_distance(double *t, t_ray *ray, t_limits *limits);
int					ft_check_distance(double *t, t_ray *ray);
int					ft_limit_axis(double t, t_ray *ray, t_limits *limits);
int					ft_islimited(t_ray *ray, double *t, t_cylinder *cyl);
int					ft_brick_sphere(t_ray *ray, t_sphere *sp);

typedef struct		s_solution
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
	double			m;
	double			n;
	double			q;
	double			p;
	double			o;
	double			tmp;
}					t_solve;

int					ft_solve_equation_4(t_solve s, double *x);
int					ft_solve_equation_3(double *x, double a, double b,
		double c);
void				ft_sort_double_table(double *x);
char				*ft_error_type(int error);

#endif
