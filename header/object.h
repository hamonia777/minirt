#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef enum s_object_type
{
    PLANE,
    CYLINDER,
    SPHERE
} t_object_type;

typedef struct s_object
{
    t_object_type type;
    void *elements;
    struct s_object *next;
} t_object;

typedef struct s_camera
{
    t_point orig;
    t_vec dir;
    t_vec right_normal;
    t_vec up_normal;
    t_point left_bottom;
    double fov;
    double focal_len;
} t_camera;

typedef struct s_light
{
    t_point orig;
    double brightness;
    t_color color;
} t_light;

typedef struct s_ambient
{
    t_color color;
    double ambient;
} t_ambient;

typedef struct s_plane
{
    t_point center;
    t_vec normal;
    t_color color;
} t_plane;

typedef struct s_cylinder
{
    t_point center;
    t_vec axis;
    double diameter;
    double height;
    t_color color;
} t_cylinder;

typedef struct s_sphere
{
    t_point center;
    double diameter;
    t_color color;
} t_sphere;

typedef struct s_scene
{
    t_camera camera;
    t_light light;
    t_ambient ambient;
    t_object *object;
} t_scene;

t_vec parse_vec(char *str);
t_color parse_color(char *split);
double  ft_atod(char *str);
void	free_split(char **split);
t_scene *read_value(char **argv);
t_ambient   parse_ambient(char **split);
t_camera   parse_camera(char **split);
t_light   parse_light(char **split);
t_sphere   *parse_sphere(char **split);
t_plane   *parse_plane(char **split);
t_cylinder   *parse_cylinder(char **split);
t_object *new_object(t_object_type type, void *elements);
void add_object(t_object **obj, t_object *new_obj);
t_vec parse_unit_vec(char *split);
void printf_error(char *msg);
int split_count(char **split);
double parse_double(char *str);
#endif