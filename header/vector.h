#ifndef VEC_H
#define VEC_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct s_vec
{
    double x;
    double y;
    double z;
} t_vec;

typedef t_vec t_point;
typedef t_vec t_color;

t_vec vec(double x, double y, double z);
t_vec vplus(t_vec v1, t_vec v2);
t_vec vminus(t_vec v1, t_vec v2);
t_vec vmult(t_vec vec, double i);
t_vec      vcross(t_vec vec, t_vec vec2);
t_vec      vunit(t_vec vec);
double      vlength2(t_vec vec);
double      vlength(t_vec vec);
double      vdot(t_vec vec, t_vec vec2);


#endif