/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:34:09 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/21 01:22:16 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/event.h"
#include "header/minirt.h"
#include "header/trace.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	render_scene(t_vars *vars)
{
	int		i;
	int		j;
	double	u;
	double	v;
	t_color	pixel_color;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			u = (double)j / (vars->width - 1);
			v = (double)(vars->height - 1 - i) / (vars->height - 1);
			vars->scene->ray = ray_primary(&vars->scene->camera, u, v);
			pixel_color = ray_color(vars->scene);
			my_mlx_pixel_put(&vars->image, j, i, create_trgb(255, pixel_color.x
					* 255.99, pixel_color.y * 255.999, pixel_color.z
					* 255.999));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	vars = vars_init();
	if (argc == 2 && ft_strlen(argv[1]) > 3)
		vars.scene = read_value(argv);
	else
	{
		printf_error("Parsing Failed or Scene is NULL", vars.scene);
	}
	render_scene(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 4, 1L << 2, mouse_down, &vars);
	mlx_hook(vars.win, 5, 1L << 3, mouse_up, &vars);
	mlx_hook(vars.win, 6, 1L << 6, mouse_move, &vars);
	mlx_hook(vars.win, 17, 1L << 0, close_window, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
