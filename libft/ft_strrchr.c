/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 02:26:05 by tnuno-mo          #+#    #+#             */
/*   Updated: 2024/11/05 21:27:00 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// find the last occurrence of "c" in "s" string and return a pointer to it

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

/*
int main(void)
{
	char test[] = "Hello! How are You?";

	printf ("res:%s\n", ft_strrchr(test, 'e'));
	printf ("res:%s\n", strrchr(test, 'e'));

	return (0);
}
*/
