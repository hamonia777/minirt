/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:53:30 by skang             #+#    #+#             */
/*   Updated: 2025/12/18 15:57:07 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/trace.h"

void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	rec->front_face = vdot(r->dir, rec->normal) < 0;
	if (!rec->front_face)
	{
		rec->normal = vmult(rec->normal, -1);
	}
}
