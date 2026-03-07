/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:29:02 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 15:26:37 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Copies n bytes from memory area src to memory area dest.
//	If dest and src overlap, behavior is undefined.

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	test1[10];
	char	test2[10];
	char	test3[10];
	char	test4[10];
	*test1 = '\0';
	*test2 = '\0';
	*test3 = '\0';
	*test4 = '\0';
	
	printf("Before: %s\n", test1);
	ft_memcpy(test1, test2, 1);
	printf("After: %s\n", test1);

	printf("Before: %s\n", test3);
	memcpy(test3, test4, 1);
	printf("After: %s\n", test3);
}
*/