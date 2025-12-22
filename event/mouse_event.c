/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <skang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:31:11 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/22 17:12:20 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/event.h"
#include "../header/minirt.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>

int	ft_abs(int n)
{
	if (n > 0)
		return (n);
	else
		return (n * (-1));
}

int	mouse_down(int button, int x, int y, t_vars *vars)
{
	double	zoom;

	if (button == LEFT_MOUSE)
	{
		vars->x = x;
		vars->y = y;
		vars->is_drag = 1;
	}
	zoom = vars->scene->camera.orig.z;
	if (button == ZOOM_IN)
	{
		zoom = 3;
		vars->scene->camera = move_camera(vars->scene->camera, zoom, 0.0, 0.0);
		render_scene(vars);
	}
	else if (button == ZOOM_OUT)
	{
		zoom = -3;
		vars->scene->camera = move_camera(vars->scene->camera, zoom, 0.0, 0.0);
		render_scene(vars);
	}
	return (0);
}

int	mouse_up(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == LEFT_MOUSE)
	{
		vars->is_drag = 0;
	}
	return (0);
}

int	mouse_move(int x, int y, t_vars *vars)
{
	vars->camera_changed = 0;
	if (vars->is_drag != 1)
		return (0);
	if (ft_abs(x - vars->x) >= 7)
	{
		if (x - vars->x > 0)
			vars->scene->camera = rotation_y(vars->scene->camera, -1.0);
		else
			vars->scene->camera = rotation_y(vars->scene->camera, 1.0);
		vars->camera_changed = 1;
		vars->x = x;
	}
	if (ft_abs(y - vars->y) >= 7)
	{
		if (y - vars->y > 0)
			vars->scene->camera = rotation_x(vars->scene->camera, 1.0);
		else
			vars->scene->camera = rotation_x(vars->scene->camera, -1.0);
		vars->camera_changed = 1;
		vars->y = y;
	}
	if (vars->camera_changed)
		render_scene(vars);
	return (0);
}
