/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <skang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 02:24:33 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/22 17:05:29 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/object.h"
#include <fcntl.h>

t_scene	*scene_init(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		printf_error("malloc fail", NULL);
	scene->amb_count = 0;
	scene->cam_count = 0;
	scene->light_count = 0;
	scene->object = NULL;
	return (scene);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	open_file(char **argv)
{
	int	fd;

	fd = -1;
	if (ft_strlen(argv[1]) > 3 && ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3,
			".rt", 3) == 0)
		fd = open(argv[1], O_RDONLY);
	return (fd);
}

int	check_object(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (*str == '\0' || *str == '\n')
		return (0);
	if (ft_strncmp(str, "A", 1) == 0 && ft_isspace(str[1]))
		return (0);
	else if (ft_strncmp(str, "C", 1) == 0 && ft_isspace(str[1]))
		return (0);
	else if (ft_strncmp(str, "L", 1) == 0 && ft_isspace(str[1]))
		return (0);
	else if (ft_strncmp(str, "sp", 2) == 0 && ft_isspace(str[2]))
		return (0);
	else if (ft_strncmp(str, "pl", 2) == 0 && ft_isspace(str[2]))
		return (0);
	else if (ft_strncmp(str, "cy", 2) == 0 && ft_isspace(str[2]))
		return (0);
	else
		return (1);
	return (0);
}
