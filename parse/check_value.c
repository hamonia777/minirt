/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:46:44 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/29 19:09:09 by jinwpark         ###   ########.fr       */
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

void	printf_error(char *msg, t_scene *scene)
{
	printf("Error %s\n", msg);
	if (scene)
		free_scene(scene);
	exit(1);
}

double	parse_double(char *str)
{
	return (ft_atod(str));
}
