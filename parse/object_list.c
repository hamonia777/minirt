/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:47:01 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/21 02:30:32 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/object.h"
#include <stdlib.h>

t_color	decision_albedo(t_object *obj, t_object_type type)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_color		albedo;

	if (type == SPHERE)
	{
		sp = (t_sphere *)obj->elements;
		albedo = vdivide(sp->color, 255.0);
	}
	else if (type == PLANE)
	{
		pl = (t_plane *)obj->elements;
		albedo = vdivide(pl->color, 255.0);
	}
	else if (type == CYLINDER)
	{
		cy = (t_cylinder *)obj->elements;
		albedo = vdivide(cy->color, 255.0);
	}
	else
		albedo = color3(1.0, 1.0, 1.0);
	return (albedo);
}

t_object	*new_object(t_object_type type, void *elements)
{
	t_object	*obj;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->next = NULL;
	obj->elements = elements;
	obj->type = type;
	obj->albedo = decision_albedo(obj, obj->type);
	return (obj);
}

t_object	*object_last(t_object *obj)
{
	if (!obj)
		return (NULL);
	while (obj->next)
		obj = obj->next;
	return (obj);
}

void	add_object(t_object **obj, t_object *new_obj)
{
	t_object	*last;

	if (!obj || !new_obj)
		return ;
	if (*obj == NULL)
	{
		*obj = new_obj;
		return ;
	}
	last = object_last(*obj);
	last->next = new_obj;
}
