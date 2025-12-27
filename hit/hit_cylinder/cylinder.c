/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:53:46 by skang             #+#    #+#             */
/*   Updated: 2025/12/18 16:03:34 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/object.h"
#include "../../header/trace.h"
#include "../../header/vector.h"
#include <math.h>

static t_bool	check_cylinder_root(t_root_check data)
{
	t_cylinder	*cy;
	double		h;
	t_point		p;
	t_vec		axis_point;

	cy = data.cy_obj->elements;
	if (data.root < data.rec->tmin || data.root > data.rec->tmax)
		return (FALSE);
	p = ray_at(data.ray, data.root);
	h = vdot(vminus(p, cy->center), cy->n);
	if (h < 0 || h > cy->height)
		return (FALSE);
	data.rec->t = data.root;
	data.rec->p = p;
	axis_point = vplus(cy->center, vmult(cy->n, h));
	data.rec->normal = vunit(vminus(p, axis_point));
	set_face_normal(data.ray, data.rec);
	data.rec->albedo = data.cy_obj->albedo;
	data.rec->tmax = data.rec->t;
	return (TRUE);
}

static void	calculate_quadratic_coeffs(t_cylinder *cy, t_ray *ray, t_vec oc,
				t_coeff *coeff)
{
	double	dot_dir_n;
	double	dot_oc_n;

	dot_dir_n = vdot(ray->dir, cy->n);
	dot_oc_n = vdot(oc, cy->n);
	coeff->a = vlength2(ray->dir) - pow(dot_dir_n, 2);
	coeff->half_b = vdot(ray->dir, oc) - (dot_dir_n * dot_oc_n);
	coeff->c = vlength2(oc) - pow(dot_oc_n, 2) - cy->radius2;
}

static t_bool	try_both_roots(t_root_calc calc, double sqrtd)
{
	t_root_check	data;
	t_bool			hit_any;

	hit_any = FALSE;
	data.cy_obj = calc.cy_obj;
	data.ray = calc.ray;
	data.rec = calc.rec;
	data.root = (-calc.coeff.half_b - sqrtd) / calc.coeff.a;
	if (check_cylinder_root(data))
		hit_any = TRUE;
	if (!hit_any)
	{
		data.root = (-calc.coeff.half_b + sqrtd) / calc.coeff.a;
		if (check_cylinder_root(data))
			hit_any = TRUE;
	}
	return (hit_any);
}

t_bool	hit_cylinder_body(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	t_coeff		coeff;
	t_root_calc	calc;
	double		discriminant;
	double		sqrtd;

	cy = cy_obj->elements;
	calculate_quadratic_coeffs(cy, ray, vminus(ray->orig, cy->center), &coeff);
	discriminant = coeff.half_b * coeff.half_b - coeff.a * coeff.c;
	if (discriminant >= 0)
	{
		sqrtd = sqrt(discriminant);
		calc.cy_obj = cy_obj;
		calc.ray = ray;
		calc.rec = rec;
		calc.coeff = coeff;
		return (try_both_roots(calc, sqrtd));
	}
	return (FALSE);
}
