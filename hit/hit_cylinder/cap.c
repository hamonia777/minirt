/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:53:42 by skang             #+#    #+#             */
/*   Updated: 2025/12/18 15:53:43 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/object.h"
#include "../../header/trace.h"
#include "../../header/vector.h"
#include <math.h>

typedef struct s_cap_data
{
	t_vec	center;
	t_vec	normal;
}			t_cap_data;

// 교점이 뚜껑 원판 안에 있는지 확인
t_bool	is_point_on_cap(t_cylinder *cy, t_point p, t_vec center)
{
	t_vec	cp;

	cp = vminus(p, center);
	return (vlength2(cp) <= cy->radius2);
}

// 광선과 평면의 교점 거리 계산
double	calculate_cap_intersection(t_ray *ray, t_vec center, t_vec normal)
{
	double	denom;
	double	t;

	denom = vdot(ray->dir, normal);
	if (fabs(denom) < 1e-6)
		return (-1.0);
	t = vdot(vminus(center, ray->orig), normal) / denom;
	return (t);
}

t_bool	hit_cap(t_object *cy_obj, t_ray *ray, t_hit_record *rec, t_cap_data cap)
{
	t_cylinder	*cy;
	double		t;
	t_point		p;

	cy = cy_obj->elements;
	t = calculate_cap_intersection(ray, cap.center, cap.normal);
	if (t < 0 || t < rec->tmin || t > rec->tmax)
		return (FALSE);
	p = ray_at(ray, t);
	if (!is_point_on_cap(cy, p, cap.center))
		return (FALSE);
	rec->t = t;
	rec->p = p;
	rec->normal = cap.normal;
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (TRUE);
}

// 실린더 뚜껑 충돌 체크
t_bool	hit_cylinder_caps(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	t_cap_data	cap_bottom;
	t_cap_data	cap_top;
	t_bool		hit_any;

	cy = cy_obj->elements;
	hit_any = FALSE;
	cap_bottom.center = cy->center;
	cap_bottom.normal = vmult(cy->n, -1);
	if (hit_cap(cy_obj, ray, rec, cap_bottom))
	{
		hit_any = TRUE;
		rec->tmax = rec->t;
	}
	cap_top.center = vplus(cy->center, vmult(cy->n, cy->height));
	cap_top.normal = cy->n;
	if (hit_cap(cy_obj, ray, rec, cap_top))
	{
		hit_any = TRUE;
		rec->tmax = rec->t;
	}
	return (hit_any);
}
