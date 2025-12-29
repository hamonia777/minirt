/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 02:24:33 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/29 17:00:30 by jinwpark         ###   ########.fr       */
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
