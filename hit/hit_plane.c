#include "../header/object.h"
#include "../header/trace.h"

double ft_fabs(double n)
{
    if (n > 0)
        return n;
    else
        return n * (-1);
}

t_bool	hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
    t_plane *pl;
    double numerator;
    double denominator;
    double result;

    pl = (t_plane *)pl_obj->elements;
    numerator = vdot(pl->normal,vminus(pl->center,ray->orig));
    denominator = vdot(pl->normal,ray->dir);
	if (ft_fabs(denominator) < EPSILON)
		return (FALSE);
    result = numerator / denominator;
    if (result < rec->tmin || rec->tmax < result) 
        return (FALSE);    
    rec->t = result;
    rec->p = ray_at(ray,result);
    rec->normal = pl->normal;
	set_face_normal(ray, rec);
    rec->albedo = pl_obj->albedo;
    return (TRUE);
}

