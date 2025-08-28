/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:22:57 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/08/28 14:12:20 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

int		clear_mlx(t_env *rt);
void	error_exit(char *msg);
void	rt_mlx_init(t_mlx *mlx);
int		key_pressed(int kc, t_env *e);

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
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	hit_sphere(t_ray *r, t_obj *s);
double	hit_plane(t_ray *r, t_obj *p);
double	hit_cylinder(t_ray *r, t_obj *cy);
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

/////////////// CORE COMPUTE /////////////

t_obj    *compute_intersections(t_env *rt, t_ray *ray);

/////////////// NORM COMPUTE /////////////

t_vec3  sphere_norm(t_obj *obj, t_vec3 hit_point);
t_vec3  plane_norm(t_obj *obj, t_vec3 hit_point);
double     check_discs(t_obj *obj, t_vec3 hit_point);
t_vec3  cylinder_norm(t_obj *obj, t_vec3 hit_point);

/////////////// INIT /////////////

void	normalize_objs_normal(t_env *rt);
void	init_rt(t_env *rt);

#endif