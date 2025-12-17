/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:27:58 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/17 17:28:00 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/object.h"
#include "../header/vector.h"
#include <math.h>

t_sphere	*parse_sphere(char **split)
{
	t_sphere	*sphere;

	if (split_count(split) != 4)
		printf_error("Error: Missing data in SPHERE\n");
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		exit(1);
	sphere->center = parse_vec(split[1]);
	sphere->radius = parse_double(split[2]) / 2;
	sphere->radius2 = sphere->radius * sphere->radius;
	sphere->color = parse_color(split[3]);
	return (sphere);
}

t_plane	*parse_plane(char **split)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		exit(1);
	if (split_count(split) != 4)
		printf_error("Error: Missing data in PLANE\n");
	plane->center = parse_vec(split[1]);
	plane->normal = parse_unit_vec(split[2]);
	plane->color = parse_color(split[3]);
	return (plane);
}

t_cylinder	*parse_cylinder(char **split)
{
	t_cylinder	*cylinder;

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
	return (cylinder);
}
