/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:33:07 by jinwpark          #+#    #+#             */
/*   Updated: 2025/02/22 18:43:40 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	jw_start_idx(char const *s1, char const *set)
{
	int	flag;
	int	i;
	int	idx;

	idx = 0;
	while (s1[idx])
	{
		i = 0;
		flag = 0;
		while (set[i])
		{
			if (s1[idx] == set[i])
				flag = 1;
			i++;
		}
		if (flag != 1)
			break ;
		idx++;
	}
	return (idx);
}

static int	jw_end_idx(char const *s1, char const *set)
{
	int	flag;
	int	i;
	int	idx;

	if (ft_strlen((const char *)s1) == 0)
		return (-1);
	idx = (int)ft_strlen((const char *)s1) - 1;
	while (idx >= 0)
	{
		i = 0;
		flag = 0;
		while (set[i])
		{
			if (s1[idx] == set[i])
				flag = 1;
			i++;
		}
		if (flag != 1)
			break ;
		idx--;
	}
	return (idx);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	start = jw_start_idx(s1, set);
	end = jw_end_idx(s1, set);
	if (end == -1)
		return (ft_strdup(""));
	str = (char *)malloc ((size_t)(end - start + 2));
	if (!str)
		return (NULL);
	while (start <= end)
	{
		str[i] = s1[start];
		start++;
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
