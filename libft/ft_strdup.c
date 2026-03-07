/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strdup.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/03 20:40:11 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2025/03/14 04:25:40 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

// Returns pointer to duplicate string
// The ft_strdup() function allocates memory for a copy of the string s1,
// does the copy, and returns a pointer to it.
// The pointer may subsequently be used as an argument to the function free.
char	*ft_strdup(const char *s)
{
	char	*dup;
	int		leng;

	leng = ft_strlen(s);
	dup = malloc(sizeof(char) * (leng + 1));
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, s, leng);
	dup[leng] = '\0';
	return (dup);
}

/*
int main(void)
{
	char *s = "Is this a test?";
	char *d = ft_strdup(s);
	printf("%s\n", d);
	free(d);
	return (0);
}
*/