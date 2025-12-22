/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <skang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:32:45 by skang             #+#    #+#             */
/*   Updated: 2025/12/22 16:48:45 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/trace.h"

t_color	phong_lighting(t_scene *scene)
{
	t_color	light_color;
	t_color	ambient_color;

	light_color = color3(0, 0, 0);
	light_color = vplus(light_color, point_light_get(scene, &scene->light));
	ambient_color = vmult(scene->ambient.color, scene->ambient.ambient);
	light_color = vplus(light_color, ambient_color);
	return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
}

t_color	point_light_get(t_scene *scene, t_light *light)
{
	t_light_calc		calc;
	t_vec				light_dir;
	t_light_components	comp;

	calc.scene = scene;
	calc.light = light;
	if (!check_light_visibility(calc, &light_dir))
		return (color3(0, 0, 0));
	light_dir = vunit(light_dir);
	comp = calculate_light_components(calc, light_dir);
	return (vmult(vplus(comp.diffuse, comp.specular), light->brightness
			* LUMEN));
}

t_bool	in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}
