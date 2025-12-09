/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:32:35 by jinwpark          #+#    #+#             */
/*   Updated: 2025/02/18 23:38:46 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t n)
{
	size_t				i;
	unsigned char		*dest1;
	const unsigned char	*source1;

	if (!dest && !source && n > 0)
		return (NULL);
	dest1 = dest;
	source1 = source;
	i = 0;
	while (i < n)
	{
		dest1[i] = source1[i];
		i++;
	}
	return (dest);
}
