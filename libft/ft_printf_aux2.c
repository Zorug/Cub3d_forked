/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:08:16 by tnuno-mo          #+#    #+#             */
/*   Updated: 2025/04/07 20:28:39 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Writes a number & returns the number of characters written
// count is made recursive to keep track of the number of characters
int	ft_printnbr(int n)
{
	long		new_n;
	int			count;

	new_n = n;
	count = 0;
	if (new_n < 0)
	{
		write (1, "-", 1);
		count++;
		new_n = -new_n;
	}
	if (new_n > 9)
		count += ft_printnbr(new_n / 10);
	ft_printchar(new_n % 10 + '0');
	count++;
	return (count);
}

// Writes an unsigned number & returns the number of characters written
int	ft_print_unsigned(unsigned int n)
{
	char	c;
	int		count;

	count = 0;
	if (n >= 10)
		count += ft_print_unsigned(n / 10);
	c = (n % 10) + '0';
	count += ft_printchar(c);
	return (count);
}

int	ft_printnbr_hex_lo(unsigned int nbr)
{
	char	*base;
	long	new_nbr;
	int		count;

	base = "0123456789abcdef";
	new_nbr = nbr;
	count = 0;
	if (new_nbr < 16)
	{
		ft_printchar(base[new_nbr]);
		count++;
	}
	else
	{
		count += ft_printnbr_hex_lo(new_nbr / 16);
		count += ft_printnbr_hex_lo(new_nbr % 16);
	}
	return (count);
}

int	ft_printnbr_hex_up(unsigned int nbr)
{
	char	*base;
	long	new_nbr;
	int		count;

	base = "0123456789ABCDEF";
	new_nbr = nbr;
	count = 0;
	if (new_nbr < 16)
	{
		ft_printchar(base[new_nbr]);
		count++;
	}
	else
	{
		count += ft_printnbr_hex_up(new_nbr / 16);
		count += ft_printnbr_hex_up(new_nbr % 16);
	}
	return (count);
}
