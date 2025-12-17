/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:27:04 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/17 16:30:33 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/event.h"
#include "../header/minirt.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>

t_camera	update_camera(t_camera camera)
{
	t_vec	vup;
	t_vec	w;
	t_vec	u;
	t_vec	v;

	vup = vec3(0, 1, 0);
	w = vunit(vmult(camera.dir, -1));
	u = vunit(vcross(vup, w));
	v = vcross(w, u);
	camera.horizontal = vmult(u, camera.viewport_w);
	camera.vertical = vmult(v, camera.viewport_h);
	camera.left_bottom = vminus(vminus(vminus(camera.orig,
					vdivide(camera.horizontal, 2)), vdivide(camera.vertical,
					2)), vmult(camera.dir, camera.focal_len));
	return (camera);
}

t_camera	move_camera(t_camera camera, double forward, double right,
		double up)
{
	t_vec	movement;
	t_vec	vup;
	t_vec	w;
	t_vec	u;
	t_vec	v;

	vup = vec3(0, 1, 0);
	w = vunit(vmult(camera.dir, -1));
	u = vunit(vcross(vup, w));
	v = vcross(w, u);
	movement = vec3(0, 0, 0);
	movement = vplus(movement, vmult(vmult(w, -1), forward));
	movement = vplus(movement, vmult(u, right));
	movement = vplus(movement, vmult(v, up));
	camera.orig = vplus(camera.orig, movement);
	camera = update_camera(camera);
	return (camera);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(vars->mlx, vars->image.img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		free_scene(vars->scene);
		exit(0);
	}
	else if (keycode == KEY_A)
		vars->scene->camera = move_camera(vars->scene->camera, 0.0, -3.0, 0.0);
	else if (keycode == KEY_D)
		vars->scene->camera = move_camera(vars->scene->camera, 0.0, 3.0, 0.0);
	else if (keycode == KEY_W)
		vars->scene->camera = move_camera(vars->scene->camera, 0.0, 0.0, 3.0);
	else if (keycode == KEY_S)
		vars->scene->camera = move_camera(vars->scene->camera, 0.0, 0.0, -3.0);
	render_scene(vars);
	return (0);
}
