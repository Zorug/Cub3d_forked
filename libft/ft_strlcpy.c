/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:52:30 by tnuno-mo          #+#    #+#             */
/*   Updated: 2024/11/07 21:00:40 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Copy src to dest up to "size". Return:size of string copied without '\0'
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	l;

	i = 0;
	l = 0;
	while (src[l] != '\0')
		l++;
	if (size != '\0')
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (l);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
	char src1[] = "It should end here and not continue further";
	char dest1[] = "The destination is not where it starts! Or is it?";
	printf("%zu | %s\n", ft_strlcpy(dest1, src1, 19), dest1);

//	compare with original function
	char src2[] = "It should end here and not continue further";
	char dest2[] = "The destination is not where it starts! Or is it?";
	printf("%zu | %s\n", strlcpy(dest2, src2, 19), dest2);

	return (0);
}
*/