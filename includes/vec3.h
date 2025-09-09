#ifndef VEC3_H
# define VEC3_H

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct s_vec3int
{
	int				x;
	int				y;
	int				z;
}					t_vec3int;

typedef struct s_basis
{
    t_vec3          u;
    t_vec3          v;
    t_vec3          w;
}               t_basis;


#endif