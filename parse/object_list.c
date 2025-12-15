#include "../header/object.h"
#include <stdlib.h>

t_object *new_object(t_object_type type, void *elements)
{
    t_object *obj;
    t_color albedo;

    obj = (t_object *)malloc(sizeof(t_object));
    if(!obj)
        return (NULL);
    obj->next = NULL;
    obj->elements = elements;
    obj->type = type;
    
    if (type == SPHERE)
    {
        t_sphere *sp = (t_sphere *)elements;
        albedo = vdivide(sp->color, 255.0);
    }
    else if (type == PLANE)
    {
        t_plane *pl = (t_plane *)elements;
        albedo = vdivide(pl->color, 255.0);
    }
    else if (type == CYLINDER)
    {
        t_cylinder *cy = (t_cylinder *)elements;
        albedo = vdivide(cy->color, 255.0);
    }
    else
    {
        albedo = color3(1.0, 1.0, 1.0);
    }
    
    obj->albedo = albedo;
    return obj;
}

t_object *object_last(t_object *obj)
{
    if(!obj)
        return (NULL);
    while(obj->next)
        obj = obj->next;
    return (obj);
}

void add_object(t_object **obj, t_object *new_obj)
{
    t_object *last;

    if (!obj || !new_obj)
        return ;
    if (*obj == NULL)
    {
        *obj = new_obj;
        return ;
    }
    last = object_last(*obj);
    last->next = new_obj;   
}