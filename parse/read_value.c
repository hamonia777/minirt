/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:47:59 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/21 01:11:16 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/object.h"
#include "../readline/cm_readline.h"
#include <fcntl.h>
#include <unistd.h>

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

t_scene	*object_parsing(t_scene *scene, char *str)
{
	char	**split;

	while (ft_isspace(*str))
		str++;
	if (str[0] == '\n' || str[0] == '\0')
		return (scene);
	split = ft_split(str, ' ');
	if (scene->amb_count > 1 || scene->cam_count > 1 || scene->light_count > 1)
		printf_error("too many elements");
	else if (ft_strncmp(split[0], "A", 1) == 0)
		scene->ambient = parse_ambient(split);
	else if (ft_strncmp(split[0], "C", 1) == 0)
		scene->camera = parse_camera(split);
	else if (ft_strncmp(split[0], "L", 1) == 0)
		scene->light = parse_light(split);
	else if (ft_strncmp(split[0], "sp", 2) == 0)
		add_object(&(scene->object), new_object(SPHERE, parse_sphere(split)));
	else if (ft_strncmp(split[0], "pl", 2) == 0)
		add_object(&(scene->object), new_object(PLANE, parse_plane(split)));
	else if (ft_strncmp(split[0], "cy", 2) == 0)
		add_object(&(scene->object), new_object(CYLINDER,
				parse_cylinder(split)));
	free_split(split);
	return (scene);
}
int count_object(t_scene *scene,char *str)
{
	while (ft_isspace(*str))
        str++;    
    if (*str == '\0' || *str == '\n')
        return (0);
	if (ft_strncmp(str, "A", 1) == 0 && ft_isspace(str[1]))
		scene->amb_count++;
	else if (ft_strncmp(str, "C", 1) == 0 && ft_isspace(str[1]))
		scene->cam_count++;
	else if (ft_strncmp(str, "L", 1) == 0 && ft_isspace(str[1]))
		scene->light_count++;
	else if (ft_strncmp(str, "sp", 2) == 0 && ft_isspace(str[2]))
		return 0;
	else if (ft_strncmp(str, "pl", 2) == 0 && ft_isspace(str[2]))
		return 0;
	else if (ft_strncmp(str, "cy", 2) == 0 && ft_isspace(str[2]))
		return 0;
	else
		return 1;
	return 0;
}

t_scene *scene_init()
{
	t_scene *scene;
	scene = malloc(sizeof(t_scene));
	if (!scene)
		printf_error("malloc fail");
	scene->amb_count = 0;
	scene->cam_count = 0;
	scene->light_count = 0;
	scene->object = NULL;
	return scene;
}
t_scene	*read_value(char **argv)
{
	t_scene	*scene;
	char	*str;
	int		fd;

	if (ft_strlen(argv[1]) > 3 && ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3,
			".rt", 3) == 0)
		fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		printf_error("invalid value");
	str = cm_readline(fd);
	scene = scene_init();
	while (str)
	{
		if (count_object(scene, str))
			printf_error("file value error");
		scene = object_parsing(scene, str);
		free(str);
		str = cm_readline(fd);
	}
	close(fd);
	return (scene);
}
