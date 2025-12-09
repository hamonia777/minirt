/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:28:45 by jinwpark          #+#    #+#             */
/*   Updated: 2025/01/21 19:58:37 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const	char	*str)
{
	long		total;
	long		minus;

	minus = 1;
	total = 0;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		total *= 10;
		total += (*str - '0');
		str++;
	}
	return ((int)(total * minus));
}
