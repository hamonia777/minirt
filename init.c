/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <skang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:28:34 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/24 12:38:55 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minirt.h"
#include "minilibx-linux/mlx.h"

t_vars	vars_init(void)
{
	t_vars	vars;

	vars.scene = NULL;
	vars.width = 400;
	vars.aspect_ratio = ASPECT_W / ASPECT_H;
	vars.height = 300;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.width, vars.height, "miniRT");
	vars.image.img = mlx_new_image(vars.mlx, vars.width, vars.height);
	vars.image.addr = mlx_get_data_addr(vars.image.img,
			&vars.image.bits_per_pixel, &vars.image.line_length,
			&vars.image.endian);
	vars.x = 0;
	vars.y = 0;
	vars.is_drag = 0;
	vars.camera_changed = 0;
	return (vars);
}
