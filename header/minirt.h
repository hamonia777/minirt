/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:16:42 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/18 14:16:43 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "object.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars
{
	t_scene	*scene;
	t_data	image;
	void	*mlx;
	void	*win;
	int		height;
	int		width;
	double	aspect_ratio;
	int		x;
	int		y;
	int		is_drag;
	int		camera_changed;
}			t_vars;

void		print_vec(char *name, t_vec vec);
void		print_scene(t_scene *scene);
int			key_hook(int keycode, t_vars *vars);
t_vars		vars_init(void);
void		render_scene(t_vars *vars);
void		print_vec(char *name, t_vec vec);
#endif
