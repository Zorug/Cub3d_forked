/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:15:59 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 14:41:13 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//concatenate two strings
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	res = malloc(len_s1 + len_s2 + 1);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, (len_s1 + 1));
	ft_strlcat(res, s2, (len_s1 + len_s2 + 1));
	res[len_s1 + len_s2] = '\0';
	return (res);
}

/*
int	main(void)
{
	char	*t1 = "Uma rã salta na lagoa... ";
	char	*t2 = "Splash! Silêncio de novo.";
	char	*res = ft_strjoin(t1, t2);

	printf("%s\n", res);
	free(res);
	return (0);
}
*/