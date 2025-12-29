/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:38:58 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/29 20:01:11 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/valid.h"

static int	is_invalid_split(char **split, int count)
{
	if (!split || split_count(split) != count)
	{
		free_split(split);
		return (1);
	}
	return (0);
}

int	valid_vec(char *str)
{
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (is_invalid_split(split, 3))
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_double(split[i]))
		{
			free_split(split);
			return (0);
		}
		i++;
	}
	free_split(split);
	return (1);
}

int	valid_unit_vec(char *str)
{
	char	**split;
	double	val;
	int		i;

	split = ft_split(str, ',');
	if (is_invalid_split(split, 3))
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_double(split[i]))
		{
			free_split(split);
			return (0);
		}
		val = ft_atod(split[i]);
		if (val < -1.0 || val > 1.0)
		{
			free_split(split);
			return (0);
		}
		i++;
	}
	free_split(split);
	return (1);
}

int	valid_color(char *str)
{
	char	**split;
	double	val;
	int		i;

	split = ft_split(str, ',');
	if (is_invalid_split(split, 3))
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_double(split[i]))
		{
			free_split(split);
			return (0);
		}
		val = ft_atod(split[i]);
		if (val < 0.0 || val > 255.0)
		{
			free_split(split);
			return (0);
		}
		i++;
	}
	free_split(split);
	return (1);
}
