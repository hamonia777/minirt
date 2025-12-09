/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:20:35 by jinwpark          #+#    #+#             */
/*   Updated: 2025/02/18 17:39:25 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*tmp;
	char	*addr;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	addr = tmp;
	while (s[i])
	{
		*tmp = s[i];
		tmp++;
		i++;
	}
	*tmp = '\0';
	return (addr);
}
