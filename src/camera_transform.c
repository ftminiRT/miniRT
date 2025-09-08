#include "minirt.h"

t_vec3	camera_transform(t_vec3 dir_local, t_vec3 cam_dir)
{
	t_vec3	forward;
	t_vec3	up_ref;
	t_vec3	right;
	t_vec3	up;
	t_vec3	world_dir;

	forward = cam_dir;
	vec3_normalize(&forward);
	if (fabs(forward.y) > 0.99)
		up_ref = (t_vec3){0, 0, 1};
	else
		up_ref = (t_vec3){0, 1, 0};
	right = vec3_cross(forward, up_ref);
	vec3_normalize(&right);
	up = vec3_cross(right, forward);
	vec3_normalize(&up);
	world_dir.x = dir_local.x * right.x + dir_local.y * up.x + dir_local.z
		* forward.x;
	world_dir.y = dir_local.x * right.y + dir_local.y * up.y + dir_local.z
		* forward.y;
	world_dir.z = dir_local.x * right.z + dir_local.y * up.z + dir_local.z
		* forward.z;
	return (world_dir);
}
