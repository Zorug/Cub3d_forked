/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 01:15:47 by tnuno-mo          #+#    #+#             */
/*   Updated: 2024/10/29 23:48:55 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/*
int	main(void)
{
	printf("ft_isalpha('a'): %d (espected: 1)\n", ft_isalpha('a'));
	printf("ft_isalpha('Z'): %d (espected: 1)\n", ft_isalpha('Z'));
	printf("ft_isalpha('5'): %d (espected: 0)\n", ft_isalpha('5'));
	printf("ft_isalpha('?'): %d (espected: 0)\n", ft_isalpha('?'));
	return (0);
}
*/