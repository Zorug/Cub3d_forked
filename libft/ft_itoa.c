/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:34:07 by tnuno-mo          #+#    #+#             */
/*   Updated: 2024/11/10 19:02:53 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//determine number of digits (counting with '-')
int	ft_dig_size(int n)
{
	size_t	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

// put digits in res
void	ft_insert_digits(size_t size, int offset, int n, char *res)
{
	while ((int)size > offset)
	{
		res[size - 1] = n % 10 + '0';
		n = n / 10;
		size--;
	}
}

// convert i to string
char	*ft_itoa(int n)
{
	int			offset;
	size_t		size;
	char		*res;

	offset = 0;
	size = ft_dig_size(n);
	res = (char *)malloc(sizeof(char) * size + 1);
	if (!res)
		return (NULL);
	if (n == -2147483648)
	{
		res[0] = '-';
		res[1] = '2';
		n = 147483648;
		offset = 2;
	}
	if (n < 0)
	{
		res[0] = '-';
		offset = 1;
		n = -n;
	}
	ft_insert_digits(size, offset, n, res);
	res[size] = '\0';
	return (res);
}
/*
int main()
{
	int	t1 = 125;
	int	t2 = -814;
	int	t_min = -2147483648;
	int	t_max = 2147483647;
	printf("%s\n", ft_itoa(t1));
	printf("%s\n", ft_itoa(t2));
	printf("%s\n", ft_itoa(t_min));
	printf("%s\n", ft_itoa(t_max));
}
*/