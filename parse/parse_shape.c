/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:27:58 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/30 14:55:08 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/object.h"
#include "../header/vector.h"
#include <math.h>

t_sphere	*parse_sphere(char **split, t_scene *scene)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
	{
		free_split(split);
		printf_error("malloc fail", scene);
	}
	sphere->center = parse_vec(split[1], scene);
	sphere->radius = parse_double(split[2]) / 2;
	sphere->radius2 = sphere->radius * sphere->radius;
	sphere->color = parse_color(split[3], scene);
	return (sphere);
}

t_plane	*parse_plane(char **split, t_scene *scene)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
	{
		free_split(split);
		printf_error("malloc fail", scene);
	}
	plane->center = parse_vec(split[1], scene);
	plane->normal = parse_unit_vec(split[2], scene);
	plane->color = parse_color(split[3], scene);
	return (plane);
}

t_cylinder	*parse_cylinder(char **split, t_scene *scene)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
	{
		free_split(split);
		printf_error("malloc fail", scene);
	}
	cylinder->center = parse_vec(split[1], scene);
	cylinder->n = vunit(parse_unit_vec(split[2], scene));
	cylinder->diameter = parse_double(split[3]);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->radius2 = cylinder->radius * cylinder->radius;
	cylinder->height = parse_double(split[4]);
	cylinder->color = parse_color(split[5], scene);
	return (cylinder);
}
