/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:54:11 by jinwpark          #+#    #+#             */
/*   Updated: 2025/02/18 17:40:03 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int x, int fd)
{
	long long	n;
	char		s;

	if (fd < 0)
		return ;
	n = (long long )x;
	if (x < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd((int)(n / 10), fd);
		s = (char)((n % 10) + '0');
		write(fd, &s, 1);
	}
	else if (n < 10 && n != 0)
	{
		s = (char)((n % 10) + '0');
		write(fd, &s, 1);
	}
	s = '0';
	if (n == 0)
		write(fd, &s, 1);
}
