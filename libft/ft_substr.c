/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:15:46 by jinwpark          #+#    #+#             */
/*   Updated: 2025/02/22 18:01:46 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*str;

	if (!s)
		return (NULL);
	s_len = ft_strlen((const char *)s);
	if (s_len <= (size_t)start)
		return (ft_strdup(""));
	if (len > s_len - (size_t)start)
		len = s_len - (size_t)start;
	str = (char *)malloc (len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*(str + i) = s[(size_t)start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
