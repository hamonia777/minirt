/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:47:13 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/29 17:09:40 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/object.h"
#include "../header/vector.h"
#include <math.h>

t_ambient	parse_ambient(char **split, t_scene *scene)
{
	t_ambient	ambient;

	ambient.ambient = parse_double(split[1]);
	ambient.color = vdivide(parse_color(split[2], scene), 255.0);
	scene->amb_count++;
	return (ambient);
}

static void	init_camera_vectors(t_camera *camera, t_vec *vup)
{
	t_vec	w;
	t_vec	u;
	t_vec	v;

	if (camera->dir.y == 1.0 || camera->dir.y == -1.0)
		*vup = vec3(0, 0, 1);
	else
		*vup = vec3(0, 1, 0);
	w = vunit(vmult(camera->dir, -1));
	u = vunit(vcross(*vup, w));
	v = vcross(w, u);
	camera->horizontal = vmult(u, camera->viewport_w);
	camera->vertical = vmult(v, camera->viewport_h);
}

static void	calc_camera_viewport(t_camera *camera)
{
	camera->left_bottom = vminus(camera->orig, vdivide(camera->horizontal, 2));
	camera->left_bottom = vminus(camera->left_bottom, vdivide(camera->vertical,
				2));
	camera->left_bottom = vminus(camera->left_bottom, vmult(camera->dir,
				camera->focal_len));
}

t_camera	parse_camera(char **split, t_scene *scene)
{
	t_camera	camera;
	t_vec		vup;

	camera.orig = parse_vec(split[1], scene);
	camera.dir = vunit(parse_unit_vec(split[2], scene));
	camera.fov = parse_double(split[3]);
	camera.viewport_h = 2.0 * tan((camera.fov * M_PI / 180.0) / 2.0);
	camera.viewport_w = camera.viewport_h * (ASPECT_W / ASPECT_H);
	camera.focal_len = 1.0;
	init_camera_vectors(&camera, &vup);
	calc_camera_viewport(&camera);
	scene->cam_count++;
	return (camera);
}

t_light	parse_light(char **split, t_scene *scene)
{
	t_light	light;

	light.orig = parse_vec(split[1], scene);
	light.brightness = parse_double(split[2]);
	light.color = vdivide(parse_color(split[3], scene), 255.0);
	scene->light_count++;
	return (light);
}
