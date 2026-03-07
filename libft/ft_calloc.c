/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_calloc.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/03 15:38:21 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2025/02/02 18:17:14 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	arr;

	arr = nmemb * size;
	res = malloc(arr);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, arr);
	return (res);
}

/*
int main(void)
{
	char *str = "Ariops";
	str = (char *)ft_calloc(10, sizeof(char));
	printf("%s\n", str);
	free(str);

	char *str2 = "Olaré";
	str2 = (char *)ft_calloc(10, sizeof(char));
	printf("%s\n", str2);
	free(str2);
	
	return (0);
}
*/
