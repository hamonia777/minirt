#include "../header/object.h"
#include "../header/vector.h"
#include <math.h>

t_ambient   parse_ambient(char **split)
{
    t_ambient ambient;
    if(split_count(split) != 3)
        printf_error("Error: Missing data in AMBIENT\n");    
    ambient.ambient = parse_double(split[1]);
    ambient.color = parse_color(split[2]);
    return ambient;
}

t_camera   parse_camera(char **split)
{
    t_camera camera;
    double theta;
    double aspect_ratio;

    if(split_count(split) != 4)
        printf_error("Error: Missing data in CAMERA\n");    
    camera.orig = parse_vec(split[1]);
    camera.dir = parse_unit_vec(split[2]);
    camera.fov = parse_double(split[3]);
    
    camera.focal_len = 1.0;
    aspect_ratio = 16.0 / 9.0; 
    theta = camera.fov * M_PI / 180.0;
    double h = tan(theta / 2.0);
    
    camera.viewport_height = 2.0 * h;
    camera.viewport_width = camera.viewport_height * aspect_ratio;
    camera.left_bottom = vec(0,0,0); 
    
    return camera;
}

t_light   parse_light(char **split)
{
    t_light light;
    if(split_count(split) != 4)
        printf_error("Error: Missing data in LIGHT\n");    
    light.orig = parse_vec(split[1]);
    light.brightness = parse_double(split[2]);
    light.color = parse_color(split[3]);
    return light;
}

t_sphere   *parse_sphere(char **split)
{
    t_sphere *sphere;
    if(split_count(split) != 4)
        printf_error("Error: Missing data in SPHERE\n");
    sphere = (t_sphere *)malloc(sizeof(t_sphere));
    if(!sphere)
        exit(1);    
    sphere->center = parse_vec(split[1]);
    sphere->diameter = parse_double(split[2]);
    sphere->color = parse_color(split[3]);
    return sphere;
}

t_plane   *parse_plane(char **split)
{
    t_plane *plane;
    plane = (t_plane *)malloc(sizeof(t_plane));
    if(!plane)
        exit(1);
    if(split_count(split) != 4)
        printf_error("Error: Missing data in PLANE\n");    
    plane->center = parse_vec(split[1]);
    plane->normal = parse_unit_vec(split[2]);
    plane->color = parse_color(split[3]);
    return plane;
}

t_cylinder   *parse_cylinder(char **split)
{
    t_cylinder *cylinder;
    cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
    if(!cylinder)
        exit(1);
    if(split_count(split) != 6)
        printf_error("Error: Missing data in CYLINDER\n");
    cylinder->center = parse_vec(split[1]);
    cylinder->axis = parse_unit_vec(split[2]);
    cylinder->diameter = parse_double(split[3]);
    cylinder->height = parse_double(split[4]);
    cylinder->color = parse_color(split[5]);
    return cylinder;
}