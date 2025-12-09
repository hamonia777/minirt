/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:39:26 by jinwpark          #+#    #+#             */
/*   Updated: 2025/01/22 15:15:56 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int val)
{
	int	str_len;

	str_len = (int)ft_strlen(str);
	while (str_len >= 0)
	{
		if ((unsigned char)str[str_len] == (unsigned char)val)
			return ((char *)&str[str_len]);
		str_len--;
	}
	return (NULL);
}
