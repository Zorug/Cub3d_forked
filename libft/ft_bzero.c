/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:13:37 by tnuno-mo          #+#    #+#             */
/*   Updated: 2024/10/29 23:35:13 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = s;
	while (i < n)
	{
		*p = 0;
		i++;
		p++;
	}
}
/*

int main (void)
{
	char test1[20] = "Gooood Morning!";
	char test2[20] = "Gooood Morning!";

	printf("Before(orig_f): %s\n", test1);
	printf("Before(myfunc): %s\n", test2);

	bzero(test1, 5);
	ft_bzero(test2, 5);

	printf("After(orig_f): %s\n", test1);
	printf("After(myfunc): %s\n", test2);
}
*/