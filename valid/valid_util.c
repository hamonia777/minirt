/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:38:31 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/29 20:08:04 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/valid.h"
#include "fcntl.h"
#include "header/object.h"
#include "readline/cm_readline.h"

int	is_valid_double(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (dot_count > 1)
				return (0);
		}
		else if (!ft_isdigit(str[i]))
		{
			if (str[i] != '\n')
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_duplicate(t_scene *scene, char **split)
{
	if (ft_strncmp(split[0], "A", 1) == 0 && scene->amb_count >= 1)
	{
		return (1);
	}
	if (ft_strncmp(split[0], "C", 1) == 0 && scene->cam_count >= 1)
	{
		return (1);
	}
	if (ft_strncmp(split[0], "L", 1) == 0 && scene->light_count >= 1)
	{
		return (1);
	}
	return (0);
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
	return (1);
}

void	cm_readline_clear(void)
{
	int		fd;
	char	*str;

	fd = open("/dev/null", O_RDONLY);
	if (fd >= 0)
	{
		str = cm_readline(fd);
		if (str)
			free(str);
		close(fd);
	}
}
