/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:22:57 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/02 21:48:24 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "minirt.h"

////////////// MLX ////////////////


int		clear_mlx(t_env *rt);
void	error_exit(char *msg);
void	rt_mlx_init(t_mlx *mlx);
int		key_pressed(int kc, t_env *e);
int	    close_window(t_env *rt);
int	    mouse_hook(int bt, int x, int y, t_env *e);


t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scalmult(double scal, t_vec3 a);
void	vec3_normalize(t_vec3 *a);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_up(void);
t_vec3	vec3_right(void);
t_vec3	vec3_forward(void);
double	vec3_norm(t_vec3 a);
double	vec3_sqnorm(t_vec3 a);
t_vec3	vec3_normalized(t_vec3 a);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	hit_sphere(t_ray *r, t_obj *s);
double	hit_plane(t_ray *r, t_obj *p);
double	hit_cylinder(t_ray *r, t_obj *cy);
double	hit_moebius(t_ray *ray, t_obj *obj);
t_vec3	camera_transform(t_vec3 dir_local, t_vec3 cam_dir);
void	ray_trace(t_env *rt);
void	putpixel(int x, int y, t_env *rt, t_color c);
t_vec3	vec3_rot(t_vec3 *v, int axis, double theta);
void	vec3_rotate(t_vec3 *v, t_vec3 r);

////////////// PARSING ////////////////

int		parsing(t_env *rt, char *file);

//check_values.c
int		check_brightness(double b);
int		check_norm(t_vec3 n);
int		count_arg(char **args);
//parsing_utils.c
double	ft_atod(char *str);
int		str_is_double(char *str);
int		str_to_vec3(t_vec3 *vec, char *str);
int		str_to_colors(t_color *clr, char *str);
//parsing_utils_bonus.c
int		set_shine(t_obj *new, char *arg);
//init_obj.c
t_obj	*create_object(t_env *rt);
int		init_cylinder(char **args, t_env *rt);
int		init_plane(char **args, t_env *rt);
int		init_sphere(char **args, t_env *rt);
//init_obj_bonus.c
int		init_boloid(char **args, t_env *rt, t_objtype type);
int		init_moebius(char **args, t_env *rt);
int		init_triangle(char **args, t_env *rt);
int		init_tore(char **args, t_env *rt);
int		init_cone(char **args, t_env *rt);
//init_set.c
int		init_cam(char **args, t_env *rt);
int		init_amblight(char **args, t_env *rt);
int		init_spotlight(char **args, t_env *rt);
void	env_init(t_env *rt);

/////////////// LIGHT COMPUTE /////////////

t_color	color_add(t_color c1, t_color c2);
t_color	color_scale(t_color c, double factor);
t_color	color_multiply(t_color c1, t_color c2);
t_color	color_clamp(t_color color);
t_vec3	get_normal(t_obj *obj, t_vec3 hit_point);
t_color	get_color(t_env *rt, t_obj *obj, t_vec3 hit_point);
t_color get_checkered_color(t_env *rt, t_obj *obj, t_vec3 hit_point);
t_color shade_phong(t_env *rt, t_obj *obj, t_vec3 hit_point, t_vec3 light_pos, t_vec3 cam_pos);
/////////////// CORE COMPUTE /////////////

t_obj	*compute_intersections(t_env *rt, t_ray *ray);
void	compute_ray(t_env *rt, t_ray *ray, int i, int j);

/////////////// NORM COMPUTE /////////////

t_vec3	sphere_normal(t_obj *obj, t_vec3 hit_point);
t_vec3	plane_normal(t_obj *obj, t_vec3 hit_point);
double	check_discs(t_obj *obj, t_vec3 hit_point);
t_vec3	cylinder_normal(t_obj *obj, t_vec3 hit_point);
t_vec3	moebius_normal(t_obj *obj, t_vec3 hit_point);

/////////////// CLEAN /////////////

void	mrt_cleaner(t_env *rt);

/////////////// INIT /////////////

void	normalize_objs(t_env *rt);
void	init_rt(t_env *rt);

int		solve_cubic(double *a, double *r);

void	debug_print_set(t_env *rt);

/////////////// NORMAL MAP /////////////

int	load_normal_map(void *mlx_ptr, t_obj *obj, char *filename);
void	free_normal_map(void *mlx_ptr, t_obj *obj);
t_vec3	sample_normal_map(t_obj *obj, float u, float v);
t_vec3	sample_normal_map_filtered(t_obj *obj, float u, float v);
t_vec3	sample_normal_at_pixel(t_obj *obj, int x, int y);
t_vec3	apply_normal_mapping(t_vec3 geo_normal, t_vec3 tangent, t_vec3 bitangent, t_vec3 map_normal);
t_vec3	compute_sphere_tangent(t_vec3 normal);
void	compute_sphere_uv(t_vec3 normal, float *u, float *v);
void	init_object_no_normal_map(t_obj *obj);


#endif