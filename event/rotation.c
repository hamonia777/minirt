/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:36:29 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/17 16:36:50 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/event.h"
#include "../header/minirt.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>

t_camera	rotation_x(t_camera camera, double theta)
{
	double	radian;
	t_vec	old_dir;

	radian = theta * M_PI / 180;
	old_dir = camera.dir;
	camera.dir.x = old_dir.x;
	camera.dir.y = (old_dir.y * cos(radian) - old_dir.z * sin(radian));
	camera.dir.z = (old_dir.y * sin(radian) + old_dir.z * cos(radian));
	camera.dir = vunit(camera.dir);
	camera = update_camera(camera);
	return (camera);
}

t_camera	rotation_y(t_camera camera, double theta)
{
	double	radian;
	t_vec	old_dir;

	radian = theta * M_PI / 180;
	old_dir = camera.dir;
	camera.dir.x = (old_dir.x * cos(radian) + old_dir.z * sin(radian));
	camera.dir.y = old_dir.y;
	camera.dir.z = -old_dir.x * sin(radian) + old_dir.z * cos(radian);
	camera.dir = vunit(camera.dir);
	camera = update_camera(camera);
	return (camera);
}
