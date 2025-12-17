#include "../header/trace.h"

typedef struct s_light_calc
{
    t_scene *scene;
    t_light *light;
} t_light_calc;

typedef struct s_diffuse_data
{
    t_vec light_dir;
    t_color light_color;
} t_diffuse_data;

typedef struct s_specular_data
{
    t_vec light_dir;
    t_color light_color;
} t_specular_data;

typedef struct s_specular_calc
{
    double ksn;
    double ks;
} t_specular_calc;

typedef struct s_light_components
{
    t_color diffuse;
    t_color specular;
} t_light_components;

t_color phong_lighting(t_scene *scene)
{
    t_color light_color;
    t_color ambient_color;

    light_color = color3(0, 0, 0); // 광원이 하나도 없다면, 빛의 양은 (0, 0, 0)일 것이다.

    // 1. 광원 처리
    light_color = vplus(light_color, point_light_get(scene, &scene->light));

    // 2. Ambient(주변광) 처리
    ambient_color = vmult(scene->ambient.color, scene->ambient.ambient);
    light_color = vplus(light_color, ambient_color);

    // 3. 최종 색상 계산 (물체의 반사율과 곱함)
    return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
    // 모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.
}

t_vec reflect(t_vec v, t_vec n)
{
    return (vminus(v, vmult(n, vdot(v, n) * 2)));
}

// 확산광(Diffuse) 계산
t_color calculate_diffuse(t_diffuse_data data, t_scene *scene)
{
    double kd;

    kd = fmax(vdot(scene->rec.normal, data.light_dir), 0.0);
    return (vmult(data.light_color, kd));
}

// 정반사광(Specular) 계산
t_color calculate_specular(t_specular_data data, t_scene *scene)
{
    t_vec view_dir;
    t_vec reflect_dir;
    double spec;

    view_dir = vunit(vmult(scene->ray.dir, -1));
    reflect_dir = reflect(vmult(data.light_dir, -1), scene->rec.normal);
    spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), 64.0);
    return (vmult(vmult(data.light_color, 0.5), spec));
}

// 광선이 그림자에 있는지 확인 및 광원 방향 벡터 계산
t_bool check_light_visibility(t_light_calc calc, t_vec *light_dir)
{
    double light_len;
    t_ray light_ray;

    *light_dir = vminus(calc.light->orig, calc.scene->rec.p);
    light_len = vlength(*light_dir);
    light_ray = ray(vplus(calc.scene->rec.p, vmult(calc.scene->rec.normal, EPSILON)), *light_dir);
    if (in_shadow(calc.scene->object, light_ray, light_len))
        return (FALSE);
    return (TRUE);
}

// 광원에서 diffuse, specular 색상 계산
t_light_components calculate_light_components(t_light_calc calc, t_vec light_dir)
{
    t_light_components comp;
    t_diffuse_data diffuse_data;
    t_specular_data specular_data;

    diffuse_data.light_dir = light_dir;
    diffuse_data.light_color = calc.light->color;
    comp.diffuse = calculate_diffuse(diffuse_data, calc.scene);

    specular_data.light_dir = light_dir;
    specular_data.light_color = calc.light->color;
    comp.specular = calculate_specular(specular_data, calc.scene);

    return (comp);
}

// 포인트 광원 계산
t_color point_light_get(t_scene *scene, t_light *light)
{
    t_light_calc calc;
    t_vec light_dir;
    t_light_components comp;

    calc.scene = scene;
    calc.light = light;
    if (!check_light_visibility(calc, &light_dir))
        return (color3(0, 0, 0));

    light_dir = vunit(light_dir);
    comp = calculate_light_components(calc, light_dir);
    return (vmult(vplus(comp.diffuse, comp.specular), light->brightness * LUMEN));
}

t_bool in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
    t_hit_record rec;

    rec.tmin = 0;
    rec.tmax = light_len;
    if (hit(objs, &light_ray, &rec))
        return (TRUE);
    return (FALSE);
}