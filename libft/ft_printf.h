/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 00:20:35 by tnuno-mo          #+#    #+#             */
/*   Updated: 2025/04/07 20:29:35 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

//libraries to include
# include <unistd.h>
# include <stdarg.h>

//functions to include
int		ft_printf(const char *format, ...);
size_t	ft_strlen(const char *s);
int		ft_printchar(int c);
int		ft_printstr(char *s);
int		ft_printnbr(int n);
int		ft_print_unsigned(unsigned int n);
int		ft_print_pointer(void *ptr);
int		ft_printnbr_hex_lo(unsigned int nbr);
int		ft_printnbr_hex_up(unsigned int nbr);

#endif