/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:08:02 by tnuno-mo          #+#    #+#             */
/*   Updated: 2024/11/05 21:20:40 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Locates the first occurrence of c (converted to a char).
// The terminating null character is considered part of the string;
// therefore if c is '\0', the function locates the terminating '\0'.

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ((char)c))
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

/*
int main(void)
{
	char test[] = "Hello! How are You?";

	printf ("res:%s\n", ft_strchr(test, 'a'));
	printf ("res:%s\n", strchr(test, 'a'));

	return (0);
}
*/