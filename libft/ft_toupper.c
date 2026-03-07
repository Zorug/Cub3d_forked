/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_toupper.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/27 22:56:54 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2024/11/01 01:32:45 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char c;
	
	c = 'a';
	printf("Original: %c\n", c);
	printf("ft_toupper: %c\n", ft_toupper(c));
	printf("toupper: %c\n\n", toupper(c));

	c = 'A';
	printf("Original: %c\n", c);
	printf("ft_toupper: %c\n", ft_toupper(c));
	printf("toupper: %c\n\n", toupper(c));

	c = '1';
	printf("Original: %c\n", c);
	printf("ft_toupper: %c\n", ft_toupper(c));
	printf("toupper: %c\n", toupper(c));

	return (0);
}
*/