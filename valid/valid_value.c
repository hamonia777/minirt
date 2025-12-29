/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 20:04:18 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/29 20:07:41 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/object.h"
#include "../header/valid.h"
#include "../readline/cm_readline.h"
#include <fcntl.h>
#include <unistd.h>

static int	valid_element(char **split)
{
	int	result;

	result = 0;
	if (ft_strncmp(split[0], "A", 1) == 0)
		result = valid_ambient(split);
	else if (ft_strncmp(split[0], "C", 1) == 0)
		result = valid_camera(split);
	else if (ft_strncmp(split[0], "L", 1) == 0)
		result = valid_light(split);
	else if (ft_strncmp(split[0], "sp", 2) == 0)
		result = valid_sphere(split);
	else if (ft_strncmp(split[0], "pl", 2) == 0)
		result = valid_plane(split);
	else if (ft_strncmp(split[0], "cy", 2) == 0)
		result = valid_cylinder(split);
	return (result);
}

static int	object_check_parsing(t_scene *scene, char *str)
{
	char	**split;
	int		result;

	while (ft_isspace(*str))
		str++;
	if (str[0] == '\n' || str[0] == '\0')
		return (0);
	split = ft_split(str, ' ');
	if (!split)
		return (1);
	result = check_duplicate(scene, split);
	result = !valid_element(split);
	if (!result)
	{
		if (ft_strncmp(split[0], "A", 1) == 0)
			scene->amb_count++;
		else if (ft_strncmp(split[0], "C", 1) == 0)
			scene->cam_count++;
		else if (ft_strncmp(split[0], "L", 1) == 0)
			scene->light_count++;
	}
	free_split(split);
	return (result);
}

static int	valid_process(int fd, t_scene *scene)
{
	char	*str;
	int		error;

	error = 0;
	str = cm_readline(fd);
	while (str)
	{
		if (check_object(str))
			error = 1;
		if (object_check_parsing(scene, str))
			error = 1;
		free(str);
		if (error)
			break ;
		str = cm_readline(fd);
	}
	return (error);
}

int	valid_value(char **argv)
{
	t_scene	*scene;
	int		fd;
	int		error;

	scene = scene_init();
	fd = open_file(argv);
	if (fd < 0)
	{
		free_scene(scene);
		printf("Error: invalid file\n");
		return (1);
	}
	error = valid_process(fd, scene);
	close(fd);
	if (!error && (scene->amb_count != 1 || scene->cam_count != 1
			|| scene->light_count != 1))
	{
		printf("Error: missing required elements (A, C, L)\n");
		error = 1;
	}
	cm_readline_clear();
	free_scene(scene);
	return (error);
}
