/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:38:43 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/29 20:01:55 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/object.h"
#include "../header/valid.h"

int	valid_sphere(char **split)
{
	if (split_count(split) != 4)
		return (0);
	if (!valid_vec(split[1]))
		return (0);
	if (!is_valid_double(split[2]))
		return (0);
	if (!valid_color(split[3]))
		return (0);
	return (1);
}

int	valid_plane(char **split)
{
	if (split_count(split) != 4)
		return (0);
	if (!valid_vec(split[1]))
		return (0);
	if (!valid_unit_vec(split[2]))
		return (0);
	if (!valid_color(split[3]))
		return (0);
	return (1);
}

int	valid_cylinder(char **split)
{
	if (split_count(split) != 6)
		return (0);
	if (!valid_vec(split[1]))
		return (0);
	if (!valid_unit_vec(split[2]))
		return (0);
	if (!is_valid_double(split[3]))
		return (0);
	if (!is_valid_double(split[4]))
		return (0);
	if (!valid_color(split[5]))
		return (0);
	return (1);
}
