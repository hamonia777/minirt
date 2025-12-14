#include "../header/trace.h"

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

t_color point_light_get(t_scene *scene, t_light *light)
{
    t_color diffuse;
    t_vec light_dir;
    double kd; // diffuse의 강도

    t_color specular;
    double light_len;
    t_ray light_ray;

    t_vec view_dir;
    t_vec reflect_dir;
    double spec;
    double ksn;
    double ks;

    double brightness;

    light_dir = vminus(light->orig, scene->rec.p);
    light_len = vlength(light_dir);
    light_ray = ray(vplus(scene->rec.p, vmult(scene->rec.normal, EPSILON)), light_dir);
    if (in_shadow(scene->object, light_ray, light_len))
        return (color3(0, 0, 0));
    // cosΘ는 Θ 값이 90도 일 때 0이고 Θ가 둔각이 되면 음수가 되므로 0.0보다 작은 경우는 0.0으로 대체한다.    
    light_dir = vunit(light_dir);
    kd = fmax(vdot(scene->rec.normal, light_dir), 0.0); // (교점에서 출발하여 광원을 향하는 벡터)와 (교점에서의 법선벡터)의 내적값.
    diffuse = vmult(light->color, kd);

    view_dir = vunit(vmult(scene->ray.dir, -1));
    reflect_dir = reflect(vmult(light_dir, -1), scene->rec.normal);
    ksn = 64;  // shininess value
    ks = 0.5;   // specular strength
    spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
    specular = vmult(vmult(light->color, ks), spec);
    brightness = light->brightness * LUMEN;
    return (vmult(vplus(diffuse, specular),brightness));
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