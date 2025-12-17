#include "../header/object.h"
#include "../header/vector.h"
#include <math.h>

t_ambient parse_ambient(char **split)
{
    t_ambient ambient;
    if (split_count(split) != 3)
        printf_error("Error: Missing data in AMBIENT\n");
    ambient.ambient = parse_double(split[1]);
    ambient.color = vdivide(parse_color(split[2]), 255.0);
    return ambient;
}
t_camera parse_camera(char **split)
{
    t_camera camera;
    double aspect_ratio;
    double viewport_height;
    double theta;
    t_vec vup, w, u, v;

    if (split_count(split) != 4)
        printf_error("Error: Missing data in CAMERA\n");

    camera.orig = parse_vec(split[1]);
    camera.dir = vunit(parse_unit_vec(split[2])); // 카메라가 보는 방향
    camera.fov = parse_double(split[3]);

    theta = camera.fov * M_PI / 180.0;
    viewport_height = 2.0 * tan(theta / 2.0);
    aspect_ratio = 4.0 / 3.0;

    camera.viewport_h = viewport_height;
    camera.viewport_w = viewport_height * aspect_ratio;
    camera.focal_len = 1.0;

    // 카메라 좌표계 설정
    vup = vec3(0, 1, 0);
    w = vunit(vmult(camera.dir, -1)); // 카메라 뒤 방향 (back)
    u = vunit(vcross(vup, w));        // 카메라 오른쪽 방향 (right)
    v = vcross(w, u);                 // 카메라 위 방향 (up)

    camera.horizontal = vmult(u, camera.viewport_w);
    camera.vertical = vmult(v, camera.viewport_h);

    // **수정: 카메라가 보는 방향으로 viewport 설정**
    camera.left_bottom = vminus(vminus(vminus(camera.orig,
                                              vdivide(camera.horizontal, 2)),
                                       vdivide(camera.vertical, 2)),
                                vmult(camera.dir, camera.focal_len)); // dir 방향으로!

    return camera;
}
t_light parse_light(char **split)
{
    t_light light;
    if (split_count(split) != 4)
        printf_error("Error: Missing data in LIGHT\n");
    light.orig = parse_vec(split[1]);
    light.brightness = parse_double(split[2]);
    light.color = vdivide(parse_color(split[3]), 255.0);
    return light;
}

t_sphere *parse_sphere(char **split)
{
    t_sphere *sphere;
    if (split_count(split) != 4)
        printf_error("Error: Missing data in SPHERE\n");
    sphere = (t_sphere *)malloc(sizeof(t_sphere));
    if (!sphere)
        exit(1);
    sphere->center = parse_vec(split[1]);
    sphere->radius = parse_double(split[2]) / 2;
    sphere->radius2 = sphere->radius * sphere->radius;
    sphere->color = parse_color(split[3]);
    return sphere;
}

t_plane *parse_plane(char **split)
{
    t_plane *plane;
    plane = (t_plane *)malloc(sizeof(t_plane));
    if (!plane)
        exit(1);
    if (split_count(split) != 4)
        printf_error("Error: Missing data in PLANE\n");
    plane->center = parse_vec(split[1]);
    plane->normal = parse_unit_vec(split[2]);
    plane->color = parse_color(split[3]);
    return plane;
}

t_cylinder *parse_cylinder(char **split)
{
    t_cylinder *cylinder;
    cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
    if (!cylinder)
        exit(1);
    if (split_count(split) != 6)
        printf_error("Error: Missing data in CYLINDER\n");
    cylinder->center = parse_vec(split[1]);
    cylinder->n = parse_unit_vec(split[2]);
    cylinder->diameter = parse_double(split[3]);
    cylinder->radius = cylinder->diameter / 2;
    cylinder->radius2 = cylinder->diameter * cylinder->diameter;
    cylinder->height = parse_double(split[4]);
    cylinder->color = parse_color(split[5]);
    return cylinder;
}