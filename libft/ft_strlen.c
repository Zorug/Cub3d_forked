/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:16:19 by tnuno-mo          #+#    #+#             */
/*   Updated: 2024/11/05 19:30:12 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

//return the size of a string without '\0' character.
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac == 2)
		printf("strlen is: %zu", ft_strlen(av[1]));
	return (0);
}
*/