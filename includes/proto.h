/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:22:57 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/21 00:31:14 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "structs.h"
# include "ui.h"

////////////// MLX ////////////////

int			clear_mlx(t_env *rt);
void		error_exit(char *msg);
void		rt_mlx_init(t_mlx *mlx);
int			key_pressed(int kc, t_env *e);
int			close_window(t_env *rt);
int			mouse_hook(int bt, int x, int y, t_env *e);
void		putpixel(int x, int y, t_env *rt, t_color c);
void		putpixel_ui(int x, int y, t_env *rt, t_color c);
void		putpixel_ui_img(int x, int y, t_color c, void *img);
t_mlxdata	*init_img(t_mlx *mlx, t_mlxdata *img, int x, int y);
void		putnbr_ui(t_env *rt, int x, int y, double nbr);

////////////// VEC3 LIB ////////////////

t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_scalmult(double scal, t_vec3 a);
void		vec3_normalize(t_vec3 *a);
double		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3_up(void);
t_vec3		vec3_right(void);
t_vec3		vec3_forward(void);
double		vec3_norm(t_vec3 a);
double		vec3_sqnorm(t_vec3 a);
t_vec3		vec3_normalized(t_vec3 a);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);
t_vec3		vec3_rot(t_vec3 *v, int axis, double theta);
void		vec3_rotate(t_vec3 *v, t_vec3 r);
void		move_vec3(t_vec3 *v, t_vec3 move);

////////////// HIT OBJ ////////////////

double		hit_sphere(t_ray *r, t_obj *s);
double		hit_plane(t_ray *r, t_obj *p);
double		hit_cylinder(t_ray *r, t_obj *cy);
int			inside_moebius(t_obj *m, t_vec3 h);
double		hit_moebius(t_ray *ray, t_obj *obj);
double		hit_torus(t_ray *ray, t_obj *obj);
double		hit_ring(t_ray *ray, t_obj *obj);
double		hit_cone(t_ray *ray, t_obj *obj);

////////////// UTILS ////////////////

t_basis		make_basis(t_vec3 n);
t_vec3		camera_transform(t_vec3 dir_local, t_vec3 cam_dir);
t_vec3		world_to_local_point(t_vec3 p, t_obj *obj, t_basis b);
t_vec3		world_to_local_vec(t_vec3 v, t_basis b);
t_vec3		local_to_world_vec(t_vec3 v, t_basis b);
t_ray		world_to_local_ray(t_ray r, t_obj *obj, t_basis b);
int			dblsgn(double x);

////////////// PARSING ////////////////

int			parsing(t_env *rt, char *file);

// check_values.c
int			check_brightness(double b);
int			check_norm(t_vec3 n);
int			count_arg(char **args);
// parsing_utils.c
double		ft_atod(char *str);
int			str_is_double(char *str);
int			str_to_vec3(t_vec3 *vec, char *str);
int			str_to_colors(t_color *clr, char *str);
// parsing_utils_bonus.c
int			set_shine(t_obj *new, char *arg);
int			set_texture(t_obj *new, char *arg);
int			set_normal_map(t_obj *new, char *arg);
int			set_reflect(t_obj *new, char *arg);
int			set_bonus_attributes(char **args, t_env *rt, t_obj *new);
// init_obj.c
t_obj		*create_object(t_env *rt);
int			init_cylinder(char **args, t_env *rt);
int			init_plane(char **args, t_env *rt);
int			init_sphere(char **args, t_env *rt);
// init_obj_bonus.c
int			init_moebius(char **args, t_env *rt);
int			init_tore(char **args, t_env *rt);
int			init_cone(char **args, t_env *rt);
int			init_ring(char **args, t_env *rt);
// init_set.c
int			init_cam(char **args, t_env *rt);
int			init_amblight(char **args, t_env *rt);
int			init_spotlight(char **args, t_env *rt);
void		env_init(t_env *rt);

/////////////// LIGHT COMPUTE /////////////

t_color		color_add(t_color c1, t_color c2);
t_color		color_scale(t_color c, double factor);
t_color		color_multiply(t_color c1, t_color c2);
t_color		color_clamp(t_color color);
t_color		get_color(t_env *rt, t_obj *obj, t_vec3 hit_point, t_ray ray);
t_color		get_checkered_color(t_env *rt, t_obj *obj, t_vec3 hit_point);
bool		in_shadow(t_env *rt, t_light *spot, t_vec3 hit_point);

/////////////// CORE COMPUTE /////////////

t_obj		*compute_intersections(t_env *rt, t_ray *ray);
void		compute_ray(t_env *rt, t_ray *ray, int i, int j);
void		ray_trace(t_env *rt);
t_color		trace_ray(t_env *rt, t_ray ray, int depth);
t_vec3		reflect(t_vec3 rdir, t_vec3 norm);
void		manage_reflect(t_env *rt, t_reflect_data *d, t_ray ray, int depth);

/////////////// UTILS /////////////

int			swapd(double *a, double *b);
t_vec3		null_vec(void);
t_uipt		btn_sz(void);
void		clear_buffer_gnl(int fd);

/////////////// OBJ NORMALS /////////////

t_vec3		sphere_normal(t_obj *obj, t_vec3 hit_point);
t_vec3		plane_normal(t_obj *obj, t_vec3 hit_point);
t_vec3		torus_normal(t_obj *obj, t_vec3 hit_point);
t_vec3		ring_normal(t_obj *obj, t_vec3 hit_point);
t_vec3		cylinder_normal(t_obj *obj, t_vec3 hit_point);
double		check_discs(t_obj *obj, t_vec3 hit_point);
t_vec3		moebius_normal(t_obj *obj, t_vec3 hit_point);
t_vec3		cone_normal(t_obj *obj, t_vec3 hit_point);

/////////////// CLEAN /////////////

void		clear_all_textures(t_env *rt);
void		mrt_cleaner(t_env *rt);
int			mega_clean(t_env *rt);
void		exit_from_export(t_vec3int info, t_env *rt, char *filename,
				char *error);
void		clean_panes(t_env *rt);
void		write_error(char *str, char *arg);

/////////////// INIT /////////////

void		normalize_objs(t_env *rt);
void		init_rt(t_env *rt);
void		print_set(t_env *rt);
void		init_base(t_obj *obj, t_basis *b);
void		init_quartic_solver(t_quartic *q, double *a);

/////////////// GALOIS ALGEBRA /////////////

int			solve_cubic(double *a, double *r);

void		print_set(t_env *rt);

/////////////// GALOIS ALGEBRA /////////////

int			solve_quadratic(double *a, double *r);
int			solve_cubic(double *a, double *r);
int			solve_quartic(double *a, double *r);
int			swapd(double *a, double *b);
void		set_d3(double *u, double u0, double u1, double u2);
int			deal_with_degenerate(double *a, double *r);
void		find_solution_to_resolvent_cubic(t_quartic *q);
void		handle_r_and_zarr(double *r, double *zarr);
void		deal_with_pos_disc(t_quartic *q);

/////////////// MAPPING /////////////

void		get_plane_uv(t_obj *obj, t_vec3 hit_point, int map[2]);
void		get_sphere_uv(t_obj *obj, t_vec3 hit_point, int map[2]);
void		get_torus_uv(t_obj *obj, t_vec3 hit_point, int map[2]);
void		get_moebius_uv(t_obj *obj, t_vec3 p, int map[2]);
void		get_ring_uv(t_obj *obj, t_vec3 hit_point, int map[2]);
void		get_cylinder_uv(t_obj *obj, t_vec3 hit_point, int map[2]);
void		get_cone_uv(t_obj *obj, t_vec3 hit_point, int map[2]);
int			load_normal_map(void *mlx_ptr, t_obj *obj, char *filename);
void		free_normal_map(void *mlx_ptr, t_obj *obj);
t_vec3		sample_normal_map(t_obj *obj, float u, float v);
t_vec3		sample_normal_map_filtered(t_obj *obj, float u, float v);
t_vec3		sample_normal_at_pixel(t_obj *obj, int x, int y);
t_vec3		apply_normal_mapping(t_vec3 geo_normal, t_vec3 tangent,
				t_vec3 bitangent, t_vec3 map_normal);
t_vec3		compute_sphere_tangent(t_vec3 normal);
void		compute_sphere_uv(t_vec3 normal, float *u, float *v);
void		init_object_no_normal_map(t_obj *obj);
int			load_texture(void *mlx_ptr, t_obj *obj, char *filename);
void		free_texture(void *mlx_ptr, t_obj *obj);
void		load_textures(t_env *rt);

/////////////// HOOKS /////////////

void		handle_exit(int kc, t_env *rt);
void		handle_selection(int kc, t_env *rt);
void		handle_movement(int kc, t_env *rt, double step, t_vec3 fwd);
void		handle_rotation(int kc, t_env *rt, double step);
void		rot_cam(int kc, t_env *rt, double step);
void		rot_obj(int kc, t_env *rt, double step);
void		handle_object_mod(int kc, t_env *rt, double step);
void		export_to_rt(t_env *rt);
void		handle_export(int kc, t_env *rt);
char		*get_next_export_filename(t_env *rt);

/////////////// OBJ TRANSFORMATION /////////////

void		move_selected(t_env *rt, t_vec3 move);
void		rotate_selected(t_env *rt, t_vec3 rot);

/////////////// INTERFACE /////////////

void		click_ui(int x, int y, t_env *rt);
void		display_ui(t_env *rt);
int			ui_init(t_env *rt);
int			init_ui_panes(t_env *rt);
void		init_pane_builders(t_env *rt);
t_items		*add_new_button(void *value, double factor, t_uipt pos,
				t_uipt scale);

/* Generic Builders*/

int			build_pane_color(void *rt, t_uipane *current);
int			build_pane_pos(void *rt, t_uipane *current, t_vec3 *pos, int y);
int			build_pane_dir(void *rt, t_uipane *current, t_vec3 *dir, int y);
int			build_pane_mat(void *rt, t_uipane *current, int y);

/******************/

int			build_pane_co(void *rt, t_uipane *current);
int			build_pane_cyl(void *rt, t_uipane *current);
int			build_pane_dft(void *rt, t_uipane *current);
int			build_pane_mo(void *rt, t_uipane *current);
int			build_pane_pl(void *rt, t_uipane *current);
int			build_pane_ri(void *rt, t_uipane *current);
int			build_pane_sp(void *rt, t_uipane *current);
int			build_pane_spot(void *rt, t_uipane *current);
int			build_pane_to(void *rt, t_uipane *current);
int			build_pane_events(void *rt, t_uipane *current);
t_uipt		pt(int x, int y);
t_items		setb(t_btn_data data, t_uipt pos, t_uipt scale);
void		add_back(t_items *new, t_uipane *pane);
int			add_btn(t_items og, t_uipane *pane);
void		build_local_basis(void *rt, t_basis *b);
int			fill_values_co(void *rt, t_uipane *cur);
int			fill_values_cy(void *rt, t_uipane *cur);
int			fill_values_dft(void *rt, t_uipane *cur);
int			fill_values_mo(void *rt, t_uipane *cur);
int			fill_values_pl(void *rt, t_uipane *cur);
int			fill_values_ri(void *rt, t_uipane *cur);
int			fill_values_sp(void *rt, t_uipane *cur);
int			fill_values_spot(void *rt, t_uipane *cur);
int			fill_values_to(void *rt, t_uipane *cur);
void		init_pane_fillers(t_env *rt);
void		init_pane_builders(t_env *rt);
void		init_pane_fillers(t_env *rt);
char		*dota(t_env *rt, double n);
t_uipane	*get_prev_spot(t_env *rt);
t_uipane	*get_next_spot(t_env *rt);
t_uipane	*get_spot(t_env *rt);
t_uipane	*get_default_pane_addr(t_env *rt);
void		exec_button(t_env *rt, t_items *itm);

#endif