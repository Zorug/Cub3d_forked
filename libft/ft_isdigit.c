/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:21:54 by tnuno-mo          #+#    #+#             */
/*   Updated: 2024/10/30 00:01:45 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("ft_isdigit('0'): %d (espected: 1)\n", ft_isdigit('0'));
	printf("ft_isdigit('9'): %d (expected: 1)\n", ft_isdigit('9'));
	printf("ft_isdigit('a'): %d (expected: 0)\n", ft_isdigit('a'));
	printf("ft_isdigit(' '): %d (expected: 0)\n", ft_isdigit(' '));
	printf("ft_isdigit('!'): %d (expected: 0)\n", ft_isdigit('!'));
	return (0);
}
*/