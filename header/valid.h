/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 20:09:30 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/29 20:09:31 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALID_H
# define VALID_H

# include "../header/object.h"

int		valid_value(char **argv);
int		valid_ambient(char **split);
int		valid_camera(char **split);
int		valid_light(char **split);
int		valid_sphere(char **split);
int		valid_plane(char **split);
int		valid_cylinder(char **split);
int		is_valid_double(char *str);
int		check_duplicate(t_scene *scene, char **split);
int		check_object(char *str);
int		valid_vec(char *str);
int		valid_unit_vec(char *str);
int		valid_color(char *str);
void	cm_readline_clear(void);

#endif
