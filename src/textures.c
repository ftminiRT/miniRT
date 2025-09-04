#include "minirt.h"

int load_texture(void *mlx_ptr, t_obj *obj, char *filename)
{
    if (!mlx_ptr || !obj || !filename)
        return (0);

    obj->texture_img = mlx_xpm_file_to_image(mlx_ptr, filename,
        &obj->texture_width, &obj->texture_height);
    if (!obj->texture_img)
        return (0);
    obj->texture_data = mlx_get_data_addr(obj->texture_img,
                            &obj->texture_bpp,
                            &obj->texture_size_line,
                            &obj->texture_endian);
    return (1);
}

/**
 * Libère la mémoire d'une texture
 * @param mlx_ptr: Pointeur MLX
 * @param obj: Objet dont libérer la texture
 */
void	free_texture(void *mlx_ptr, t_obj *obj)
{
	if (!obj)
		return ;
	if (obj->texture_img)
	{
		mlx_destroy_image(mlx_ptr, obj->texture_img);
		obj->texture_img = NULL;
	}
	obj->texture_data = NULL;
	obj->texture_width = 0;
	obj->texture_height = 0;
	obj->texture_bpp = 0;
	obj->texture_size_line = 0;
	obj->texture_endian = 0;
	printf("Texture reset (MLX cleanup handled by clear_mlx)\n");
}

