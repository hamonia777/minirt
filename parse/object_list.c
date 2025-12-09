#include "../header/object.h"
#include <stdlib.h>

t_object *new_object(t_object_type type, void *elements)
{
    t_object *obj;

    obj = (t_object *)malloc(sizeof(t_object));
    if(!obj)
        return (NULL);
    obj->next = NULL;
    obj->elements = elements;
    obj->type = type;
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