/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_aux1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 23:54:14 by tnuno-mo          #+#    #+#             */
/*   Updated: 2025/04/07 21:00:54 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Writes a string & returns the number of characters written
int	ft_printstr(char *s)
{
	int	len;

	if (!s)
	{
		write (1, "(null)", 6);
		return (6);
	}
	len = ft_strlen(s);
	write(1, s, len);
	return (len);
}

// print pointer address in hexadecimal & return number of characters printed
// if it's NULL, print "(nil)" & return 5
int	ft_print_pointer(void *ptr)
{
	unsigned long	address;
	char			*hex_digits;
	char			buffer[16];
	int				i;
	int				count;

	if (!ptr)
	{
		ft_printstr("(nil)");
		return (5);
	}
	address = (unsigned long)ptr;
	hex_digits = "0123456789abcdef";
	i = 15;
	while (address)
	{
		buffer[i--] = hex_digits[address % 16];
		address /= 16;
	}
	count = ft_printstr("0x");
	while (++i < 16)
		count += ft_printchar(buffer[i]);
	return (count);
}

// Writes a character & returns the number of characters (bytes) printed
int	ft_printchar(int c)
{
	return (write (1, &c, 1));
}

//return the size of a string without '\0' character.
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
