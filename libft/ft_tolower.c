/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 23:04:50 by tnuno-mo          #+#    #+#             */
/*   Updated: 2024/11/01 01:05:07 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char c;
	
	c = 'a';
	printf("Original: %c\n", c);
	printf("ft_tolower: %c\n", ft_tolower(c));
	printf("tolower: %c\n\n", tolower(c));

	c = 'A';
	printf("Original: %c\n", c);
	printf("ft_tolower: %c\n", ft_tolower(c));
	printf("tolower: %c\n\n", tolower(c));

	c = '1';
	printf("Original: %c\n", c);
	printf("ft_tolower: %c\n", ft_tolower(c));
	printf("tolower: %c\n", tolower(c));

	return (0);
}
*/