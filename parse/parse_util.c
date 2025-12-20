/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:47:45 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/21 02:28:50 by jinwpark         ###   ########.fr       */
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

t_vec	parse_vec(char *str, t_scene *scene)
{
	char	**split;
	t_vec	vec;

	split = ft_split(str, ',');
	if (!split)
		printf_error("malloc fail", scene);
	if (split_count(split) != 3)
	{
		free_split(split);
		printf_error("Error: Invalid vector format", scene);
	}
	vec.x = parse_double(split[0], scene);
	vec.y = parse_double(split[1], scene);
	vec.z = parse_double(split[2], scene);
	free_split(split);
	return (vec);
}

t_color	parse_color(char *split, t_scene *scene)
{
	char	**color;
	t_point	color_xyz;

	color = ft_split(split, ',');
	if (!color)
		printf_error("malloc fail", scene);
	if (split_count(color) != 3)
	{
		free_split(color);
		printf_error("Error: Invalid color format", scene);
	}
	color_xyz.x = parse_double(color[0], scene);
	color_xyz.y = parse_double(color[1], scene);
	color_xyz.z = parse_double(color[2], scene);
	free_split(color);
	return (color_xyz);
}

t_vec	parse_unit_vec(char *str, t_scene *scene)
{
	char	**split;
	t_vec	vec;

	split = ft_split(str, ',');
	if (!split)
		printf_error("malloc fail", scene);
	if (split_count(split) != 3)
	{
		free_split(split);
		printf_error("Error: Invalid unit vector format", scene);
	}
	vec.x = parse_double(split[0], scene);
	vec.y = parse_double(split[1], scene);
	vec.z = parse_double(split[2], scene);
	free_split(split);
	if (vec.x < -1.0 || vec.x > 1.0 || vec.y < -1.0
		|| vec.y > 1.0 || vec.z < -1.0 || vec.z > 1.0)
		printf_error("Error: value out of range (-1.0 to 1.0)", scene);
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
