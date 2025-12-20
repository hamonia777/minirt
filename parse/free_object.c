/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 02:30:37 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/21 02:30:38 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/object.h"

void	free_element(t_object *obj)
{
	if (!obj || !obj->elements)
		return ;
	free(obj->elements);
	obj->elements = NULL;
}

void	free_object_list(t_object *obj)
{
	t_object	*next;

	while (obj)
	{
		next = obj->next;
		free_element(obj);
		free(obj);
		obj = next;
	}
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_object_list(scene->object);
	free(scene);
}
