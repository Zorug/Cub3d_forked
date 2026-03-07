/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:08:16 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 14:41:13 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Writes a number to a file descriptor
void	ft_putnbr_fd(int n, int fd)
{
	long	new_n;

	new_n = n;
	if (new_n < 0)
	{
		write (fd, "-", 1);
		new_n = -new_n;
	}
	if (new_n > 9)
		ft_putnbr_fd(new_n / 10, fd);
	ft_putchar_fd(new_n % 10 + '0', fd);
}
