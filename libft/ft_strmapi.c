/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:22:37 by jinwpark          #+#    #+#             */
/*   Updated: 2025/01/25 20:58:50 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		idx;

	if (!s || !f)
		return (NULL);
	str = (char *)malloc (ft_strlen((const char *)s) + 1);
	if (!str)
		return (NULL);
	idx = 0;
	while (s[idx])
	{
		*(str + idx) = f((unsigned int)idx, s[idx]);
		idx++;
	}
	str[idx] = '\0';
	return (str);
}
