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
bool    hit_sphere(t_ray *r, t_sphere s);
bool    hit_plane(t_ray *r, t_plane p);
bool    hit_cylinder(t_ray *r, t_cyl cy);
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

#endif