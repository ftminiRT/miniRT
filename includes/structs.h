/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-29 13:03:19 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-08-29 13:03:19 by tcoeffet         ###   ########.fr       */
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
	t_vec3	pt;
	t_vec3	dir;
	double	hit;
	t_color	color;
}              t_ray;

typedef struct s_cam
{
	bool			is_set;
	t_vec3			pos;
	t_vec3			dir;
	unsigned char	fov;
}					t_cam;

typedef struct s_light
{
	bool			is_set;
	t_vec3			pos;
	double			brightness;
	t_color			color;
	struct s_light	*next;
}					t_light;

typedef struct s_phong
{
	t_vec3	light;
	t_vec3	view;
	t_vec3	reflected;
	t_vec3	normal;
}               t_phong;

typedef struct		s_cubic
{
	double			q;
	double			r;
	double			bq;
	double			br;
	double			bq3;
	double			br2;
	double			cr2;
	double			cq3;
	double			sqrtbq;
	double			sgnbr;
	double			ratio;
	double			theta;
	double			norm;
	double			r0;
	double			r1;
	double			r2;
	double			ba;
	double			bb;
	int				i;
}					t_cubic;

typedef struct		s_moebius
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
	double			f;
	double			g;
}					t_moebius;

typedef struct s_proj_data
{
	t_vec3	d_proj;
	t_vec3	oc_proj;
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sqrt_d;
}	t_proj_data;

# define OBJTYPENUMBER 9

typedef enum e_objtype
{
	OT_SPHERE,
	OT_PLANE,
	OT_CYL,
	OT_CONE,
	OT_TORE,
	OT_TRIANGLE,
	OT_PARA,
	OT_MOEB,
	OT_HYP,
}               t_objtype;

typedef enum    e_axis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS
}               t_axis;

typedef struct s_obj
{
	double			scal; // rayon
	double			scal2; // height du cylindre
	t_vec3			pt; // centre / pos
	t_vec3			pt2;
	t_vec3			pt3;
	double			a; // angle
	t_vec3			n; // normal
	double			max; //moebius
	t_objtype		type;
	t_color			color;
	double			shine;
	int				id;
	bool			checkered;
	struct s_obj	*next;
}               t_obj;

typedef struct s_mlxdata
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			hgt;
	int			wdt;
	int			scale;
	int			endian;
}					t_mlxdata;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_mlxdata	img;
}				t_mlx; 

typedef enum e_select_type
{
	CAM,
	SPOT,
	AMB,
	OBJ
}			t_select_type;


typedef struct s_select
{
	t_cam		*cam;
	t_obj		*obj;
	t_light		*spot;
	t_light		*amb;
	t_select_type	type;
}				t_select;

typedef struct s_env
{
	t_ray		ray;
	t_cam		cam;
	t_light		ambient;
	t_light		spot;
	t_obj		*objects;
	t_select	selected;
	double		(*hit_object[OBJTYPENUMBER + 1])(t_ray *, t_obj *);
	t_vec3		(*get_norm[OBJTYPENUMBER + 1])(t_obj *, t_vec3);
	t_mlx		mlx;
	int			log_fd;
}				t_env;

#endif