#ifndef TRACE_H
#define TRACE_H

#include "object.h"
#include "vector.h"

t_ray ray(t_point orig, t_vec dir);
t_point ray_at(t_ray *ray, double t);
t_ray ray_primary(t_camera *cam, double u, double v);
t_color ray_color(t_scene *scene);
t_bool hit(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool hit_sphere(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool	hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec);
void set_face_normal(t_ray *r, t_hit_record *rec);
t_color phong_lighting(t_scene *scene);

t_color point_light_get(t_scene *scene, t_light *light);

t_bool in_shadow(t_object *objs, t_ray light_ray, double light_len);

#endif