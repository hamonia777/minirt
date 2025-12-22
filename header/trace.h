/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <skang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:16:58 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/22 17:04:50 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include "object.h"
# include "vector.h"

t_hit_record		record_init(void);
t_ray				ray(t_point orig, t_vec dir);
t_point				ray_at(t_ray *ray, double t);
t_ray				ray_primary(t_camera *cam, double u, double v);
t_color				ray_color(t_scene *scene);
t_bool				hit(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool				hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool				hit_sphere(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool				hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec);
t_bool				hit_cylinder(t_object *obj, t_ray *ray, t_hit_record *rec);
void				set_face_normal(t_ray *r, t_hit_record *rec);
t_color				phong_lighting(t_scene *scene);

t_color				point_light_get(t_scene *scene, t_light *light);

t_bool				in_shadow(t_object *objs, t_ray light_ray,
						double light_len);

t_color				calculate_diffuse(t_diffuse_data data, t_scene *scene);
t_color				calculate_specular(t_specular_data data, t_scene *scene);
t_bool				check_light_visibility(t_light_calc calc, t_vec *light_dir);
t_light_components	calculate_light_components(t_light_calc calc,
						t_vec light_dir);

#endif
