/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:20:39 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 14:41:13 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while ((big[i + j] == little[j]) && (i + j < len))
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
	const char	*largestring = "Foo Bar Baz";
	const char	*smallstring = "Bar";
	char		*ptr1;

	ptr1 = ft_strnstr(largestring, smallstring, 4);
	printf("Test 1 Expected: (null)\n");
	printf("Test 1 - String: %s\n\n", ptr1);
	

	const char	*largestring2 = "Hello World";
	const char	*smallstring2 = "World";
	char		*ptr2;

	ptr2 = ft_strnstr(largestring2, smallstring2, 11);
	printf("Test 2 Expected: World\n");
	printf("Test 2 - String: %s\n\n", ptr2);

	const char	*largestring3 = "Hello World";
	const char	*smallstring3 = "world";
	char		*ptr3;

	ptr3 = ft_strnstr(largestring3, smallstring3, 11);
	printf("Test 3 Expected: (null) (case-sensitive search)\n");
	printf("Test 3 - String: %s\n\n", ptr3);

	const char	*largestring4 = "Hello World";
	const char	*smallstring4 = "";
	char		*ptr4;

	ptr4 = ft_strnstr(largestring4, smallstring4, 11);
	printf("Test 4 Expected: Hello World (empty string matches)\n");
	printf("Test 4 - String: %s\n\n", ptr4);

	return (0);
}
*/