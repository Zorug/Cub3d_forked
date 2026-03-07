/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 04:30:46 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 14:41:13 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//searches for the first occurrence of the character c
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	conv_c;
	unsigned char	*conv_s;

	conv_c = (unsigned char)c;
	conv_s = (unsigned char *)s;
	while (n > 0)
	{
		if (*conv_s == conv_c)
		{
			return (conv_s);
		}
		conv_s++;
		n--;
	}
	return (NULL);
}
/*
int main()
{
	char str[] = "Hello World";
	char *result = ft_memchr(str, 'o', 12);
	if (result == NULL)
	{
		printf("Character not found\n");
	}
	else
	{
		printf("Character found at %s\n", result);
	}
	return (0);
}
*/