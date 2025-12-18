/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:52:50 by skang             #+#    #+#             */
/*   Updated: 2025/12/18 15:52:51 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/object.h"
#include "../header/trace.h"
#include "../header/vector.h"

t_bool	hit_cylinder_body(t_object *cy_obj, t_ray *ray, t_hit_record *rec);
t_bool	hit_cylinder_caps(t_object *cy_obj, t_ray *ray, t_hit_record *rec);

t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_bool	body_hit;
	t_bool	caps_hit;

	body_hit = hit_cylinder_body(cy_obj, ray, rec);
	caps_hit = hit_cylinder_caps(cy_obj, ray, rec);
	return (body_hit || caps_hit);
}
