/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memcmp.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/01 17:20:15 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2024/11/01 22:04:37 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*conv_s1;
	unsigned char	*conv_s2;
	size_t			i;

	conv_s1 = (unsigned char *)s1;
	conv_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (conv_s1[i] != conv_s2[i])
			return (conv_s1[i] - conv_s2[i]);
		i++;
	}
	i--;
	return (conv_s1[i] - conv_s2[i]);
}
/*
int main(void)
{
	char str1[] = "Hello";
	char str2[] = "Hell!";
	size_t n = 10;

	printf("memcmp: %d\n", memcmp(str1, str2, n));
	printf("ft_memcmp: %d\n", ft_memcmp(str1, str2, n));
	return (0);
}
*/