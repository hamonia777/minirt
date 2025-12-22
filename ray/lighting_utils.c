/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <skang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:32:45 by skang             #+#    #+#             */
/*   Updated: 2025/12/22 16:48:29 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/trace.h"

t_color	calculate_diffuse(t_diffuse_data data, t_scene *scene)
{
	double	kd;

	kd = fmax(vdot(scene->rec.normal, data.light_dir), 0.0);
	return (vmult(data.light_color, kd));
}

t_color	calculate_specular(t_specular_data data, t_scene *scene)
{
	t_vec	view_dir;
	t_vec	reflect_dir;
	double	spec;

	view_dir = vunit(vmult(scene->ray.dir, -1));
	reflect_dir = vminus(vmult(data.light_dir, -1), vmult(scene->rec.normal,
				vdot(vmult(data.light_dir, -1), scene->rec.normal) * 2));
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), 64.0);
	return (vmult(vmult(data.light_color, 0.5), spec));
}

t_bool	check_light_visibility(t_light_calc calc, t_vec *light_dir)
{
	double	light_len;
	t_ray	light_ray;

	*light_dir = vminus(calc.light->orig, calc.scene->rec.p);
	light_len = vlength(*light_dir);
	light_ray = ray(vplus(calc.scene->rec.p, vmult(calc.scene->rec.normal,
					EPSILON)), *light_dir);
	if (in_shadow(calc.scene->object, light_ray, light_len))
		return (FALSE);
	return (TRUE);
}

t_light_components	calculate_light_components(t_light_calc calc,
		t_vec light_dir)
{
	t_light_components	comp;
	t_diffuse_data		diffuse_data;
	t_specular_data		specular_data;

	diffuse_data.light_dir = light_dir;
	diffuse_data.light_color = calc.light->color;
	comp.diffuse = calculate_diffuse(diffuse_data, calc.scene);
	specular_data.light_dir = light_dir;
	specular_data.light_color = calc.light->color;
	comp.specular = calculate_specular(specular_data, calc.scene);
	return (comp);
}
