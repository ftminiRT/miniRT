/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:22:58 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/08/28 11:57:18 by tbeauman         ###   ########.fr       */
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
    struct s_light  *next;
}					t_light;

typedef struct s_phong
{
    t_vec3      light;
    t_vec3      view;
    t_vec3      reflected;
    t_vec3      normal;
}               t_phong;


typedef enum e_objtype
{
    OT_SPHERE,
    OT_PLANE,
    OT_CYL,
    OT_CONE,
    OT_TORE,
    OT_TRIANGLE,
    OT_PARA,
    OT_HYP,
    OT_MOEB
}               t_objtype;

typedef enum    e_axis
{
    X_AXIS,
    Y_AXIS,
    Z_AXIS
}               t_axis;

typedef struct s_obj
{
    double      scal; // rayon
    double      scal2; // height du cylindre
    t_vec3      pt; // centre / pos
    t_vec3      pt2;
    t_vec3      pt3;
    double      a; // angle
    t_vec3      n; // normal
    t_objtype   type;
    t_color     color;
    double      shine;
    int         id;
    struct s_obj    *next;
}               t_obj;

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
    t_obj      *objects;
    double      (*hit_object[sizeof(t_objtype)])(t_ray *, t_obj *);
    t_vec3      (*get_norm[sizeof(t_objtype)])(t_obj *, t_vec3);
    t_mlx       mlx;
    int         log_fd;
}               t_env;

#endif