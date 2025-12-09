#include "header/object.h"
#include "header/minirt.h"
#include <stdio.h>
void print_vec(char *name, t_vec vec)
{
    printf("%s: [%.2f, %.2f, %.2f]\n", name, vec.x, vec.y, vec.z);
}

void print_scene(t_scene *scene)
{
    printf("===== SCENE DATA =====\n");

    printf("[Ambient]\n");
    printf("\tRatio: %.2f\n", scene->ambient.ambient);
    print_vec("\tColor", scene->ambient.color);

    printf("[Camera]\n");
    print_vec("\tOrigin", scene->camera.orig);
    print_vec("\tDir", scene->camera.dir);
    printf("\tFOV: %.2f\n", scene->camera.fov);

    printf("[Light]\n");
    print_vec("\tOrigin", scene->light.orig);
    printf("\tBrightness: %.2f\n", scene->light.brightness);
    print_vec("\tColor", scene->light.color);

    printf("[Objects]\n");
    t_object *current = scene->object;
    int i = 0;

    while (current)
    {
        printf("  -> Object %d: ", i++);
        if (current->type == SPHERE)
        {
            t_sphere *sp = (t_sphere *)current->elements;
            printf("SPHERE\n");
            print_vec("\tCenter", sp->center);
            printf("\tDiameter: %.2f\n", sp->diameter);
            print_vec("\tColor", sp->color);
        }
        else if (current->type == PLANE)
        {
            t_plane *pl = (t_plane *)current->elements;
            printf("PLANE\n");
            print_vec("\tCenter", pl->center);
            print_vec("\tNormal", pl->normal);
            print_vec("\tColor", pl->color);
        }
        else if (current->type == CYLINDER)
        {
            t_cylinder *cy = (t_cylinder *)current->elements;
            printf("CYLINDER\n");
            print_vec("\tCenter", cy->center);
            print_vec("\tAxis", cy->axis);
            printf("\tDiameter: %.2f, Height: %.2f\n", cy->diameter, cy->height);
            print_vec("\tColor", cy->color);
        }
        current = current->next;
    }
    printf("======================\n");
}