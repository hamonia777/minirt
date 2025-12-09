/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:03:49 by jinwpark          #+#    #+#             */
/*   Updated: 2025/02/22 18:42:07 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*jw_frees(char **str, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(str[j]);
		j++;
	}
	free(str);
	return (NULL);
}

static size_t	jw_i_size(char const *s, char c)
{
	int		flag;
	int		i;
	size_t	count;

	count = 0;
	flag = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && !flag)
		{
			flag = 1;
			count++;
		}
		else if (s[i] == c)
		{
			flag = 0;
		}
		i++;
	}
	return (count);
}

static size_t	jw_find_idx(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	size = jw_i_size(s, c);
	i = 0;
	str = (char **)malloc(sizeof(char *) * (size + 1));
	if (!str)
		return (NULL);
	while (i < size)
	{
		while (*s == c)
			s++;
		str[i] = (char *)malloc(jw_find_idx(s, c) + 1);
		if (!str[i])
			return (jw_frees(str, i));
		ft_strlcpy(str[i], s, jw_find_idx(s, c) + 1);
		s += jw_find_idx(s, c);
		i++;
	}
	str[size] = NULL;
	return (str);
}
