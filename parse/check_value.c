/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:46:44 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/21 01:11:02 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/object.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	split_count(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	printf_error(char *msg)
{
	// if(!scene)
	// 	printf("%s", msg);
	// free_scene(scene);
	// free_object_list(scene->object);
	printf("%s", msg);
	exit(1);
}

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

double	parse_double(char *str)
{
	if (!is_valid_double(str))
	{
		printf("Error: Invalid number format: %s\n", str);
		exit(1);
	}
	return (ft_atod(str));
}
