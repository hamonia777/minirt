/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:32:37 by jinwpark          #+#    #+#             */
/*   Updated: 2025/02/21 16:40:05 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	char	*buf;
	int		i;

	i = 0;
	buf = (char *)src;
	if (dest == src)
		return (dest);
	if (src < dest)
		while (count--)
			*((char *)dest + count) = *((char *)buf + count);
	else
	{
		while (count--)
		{
			*((char *)dest + i) = *((char *)buf + i);
			i++;
		}
	}
	return (dest);
}
