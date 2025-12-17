#include "../header/vector.h"
#include "../header/trace.h"
#include "../header/object.h"
#include <math.h>

t_bool hit_cap(t_object *cy_obj, t_ray *ray, t_hit_record *rec, t_vec center, t_vec normal)
{
    t_cylinder *cy = cy_obj->elements;
    double denom;
    double t;
    t_vec p;
    t_vec cp; // center to point

    denom = vdot(ray->dir, normal);
    if (fabs(denom) < 1e-6)
        return (FALSE);

    t = vdot(vminus(center, ray->orig), normal) / denom;

    if (t < rec->tmin || t > rec->tmax)
        return (FALSE);

    p = ray_at(ray, t);
    cp = vminus(p, center);
    if (vlength2(cp) > cy->radius2)
        return (FALSE);

    rec->t = t;
    rec->p = p;
    rec->normal = normal; // 뚜껑의 법선은 일정함
    set_face_normal(ray, rec);
    rec->albedo = cy_obj->albedo;
    return (TRUE);
}

t_bool hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
    t_cylinder *cy = cy_obj->elements;
    t_vec oc;
    double a, half_b, c, discriminant;
    double sqrtd, root, h;
    t_bool hit_any = FALSE; // 충돌 여부 플래그

    oc = vminus(ray->orig, cy->center);
    a = vlength2(ray->dir) - pow(vdot(ray->dir, cy->n), 2);
    half_b = vdot(ray->dir, oc) - (vdot(ray->dir, cy->n) * vdot(oc, cy->n));
    c = vlength2(oc) - pow(vdot(oc, cy->n), 2) - cy->radius2;
    discriminant = half_b * half_b - a * c;

    if (discriminant >= 0)
    {
        sqrtd = sqrt(discriminant);

        // 첫 번째 근 (작은 t)
        root = (-half_b - sqrtd) / a;
        if (root >= rec->tmin && root <= rec->tmax)
        {
            h = vdot(vminus(ray_at(ray, root), cy->center), cy->n);
            if (0 <= h && h <= cy->height)
            {
                rec->t = root;
                rec->p = ray_at(ray, root);
                rec->normal = vdivide(vminus(vminus(rec->p, cy->center), vmult(cy->n, h)), cy->radius);
                set_face_normal(ray, rec);
                rec->albedo = cy_obj->albedo;
                rec->tmax = rec->t;
                hit_any = TRUE;
            }
        }

        if (!hit_any)
        {
            root = (-half_b + sqrtd) / a;
            if (root >= rec->tmin && root <= rec->tmax)
            {
                h = vdot(vminus(ray_at(ray, root), cy->center), cy->n);
                if (0 <= h && h <= cy->height)
                {
                    rec->t = root;
                    rec->p = ray_at(ray, root);
                    rec->normal = vdivide(vminus(vminus(rec->p, cy->center), vmult(cy->n, h)), cy->radius);
                    set_face_normal(ray, rec);
                    rec->albedo = cy_obj->albedo;
                    rec->tmax = rec->t;
                    hit_any = TRUE;
                }
            }
        }
    }

    if (hit_cap(cy_obj, ray, rec, cy->center, vmult(cy->n, -1)))
    {
        hit_any = TRUE;
        rec->tmax = rec->t;
    }

    t_vec top_center = vplus(cy->center, vmult(cy->n, cy->height));
    if (hit_cap(cy_obj, ray, rec, top_center, cy->n))
    {
        hit_any = TRUE;
        rec->tmax = rec->t;
    }

    return (hit_any);
}