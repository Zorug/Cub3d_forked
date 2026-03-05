/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:24:51 by tnuno-mo          #+#    #+#             */
/*   Updated: 2024/10/30 00:02:15 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char c1 = 'A';
	char c2 = 200;
	char c3 = '\n';
	
	printf("'%c' is ASCII: %d\n", c1, ft_isascii(c1));
	printf("'%c' is ASCII: %d\n", c1, isascii(c1));
	printf("'%c' is ASCII: %d\n", c2, ft_isascii(c2));
	printf("'%c' is ASCII: %d\n", c2, isascii(c2));
	printf("'%c' is ASCII: %d\n", c3, ft_isascii(c3));
	printf("'%c' is ASCII: %d\n", c3, isascii(c3));

    return (0);
}
*/