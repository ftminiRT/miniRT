#include "minirt.h"

t_vec3  vec3_up()
{
    return ((t_vec3) {1, 0, 0});
}

t_vec3  vec3_right()
{
    return ((t_vec3) {0, 1, 0});
}

t_vec3  vec3_forward()
{
    return ((t_vec3) {0, 0, 1});
}
