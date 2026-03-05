/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:57:12 by tnuno-mo          #+#    #+#             */
/*   Updated: 2024/10/29 23:37:36 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("ft_isalnum('a'): %d (espected: 1)\n", ft_isalnum('a'));
	printf("ft_isalnum('Z'): %d (espected: 1)\n", ft_isalnum('Z'));
	printf("ft_isalnum('5'): %d (espected: 1)\n", ft_isalnum('5'));
	printf("ft_isalnum('?'): %d (espected: 0)\n", ft_isalnum('?'));
	return (0);
}
*/