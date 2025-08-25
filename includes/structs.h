/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:22:58 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 19:56:37 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	alpha;
}					t_color;

typedef struct s_ray
{
    t_vec3      pt;
    t_vec3      dir;
    double      hit;
    t_color     color;
}              t_ray;

typedef struct s_cam
{
    bool            is_set;
	t_vec3			pos;
	t_vec3			dir;
	unsigned char	fov;
}					t_cam;

typedef struct s_light
{
    bool            is_set;
	t_vec3			pos;
	double			brightness;
	t_color			color;
}					t_light;

typedef struct s_sphere
{
	t_vec3			center;
	double			r;
}					t_sphere;

typedef struct  s_plane
{
    t_vec3      pt;
    t_vec3      n;
}               t_plane;

typedef struct s_cyl
{
	t_vec3			center;
	t_vec3			n;
	double			r;
	double			height;

}					t_cyl;

typedef enum e_objtype
{
    OT_SPHERE,
    OT_PLANE,
    OT_CYL
}               t_objtype;

typedef enum    e_axis
{
    X_AXIS,
    Y_AXIS,
    Z_AXIS
}               t_axis;

typedef struct s_obj
{
    t_sphere    sphere;
    t_plane     plane;
    t_cyl       cyl;
    t_objtype   type;
    t_color     color;
    int         id;
}               t_obj;

typedef struct s_list_obj
{
    t_obj       obj;
    struct s_list_obj  *next;
}               t_list_obj;

typedef struct s_mlxdata
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				hgt;
	int				wdt;
	int				scale;
	int				endian;
}					t_mlxdata;

typedef struct s_mlx
{
    void        *mlx;
    void        *win;
    t_mlxdata   img;
}               t_mlx; 

typedef struct s_env
{
    t_ray       ray;
    t_cam       cam;
    t_light     ambient;
    t_light     spot;
    t_list_obj  *objects;
    t_mlx       mlx;
}               t_env;

#endif