/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_printf.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/17 00:57:14 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2024/11/24 18:49:29 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "ft_printf.h"

static int	select_format(char format, va_list args)
{
	if (format == 'c')
		return (ft_printchar(va_arg(args, int)));
	else if (format == '%')
		return (ft_printchar('%'));
	else if (format == 's')
		return (ft_printstr(va_arg(args, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_printnbr(va_arg(args, int)));
	else if (format == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else if (format == 'x')
		return (ft_printnbr_hex_lo(va_arg(args, unsigned int)));
	else if (format == 'X')
		return (ft_printnbr_hex_up(va_arg(args, unsigned int)));
	else if (format == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	else
	{
		ft_printchar('%');
		return (ft_printchar(format));
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += select_format(*format, args);
		}
		else
			count += ft_printchar(*format);
		format++;
	}
	va_end(args);
	return (count);
}
/*
#include <stdio.h>

int main (void)
{
	printf ("%d\n", (ft_printf ("mine %%tttt\n", "teste")));
	printf ("%d\n", (printf ("orig %%tttt\n", "teste")));
}
*/