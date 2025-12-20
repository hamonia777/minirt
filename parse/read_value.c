/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:47:59 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/21 02:22:49 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/object.h"
#include "../readline/cm_readline.h"
#include <unistd.h>

static void	check_duplicate(t_scene *scene, char **split)
{
	if (ft_strncmp(split[0], "A", 1) == 0 && scene->amb_count >= 1)
	{
		free_split(split);
		printf_error("too many elements", scene);
	}
	if (ft_strncmp(split[0], "C", 1) == 0 && scene->cam_count >= 1)
	{
		free_split(split);
		printf_error("too many elements", scene);
	}
	if (ft_strncmp(split[0], "L", 1) == 0 && scene->light_count >= 1)
	{
		free_split(split);
		printf_error("too many elements", scene);
	}
}

static void	parse_element(t_scene *scene, char **split)
{
	if (ft_strncmp(split[0], "A", 1) == 0)
		scene->ambient = parse_ambient(split, scene);
	else if (ft_strncmp(split[0], "C", 1) == 0)
		scene->camera = parse_camera(split, scene);
	else if (ft_strncmp(split[0], "L", 1) == 0)
		scene->light = parse_light(split, scene);
	else if (ft_strncmp(split[0], "sp", 2) == 0)
		add_object(&(scene->object), new_object(SPHERE,
				parse_sphere(split, scene)));
	else if (ft_strncmp(split[0], "pl", 2) == 0)
		add_object(&(scene->object), new_object(PLANE,
				parse_plane(split, scene)));
	else if (ft_strncmp(split[0], "cy", 2) == 0)
		add_object(&(scene->object), new_object(CYLINDER,
				parse_cylinder(split, scene)));
}

t_scene	*object_parsing(t_scene *scene, char *str)
{
	char	**split;

	while (ft_isspace(*str))
		str++;
	if (str[0] == '\n' || str[0] == '\0')
		return (scene);
	split = ft_split(str, ' ');
	if (!split)
		printf_error("malloc fail", scene);
	check_duplicate(scene, split);
	parse_element(scene, split);
	free_split(split);
	return (scene);
}

static void	process_line(t_scene **scene, char *str)
{
	if (check_object(*scene, str))
	{
		free(str);
		printf_error("invalid value", *scene);
	}
	*scene = object_parsing(*scene, str);
}

t_scene	*read_value(char **argv)
{
	t_scene	*scene;
	char	*str;
	int		fd;

	scene = scene_init();
	fd = open_file(argv);
	if (fd < 0)
		printf_error("invalid file", scene);
	str = cm_readline(fd);
	while (str)
	{
		process_line(&scene, str);
		free(str);
		str = cm_readline(fd);
	}
	close(fd);
	return (scene);
}
