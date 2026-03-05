/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:34:35 by tnuno-mo          #+#    #+#             */
/*   Updated: 2024/11/03 15:34:09 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>

int main(void)
{
    int arr_int[5];
    char str[50] = "Howdy people! What's up?";
    int num = 4259;

    // Fill the array of ints with zeros
    ft_memset(arr_int, 0, sizeof(arr_int));

    // Print the array of ints
    printf("Int array: ");
    for (int i = 0; i < 5; i++)
    printf("%d ", arr_int[i]);
    printf("\n");

    // Fill the 1st 10 characters with '-'
    ft_memset(str, '-', 10);
    printf("Modified string: %s\n", str);

    // Changes int to 0
    ft_memset(&num, 0, sizeof(num));
    printf("Int value modified: %d\n", num);

    return (0);
}
*/