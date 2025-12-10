#include "header/vector.h"

t_vec vec(double x,double y, double z)
{
    t_vec vec;

    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

t_vec vplus(t_vec v1, t_vec v2)
{
    t_vec vec;

    vec.x = v1.x + v2.x;
    vec.y = v1.y + v2.y;
    vec.z = v1.z + v2.z;
    return vec;
}

t_vec vminus(t_vec v1, t_vec v2)
{
    t_vec vec;
    
    vec.x = v1.x - v2.x;
    vec.y = v1.y - v2.y;
    vec.z = v1.z - v2.z;
    return vec;
}

t_vec vmult(t_vec vec, double i)
{
    t_vec new_vec;

    new_vec.x = vec.x * i;
    new_vec.y = vec.y * i;
    new_vec.z = vec.z * i;
    return new_vec;
}

double      vdot(t_vec vec, t_vec vec2)
{
    return (vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z);
}

t_vec      vcross(t_vec vec, t_vec vec2)
{
    t_vec new;

    new.x = vec.y * vec2.z - vec.z * vec2.y;
    new.y = vec.z * vec2.x - vec.x * vec2.z;
    new.z = vec.x * vec2.y - vec.y * vec2.x;
    return (new);
}

t_vec      vunit(t_vec vec)
{
    double len = vlength(vec);
    if (len == 0)
    {
        printf("Error\n:Devider is 0");
        exit(0);
    }
    vec.x /= len;
    vec.y /= len;
    vec.z /= len;
    return (vec);
}

double      vlength2(t_vec vec)
{
    return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double      vlength(t_vec vec)
{
    return (sqrt(vlength2(vec)));
}