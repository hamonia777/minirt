/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:47:45 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/17 17:05:49 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/object.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_vec	parse_vec(char *str)
{
	char	**split;
	t_vec	vec;

	split = ft_split(str, ',');
	if (split_count(split) != 3)
	{
		printf("Error: Invalid vector format\n");
		exit(1);
	}
	vec.x = parse_double(split[0]);
	vec.y = parse_double(split[1]);
	vec.z = parse_double(split[2]);
	free_split(split);
	return (vec);
}

t_color	parse_color(char *split)
{
	char	**color;
	t_point	color_xyz;

	color = ft_split(split, ',');
	if (split_count(color) != 3)
	{
		printf("Error: Invalid color format\n");
		exit(1);
	}
	color_xyz.x = parse_double(color[0]);
	color_xyz.y = parse_double(color[1]);
	color_xyz.z = parse_double(color[2]);
	free_split(color);
	return (color_xyz);
}

t_vec	parse_unit_vec(char *str)
{
	char	**split;
	t_vec	vec;

	split = ft_split(str, ',');
	if (split_count(split) != 3)
	{
		printf("Error: Invalid unit vector format\n");
		exit(1);
	}
	vec.x = parse_double(split[0]);
	vec.y = parse_double(split[1]);
	vec.z = parse_double(split[2]);
	free_split(split);
	if (vec.x < -1.0 || vec.x > 1.0 || vec.y < -1.0 || vec.y > 1.0
		|| vec.z < -1.0 || vec.z > 1.0)
	{
		printf("Error: Normalized vector value out of range (-1.0 to 1.0)\n");
		exit(1);
	}
	return (vec);
}

double	ft_atod(char *str)
{
	double	result;
	double	divisor;
	double	sign;
	int		i;

	result = 0.0;
	divisor = 1.0;
	sign = 1.0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1.0;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10.0 + (str[i] - '0');
			divisor *= 10.0;
			i++;
		}
	}
	return (sign * result / divisor);
}
