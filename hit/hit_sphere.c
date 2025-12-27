/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:53:09 by skang             #+#    #+#             */
/*   Updated: 2025/12/18 15:53:23 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/object.h"
#include "../header/trace.h"
#include "../header/vector.h"
#include <math.h>

typedef struct s_sphere_coeff
{
	double			a;
	double			half_b;
	double			c;
}					t_sphere_coeff;

typedef struct s_sphere_data
{
	t_object		*sp_obj;
	t_ray			*ray;
	t_hit_record	*rec;
}					t_sphere_data;

static void	calculate_sphere_coeffs(t_sphere *sp, t_ray *ray,
				t_sphere_coeff *coeff)
{
	t_vec	oc;

	oc = vminus(ray->orig, sp->center);
	coeff->a = vlength2(ray->dir);
	coeff->half_b = vdot(oc, ray->dir);
	coeff->c = vlength2(oc) - sp->radius2;
}

static t_bool	check_sphere_root(t_sphere_data data, double root)
{
	t_sphere	*sp;
	t_point		p;

	sp = data.sp_obj->elements;
	if (root < data.rec->tmin || data.rec->tmax < root)
		return (FALSE);
	p = ray_at(data.ray, root);
	data.rec->t = root;
	data.rec->p = p;
	data.rec->normal = vdivide(vminus(p, sp->center), sp->radius);
	set_face_normal(data.ray, data.rec);
	data.rec->albedo = data.sp_obj->albedo;
	return (TRUE);
}

static t_bool	try_sphere_roots(t_sphere_data data, t_sphere_coeff coeff,
				double sqrtd)
{
	double	root1;
	double	root2;

	root1 = (-coeff.half_b - sqrtd) / coeff.a;
	if (check_sphere_root(data, root1))
		return (TRUE);
	root2 = (-coeff.half_b + sqrtd) / coeff.a;
	if (check_sphere_root(data, root2))
		return (TRUE);
	return (FALSE);
}

t_bool	hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere		*sp;
	t_sphere_coeff	coeff;
	t_sphere_data	data;
	double			discriminant;
	double			sqrtd;

	sp = sp_obj->elements;
	data.sp_obj = sp_obj;
	data.ray = ray;
	data.rec = rec;
	calculate_sphere_coeffs(sp, ray, &coeff);
	discriminant = coeff.half_b * coeff.half_b - coeff.a * coeff.c;
	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	return (try_sphere_roots(data, coeff, sqrtd));
}
