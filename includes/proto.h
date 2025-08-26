/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:22:57 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 19:54:47 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

int	clear_mlx(t_env *rt);
void    error_exit(char *msg);
void    rt_mlx_init(t_mlx *mlx);
int     key_pressed(int kc, t_env *e);

t_vec3  vec3_add(t_vec3 a, t_vec3 b);
t_vec3  vec3_sub(t_vec3 a, t_vec3 b);
t_vec3  vec3_scalmult(double scal, t_vec3 a);
void    vec3_normalize(t_vec3 *a);
double  vec3_dot(t_vec3 a, t_vec3 b);
t_vec3  vec3_up();
t_vec3  vec3_right();
t_vec3  vec3_forward();
double  vec3_norm(t_vec3 a);
double  vec3_sqnorm(t_vec3 a);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
double    hit_sphere(t_ray *r, t_obj *s);
double    hit_plane(t_ray *r, t_obj *p);
double    hit_cylinder(t_ray *r, t_obj *cy);
t_vec3 camera_transform(t_vec3 dir_local, t_vec3 cam_dir);
void    ray_trace(t_env *rt);
void	putpixel(int x, int y, t_env *rt, t_color c);
t_vec3  vec3_rot(t_vec3 *v, int axis, double theta);
void    vec3_rotate(t_vec3 *v, t_vec3 r);

////////////// PARSING ////////////////

int		parsing(t_env *rt, char *file);

//parsing_utils.c
double	ft_atod(char *str);
int		str_to_vec3(t_vec3 *vec, char *str);
int		str_to_colors(t_color *clr, char *str);

//init_obj.c
int		init_cylinder(char **args, t_env *rt);
int		init_plane(char **args, t_env *rt);
int		init_sphere(char **args, t_env *rt);
//init_set.c
int		init_cam(char **args, t_env *rt);
int		init_amblight(char **args, t_env *rt);
int		init_spotlight(char **args, t_env *rt);
void    env_init(t_env *rt);

/////////////// LIGHT COMPUTE /////////////
t_vec3 get_normal(t_obj *obj, t_vec3 hit_point);
double calculate_diffuse(t_vec3 normal, t_vec3 light_dir);
double calculate_specular(t_vec3 normal, t_vec3 light_dir, t_vec3 view_dir, double shininess);
t_color calculate_lighting(t_env *rt, t_obj *obj, t_vec3 hit_point, t_vec3 ray_dir);
t_color simple_lighting(t_env *rt, t_obj *obj, t_vec3 hit_point);

/////////////// CORE COMPUTE /////////////

t_obj    *compute_intersections(t_env *rt, t_ray *ray);


t_color color_add(t_color c1, t_color c2)

t_color color_scale(t_color c, double factor)

t_color	calc_ambient(t_color base, t_color amb, double bright)

t_color	calc_diffuse_spec(t_env *rt, t_obj *obj,

#endif