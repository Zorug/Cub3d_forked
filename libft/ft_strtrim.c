/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strtrim.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/05 21:04:53 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2024/11/05 23:17:16 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

// remove the characters in "set" from the beginning and the end of "s1"
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (ft_strchr(set, s1[i]) != NULL)
		i++;
	j = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[j]) != NULL)
		j--;
	return (ft_substr(s1, i, j - i + 1));
}
/*
int main(void)
{
	char *s;
	char *set;
	char *trim;

	s = "This is the test string, this is not any other string!";
	set = "This is wrong!";
	trim = ft_strtrim(s, set);
	printf("%s\n", trim);
	free(trim);

	s = "This is the test string, this is not any other string!";
	set = "T";
	trim = ft_strtrim(s, set);
	printf("%s\n", trim);
	free(trim);
	return (0);
}
*/
