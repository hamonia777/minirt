/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:53:40 by jinwpark          #+#    #+#             */
/*   Updated: 2025/02/21 21:04:29 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	tmp;
	int				i;

	i = 0;
	tmp = (unsigned char)c;
	while ((unsigned char)str[i] != tmp)
	{
		if ((unsigned char)str[i] == '\0')
			return (0);
		i++;
	}
	return ((char *)&str[i]);
}
