#include "../header/vector.h"
#include "../header/trace.h"
#include "../header/object.h"

t_bool hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
    t_sphere *sp;
    t_vec oc;
    double a;
    double half_b;
    double c;
    double discriminant;
    double sqrtd;
    double root;

    // if (!obj || !obj->element)
    //     return (FALSE);
    sp = sp_obj->elements;
    oc = vminus(ray->orig, sp->center);
    a = vlength2(ray->dir);
    half_b = vdot(oc, ray->dir);
    c = vlength2(oc) - sp->radius2;
    discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return (FALSE);
    sqrtd = sqrt(discriminant);
    root = (-half_b - sqrtd) / a;
    if (root < rec->tmin || rec->tmax < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < rec->tmin || rec->tmax < root)
            return (FALSE);
    }
    rec->t = root;
    rec->p = ray_at(ray, root);
    rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
    set_face_normal(ray, rec);
    rec->albedo = sp_obj->albedo;
    return (TRUE);
}