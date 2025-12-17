#include "../../header/vector.h"
#include "../../header/trace.h"
#include "../../header/object.h"
#include <math.h>

typedef struct s_coeff
{
    double a;
    double half_b;
    double c;
} t_coeff;

typedef struct s_root_check
{
    t_object *cy_obj;
    t_ray *ray;
    t_hit_record *rec;
    double root;
} t_root_check;


// 실린더 몸통의 한쪽 근을 체크
t_bool check_cylinder_root(t_root_check data)
{
    t_cylinder *cy;
    double h;
    t_point p;

    cy = data.cy_obj->elements;
    if (data.root < data.rec->tmin || data.root > data.rec->tmax)
        return (FALSE);

    p = ray_at(data.ray, data.root);
    h = vdot(vminus(p, cy->center), cy->n);

    if (h < 0 || h > cy->height)
        return (FALSE);

    data.rec->t = data.root;
    data.rec->p = p;
        data.rec->normal = vdivide(vminus(vminus(p, cy->center), vmult(cy->n, h)), cy->radius);
    set_face_normal(data.ray, data.rec);
    data.rec->albedo = data.cy_obj->albedo;
    data.rec->tmax = data.rec->t;
    return (TRUE);
}

// 이차방정식의 계수 계산 (a, b, c)
void calculate_quadratic_coeffs(t_cylinder *cy, t_ray *ray, t_vec oc, t_coeff *coeff)
{
    double dot_dir_n;
    double dot_oc_n;

    dot_dir_n = vdot(ray->dir, cy->n);
    dot_oc_n = vdot(oc, cy->n);
    coeff->a = vlength2(ray->dir) - pow(dot_dir_n, 2);
    coeff->half_b = vdot(ray->dir, oc) - (dot_dir_n * dot_oc_n);
    coeff->c = vlength2(oc) - pow(dot_oc_n, 2) - cy->radius2;
}

// 판별식으로부터 두 근 계산
t_bool try_both_roots(t_object *cy_obj, t_ray *ray, t_hit_record *rec, t_coeff coeff, double sqrtd)
{
    t_root_check data;
    t_bool hit_any;

    hit_any = FALSE;
    data.cy_obj = cy_obj;
    data.ray = ray;
    data.rec = rec;
    data.root = (-coeff.half_b - sqrtd) / coeff.a;
    if (check_cylinder_root(data))
        hit_any = TRUE;

    if (!hit_any)
    {
        data.root = (-coeff.half_b + sqrtd) / coeff.a;
        if (check_cylinder_root(data))
            hit_any = TRUE;
    }

    return (hit_any);
}

// 실린더 몸통 충돌 체크
t_bool hit_cylinder_body(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
    t_cylinder *cy;
    t_vec oc;
    t_coeff coeff;
    double discriminant;
    double sqrtd;

    cy = cy_obj->elements;
    oc = vminus(ray->orig, cy->center);
    calculate_quadratic_coeffs(cy, ray, oc, &coeff);
    discriminant = coeff.half_b * coeff.half_b - coeff.a * coeff.c;

    if (discriminant >= 0)
    {
        sqrtd = sqrt(discriminant);
        return (try_both_roots(cy_obj, ray, rec, coeff, sqrtd));
    }
    return (FALSE);
}
