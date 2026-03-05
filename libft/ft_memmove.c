/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:17:46 by tnuno-mo          #+#    #+#             */
/*   Updated: 2024/11/01 23:14:32 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*p_dest;
	const unsigned char	*p_src;
	size_t				i;

	p_dest = dest;
	p_src = src;
	i = 0;
	if (p_dest < p_src)
	{
		while (i < n)
		{
			p_dest[i] = p_src[i];
			i++;
		}
	}
	else if (p_dest > p_src)
	{
		i = n;
		while (i > 0)
		{
			p_dest[i - 1] = p_src[i - 1];
			i--;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	// Test case 1: Non-overlapping regions
	char test1[] = "This is a test";
	ft_memmove(test1 + 5, test1, 10);
	printf("Test 1: %s\n", test1); // Expected: "This This is a"

	// Test case 2: Overlapping regions (src before dest)
	char test2[] = "E ISTO É O QUÊ, HUM?";
	ft_memmove(test2, test2 + 2, 10);
	printf("Test 2: %s\n", test2); // Expected: " ISTO É O QUÊ, HUM?"

	// Test case 3: Overlapping regions (dest before src)
	char test3[] = "This is the test string!";
	ft_memmove(test3 + 2, test3, 10);
	printf("Test 3: %s\n", test3); // Expected: "ThThis is the test string!"

	return (0);
}
*/
