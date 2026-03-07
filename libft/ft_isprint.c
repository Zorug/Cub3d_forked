/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:01:25 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 14:41:12 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	char	c1 = 'A';
	char	c2 = ' ';
	char	c3 = '\n';
	
	printf("'%c' is printable: %d\n", c1, ft_isprint(c1));
	printf("'%c' is printable: %d\n", c2, ft_isprint(c2));
	printf("'%c' is printable: %d\n", c3, ft_isprint(c3));
	return (0);
}
*/