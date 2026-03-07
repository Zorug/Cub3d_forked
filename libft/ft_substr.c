/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 21:51:52 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 15:29:43 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//create a substring starting in "start" with "len" lenght
//the substring content is part of the original
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > (s_len - start))
		len = s_len - start;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len +1);
	substr[len] = '\0';
	return (substr);
}

/*
int main(void)
{
	char *s = "Hello World!";
	char *substr = ft_substr(s, 6, 5);
	printf("%s\n", substr);
	free(substr);

	substr = ft_substr(s, 6, 100);
	printf("%s\n", substr);
	free(substr);

	substr = ft_substr(s, 100, 5);
	printf("%s\n", substr);
	free(substr);

	substr = ft_substr(s, 3, 0);
	printf("%s\n", substr);
	free(substr);
	return (0);
}
*/