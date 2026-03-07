/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:48:36 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 14:41:13 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	size_t	i;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	res = malloc(sizeof(char) * (len_s + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len_s)
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

/* 
char	ft_test(unsigned int i, char c)
{
	return (c + i);
}

int	main(void)
{
	char	*original = "Yo! What's up?!";
	char	*modified;

	// Use ft_strmapi with the to_upper function
	modified = ft_strmapi(original, ft_test);

	if (modified == NULL)
	{
		printf("Memory allocation failed\n");
		return (1);
	}

	printf("Original: %s\n", original);
	printf("Modified: %s\n", modified);

	// Free the allocated memory
	free(modified);

	return (0);
}
 */