/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:47:13 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/21 01:10:39 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/object.h"
#include "../header/vector.h"
#include <math.h>

t_ambient	parse_ambient(char **split)
{
	t_ambient	ambient;

	if (split_count(split) != 3)
		printf_error("Missing data in AMBIENT\n");
	ambient.ambient = parse_double(split[1]);
	ambient.color = vdivide(parse_color(split[2]), 255.0);
	return (ambient);
}

t_camera	parse_camera(char **split)
{
	t_camera	camera;
	t_vec		vup;
	t_vec		w;
	t_vec		u;
	t_vec		v;

	if (split_count(split) != 4)
		printf_error("Missing data in CAMERA\n");
	camera.orig = parse_vec(split[1]);
	camera.dir = vunit(parse_unit_vec(split[2]));
	camera.fov = parse_double(split[3]);
	camera.viewport_h = 2.0 * tan((camera.fov * M_PI / 180.0) / 2.0);
	camera.viewport_w = camera.viewport_h * (4.0 / 3.0);
	camera.focal_len = 1.0;
	if(camera.dir.y == 1.0 || camera.dir.y == -1.0)
		vup = vec3(0, 0, 1);
	else
		vup = vec3(0, 1, 0);
	w = vunit(vmult(camera.dir, -1));
	u = vunit(vcross(vup, w));
	v = vcross(w, u);
	camera.horizontal = vmult(u, camera.viewport_w);
	camera.vertical = vmult(v, camera.viewport_h);
	camera.left_bottom = vminus(vminus(vminus(camera.orig,
					vdivide(camera.horizontal, 2)), vdivide(camera.vertical,
					2)), vmult(camera.dir, camera.focal_len));
	return (camera);
}

t_light	parse_light(char **split)
{
	t_light	light;

	if (split_count(split) != 4)
		printf_error("Missing data in LIGHT\n");
	light.orig = parse_vec(split[1]);
	light.brightness = parse_double(split[2]);
	light.color = vdivide(parse_color(split[3]), 255.0);
	return (light);
}
