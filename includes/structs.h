/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:03:19 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/09 23:14:29 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minirt.h"
# include "vec3.h"
# include "ui.h"

typedef struct s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}						t_color;

typedef struct s_ray
{
	t_vec3				pt;
	t_vec3				dir;
	double				hit;
	t_color				color;
}						t_ray;

typedef struct s_cam
{
	bool				is_set;
	t_vec3				pos;
	t_vec3				dir;
	t_basis				local_basis;
	unsigned char		fov;
}						t_cam;

typedef struct s_light
{
	size_t				index;
	bool				is_set;
	t_vec3				pos;
	double				brightness;
	t_color				color;
	t_basis				local_basis;
	struct s_light		*next;
}						t_light;

typedef struct s_phong
{
	t_vec3				light;
	t_vec3				view;
	t_vec3				reflected;
	t_vec3				normal;
	t_color				diffuse;
	t_color				specular;
}						t_phong;

typedef struct s_normap
{
	double				scale_u;
	double				scale_v;
	double				u;
	double				v;
	double				h;
	t_vec3				tangent;
	t_vec3				bitangent;
}						t_normap;

typedef struct s_cubic
{
	double				q;
	double				r;
	double				bq;
	double				br;
	double				bq3;
	double				br2;
	double				cr2;
	double				cq3;
	double				sqrtbq;
	double				sgnbr;
	double				ratio;
	double				theta;
	double				norm;
	double				r0;
	double				r1;
	double				r2;
	double				ba;
	double				bb;
	int					i;
}						t_cubic;

typedef struct s_quartic
{
	double				u[3];
	double				v[3];
	double				zarr[4];
	double				args[3];
	double				aa;
	double				pp;
	double				qq;
	double				rr;
	double				rc;
	double				sc;
	double				tc;
	double				mt;
	double				w1r;
	double				w1i;
	double				w2r;
	double				w2i;
	double				w3r;
	double				v1;
	double				v2;
	double				arg;
	double				theta;
	double				disc;
	double				h;
	double				qcub;
	double				rcub;
	double				bq;
	double				br;
	double				bq3;
	double				br2;
	double				cr2;
	double				cq3;
	double				sqrtbq;
	double				sqrtbq3;
	double				sgnbr;
	double				modbr;
	double				norm;
	double				sqrt_disc;
	double				ba;
	double				bb;
	double				mod_diffbabb;
	int					k1;
	int					k2;
}						t_quartic;

typedef struct s_moebius
{
	double				a;
	double				b;
	double				c;
	double				d;
	double				e;
	double				f;
	double				g;
}						t_moebius;

typedef struct s_moebnorm
{
	double				t;
	double				s;
	t_vec3				dp_dt;
	t_vec3				dp_ds;
}				t_moebnorm;

typedef struct s_torusnorm
{
	t_basis		b;
	t_vec3		local_hit;
	t_vec3		center_to_hit;
	t_vec3		center_ring;
	double		br;
	double		r;
}				t_torusnorm;

typedef struct s_ring
{
	t_vec3				ro;
	t_vec3				rd;
	double				br;
	double				r;
	double				dd;
	double				e;
	double				f;
	double				four_br2;
}						t_ring;

typedef struct s_ring_uv
{
	t_vec3				u_axis;
	t_vec3				v_axis;
	t_vec3				w_axis;
	t_vec3				rel;
	t_vec3				local;
	double				theta;
	double				u;
	double				v;
	double				phi;
}						t_ring_uv;

typedef struct s_proj_data
{
	t_vec3				d_proj;
	t_vec3				oc_proj;
	double				a;
	double				b;
	double				c;
	double				delta;
	double				sqrt_d;
}						t_proj_data;

typedef enum e_objtype
{
	OT_DFT,
	OT_SPHERE,
	OT_PLANE,
	OT_CYL,
	OT_CONE,
	OT_TORE,
	OT_MOEB,
	OT_RING,
	OT_LIGHT
}						t_objtype;

typedef enum e_axis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS
}						t_axis;

/*
** OBJETS
** SPHERE
**	-> scal = rayon
**	-> pt = centre
** PLAN
**	-> pt = un pt du plan
**	-> n = normale du plan
** CYLINDRE
**	-> scal = rayon du tronc
**	-> scal2 = hauteur du cylindre
**	-> n = direction du cylindre
** MOEBIUS
**	-> scal = rayon
**	-> max = largeur de la bande
**	-> pt = centre de la nappe (la ou ca se replie dessus)
**	-> a = angle d'ouverture de la nappe jcrois pas sur que ce soit utile apres
**	-> n = direction de la nappe
**
**	Tous les objets ont une couleur, une brillance (shine), un id et un type
*/

typedef struct s_obj
{
	double				scal;
	double				scal2;
	double				scal3;
	double				k;
	t_vec3				pt;
	t_vec3				pt2;
	t_vec3				pt3;
	double				a;
	t_vec3				n;
	double				max;
	double				reflect;
	t_objtype			type;
	t_color				color;
	t_color				t_color;
	double				shine;
	int					id;
	t_basis				local_basis;
	char				*texture_filename;
	int					texture_width;
	int					texture_height;
	void				*texture_data;
	void				*texture_img;
	int					texture_size_line;
	int					texture_bpp;
	int					texture_endian;
	char				*normal_map_filename;
	void				*normal_map_img;
	void				*normal_map_data;
	int					normal_map_width;
	int					normal_map_height;
	int					normal_map_bpp;
	int					normal_map_size_line;
	int					normal_map_endian;
	bool				checkered;
	struct s_obj		*next;
}						t_obj;

typedef struct s_mlxdata
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					hgt;
	int					wdt;
	int					scale;
	int					endian;
}						t_mlxdata;

typedef struct s_reflect_data
{
	t_obj				*hitted;
	t_vec3				hit_point;
	t_color				local_color;
	t_color				reflected_color;
	t_vec3				normal;
	t_vec3				reflected;
	t_ray				reflected_ray;

}						t_reflect_data;

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	t_mlxdata			img;
	t_mlxdata			ui;
}						t_mlx;

typedef enum e_select_type
{
	CAM,
	SPOT,
	AMB,
	OBJ
}						t_select_type;

typedef struct s_select
{
	t_cam				*cam;
	t_obj				*obj;
	t_light				*spot;
	t_light				*amb;
	t_select_type		type;
}						t_select;

typedef struct s_env	t_env;
typedef struct s_ui		t_ui;
typedef double			(*t_hit_funcs[OBJTYPENUMBER])(t_ray *, t_obj *);
typedef t_vec3			(*t_get_norm[OBJTYPENUMBER])(t_obj *, t_vec3);
typedef void			(*t_get_uv[OBJTYPENUMBER])(t_obj *, t_vec3,
				int map[2]);

typedef struct s_env
{
	t_ray				ray;
	t_cam				cam;
	t_light				ambient;
	t_light				spot;
	t_obj				*objects;
	t_select			selected;
	t_hit_funcs			hit_object;
	t_get_norm			get_norm;
	t_get_uv			get_uv;
	t_mlx				mlx;
	t_ui				ui;
	size_t				nb_spots;
	bool				render;
	int					log_fd;
}						t_env;

#endif