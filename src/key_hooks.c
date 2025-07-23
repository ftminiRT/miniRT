#include "minirt.h"

int     key_pressed(int kc, t_env *e)
{
    if (kc == KEY_ESC && clear_mlx(e))
        exit (1);
    return (1);
}