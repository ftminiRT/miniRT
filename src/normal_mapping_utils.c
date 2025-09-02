
#include "minirt.h"

/**
 * Charge une normal map XPM sur un objet
 * @param mlx_ptr: Pointeur MLX
 * @param obj: Objet sur lequel charger la texture
 * @param filename: Nom du fichier XPM
 * @return: 1 si succès, 0 si échec
 */
int	load_normal_map(void *mlx_ptr, t_obj *obj, char *filename)
{
	if (!mlx_ptr || !obj || !filename)
		return (0);

	obj->normal_map_img = mlx_xpm_file_to_image(mlx_ptr, filename,
		&obj->normal_map_width, &obj->normal_map_height);
	
	if (!obj->normal_map_img)
	{
		printf("Erreur: Impossible de charger %s\n", filename);
		return (0);
	}
	
	obj->normal_map_data = mlx_get_data_addr(obj->normal_map_img,
		&obj->normal_map_bpp, &obj->normal_map_size_line, &obj->normal_map_endian);
	
	if (!obj->normal_map_data)
	{
		mlx_destroy_image(mlx_ptr, obj->normal_map_img);
		obj->normal_map_img = NULL;
		return (0);
	}
	
	printf("Normal map chargée: %dx%d pixels\n", 
		obj->normal_map_width, obj->normal_map_height);
	return (1);
}

/**
 * Libère la mémoire d'une normal map
 * @param mlx_ptr: Pointeur MLX
 * @param obj: Objet dont libérer la texture
 */
void	free_normal_map(void *mlx_ptr, t_obj *obj)
{
	if (!obj)
		return;
	
	(void)mlx_ptr;
	
	// Just reset pointers, let clear_mlx handle MLX destruction
	obj->normal_map_img = NULL;
	obj->normal_map_data = NULL;
	obj->normal_map_width = 0;
	obj->normal_map_height = 0;
	obj->normal_map_bpp = 0;
	obj->normal_map_size_line = 0;
	obj->normal_map_endian = 0;
	
	printf("Normal map reset (MLX cleanup handled by clear_mlx)\n");
}

/**
 * Sample une normale depuis la texture à des coordonnées UV données
 * @param obj: Objet avec la normal map
 * @param u: Coordonnée U [0,1]
 * @param v: Coordonnée V [0,1]
 * @return: Normale en tangent space [-1,1]
 */
t_vec3	sample_normal_map(t_obj *obj, float u, float v)
{
	t_vec3	map_normal;
	int		x, y, pixel;
	char	*data;

	// Valeur par défaut si pas de normal map
	if (!obj->normal_map_data)
		return ((t_vec3){0.0, 0.0, 1.0});
	
	// Clamp et wrap des coordonnées UV
	u = u - floor(u); // Wrap [0,1]
	v = v - floor(v);
	if (u < 0) u += 1.0;
	if (v < 0) v += 1.0;
	
	// Convertir en coordonnées pixel
	x = (int)(u * obj->normal_map_width) % obj->normal_map_width;
	y = (int)(v * obj->normal_map_height) % obj->normal_map_height;
	
	// Récupérer le pixel
	data = (char *)obj->normal_map_data;
	pixel = *(int *)(data + (y * obj->normal_map_size_line + x * (obj->normal_map_bpp / 8)));
	
	// Convertir RGB [0,255] vers normale [-1,1]
	// Format: R=X, G=Y, B=Z
	map_normal.x = ((pixel & 0xFF0000) >> 16) / 255.0 * 2.0 - 1.0;
	map_normal.y = ((pixel & 0x00FF00) >> 8) / 255.0 * 2.0 - 1.0;
	map_normal.z = (pixel & 0x0000FF) / 255.0 * 2.0 - 1.0;
	
	return (map_normal);
}

/**
 * Sample avec filtrage bilinéaire pour un rendu plus lisse
 * @param obj: Objet avec la normal map
 * @param u: Coordonnée U [0,1]
 * @param v: Coordonnée V [0,1]
 * @return: Normale interpolée en tangent space
 */
t_vec3	sample_normal_map_filtered(t_obj *obj, float u, float v)
{
	t_vec3	normal00, normal01, normal10, normal11;
	t_vec3	normal_top, normal_bottom, final_normal;
	float	fu, fv, iu, iv;
	float	x_exact, y_exact;
	int		x0, y0, x1, y1;

	if (!obj->normal_map_data)
		return ((t_vec3){0.0, 0.0, 1.0});
	
	// Wrap UV
	u = u - floor(u);
	v = v - floor(v);
	if (u < 0) u += 1.0;
	if (v < 0) v += 1.0;
	
	// Coordonnées exactes dans la texture
	x_exact = u * obj->normal_map_width;
	y_exact = v * obj->normal_map_height;
	
	// Coordonnées des 4 pixels voisins
	x0 = (int)x_exact % obj->normal_map_width;
	y0 = (int)y_exact % obj->normal_map_height;
	x1 = (x0 + 1) % obj->normal_map_width;
	y1 = (y0 + 1) % obj->normal_map_height;
	
	// Facteurs d'interpolation
	fu = x_exact - floor(x_exact);
	fv = y_exact - floor(y_exact);
	iu = 1.0 - fu;
	iv = 1.0 - fv;
	
	// Sample les 4 pixels
	normal00 = sample_normal_at_pixel(obj, x0, y0);
	normal01 = sample_normal_at_pixel(obj, x0, y1);
	normal10 = sample_normal_at_pixel(obj, x1, y0);
	normal11 = sample_normal_at_pixel(obj, x1, y1);
	
	// Interpolation bilinéaire
	normal_top = vec3_add(vec3_scalmult(iu, normal00), vec3_scalmult(fu, normal10));
	normal_bottom = vec3_add(vec3_scalmult(iu, normal01), vec3_scalmult(fu, normal11));
	final_normal = vec3_add(vec3_scalmult(iv, normal_top), vec3_scalmult(fv, normal_bottom));
	
	vec3_normalize(&final_normal);
	return (final_normal);
}

/**
 * Fonction helper pour sample_normal_map_filtered
 */
t_vec3	sample_normal_at_pixel(t_obj *obj, int x, int y)
{
	t_vec3	map_normal;
	int		pixel;
	char	*data;

	data = (char *)obj->normal_map_data;
	pixel = *(int *)(data + (y * obj->normal_map_size_line + x * (obj->normal_map_bpp / 8)));
	
	map_normal.x = ((pixel & 0xFF0000) >> 16) / 255.0 * 2.0 - 1.0;
	map_normal.y = ((pixel & 0x00FF00) >> 8) / 255.0 * 2.0 - 1.0;
	map_normal.z = (pixel & 0x0000FF) / 255.0 * 2.0 - 1.0;
	
	return (map_normal);
}

/**
 * Calcule un vecteur tangent stable pour une sphère
 * @param normal: Normale géométrique de la sphère
 * @return: Vecteur tangent orthogonal
 */
t_vec3	compute_sphere_tangent(t_vec3 normal)
{
	t_vec3	tangent;
	t_vec3	up = {0, 1, 0};
	t_vec3	right = {1, 0, 0};
	
	// Éviter le cas dégénéré aux pôles
	if (fabs(vec3_dot(normal, up)) > 0.9)
		tangent = vec3_cross(normal, right);
	else
		tangent = vec3_cross(normal, up);
	
	vec3_normalize(&tangent);
	return (tangent);
}

/**
 * Calcule les coordonnées UV sphériques
 * @param normal: Normale géométrique normalisée
 * @param u: Pointeur vers coordonnée U [0,1]
 * @param v: Pointeur vers coordonnée V [0,1]
 */
void	compute_sphere_uv(t_vec3 normal, float *u, float *v)
{
	*u = atan2(normal.z, normal.x) / (2.0 * M_PI) + 0.5;
	*v = asin(fmax(-1.0, fmin(1.0, normal.y))) / M_PI + 0.5;
	
	// Assurer que les coordonnées sont dans [0,1]
	if (*u < 0) *u += 1.0;
	if (*v < 0) *v += 1.0;
	if (*u > 1) *u -= 1.0;
	if (*v > 1) *v -= 1.0;
}

/**
 * Initialise un objet sans normal map
 * @param obj: Objet à initialiser
 */
void	init_object_no_normal_map(t_obj *obj)
{
	obj->normal_map_img = NULL;
	obj->normal_map_data = NULL;
	obj->normal_map_width = 0;
	obj->normal_map_height = 0;
	obj->normal_map_bpp = 0;
	obj->normal_map_size_line = 0;
	obj->normal_map_endian = 0;
}