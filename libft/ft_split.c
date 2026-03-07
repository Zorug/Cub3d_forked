/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_split.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/10 02:22:58 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2025/04/11 02:12:54 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

// 1. Determine the length of the segment up to lim
static size_t	ft_seg_len(char const *str, char lim)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != lim)
		i++;
	return (i);
}

// Count how man words are in the string
static int	ft_count_words(char const *s, char lim)
{
	size_t	i;
	size_t	len;
	int		res;

	i = 0;
	res = 0;
	while (s[i])
	{
		while (s[i] == lim)
			i++;
		len = ft_seg_len(s + i, lim);
		i += len;
		if (len > 0)
			res++;
	}
	return (res);
}

// free the array of strings iteraively one by one
static void	*ft_free_arrays(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

// Split the string into words
char	**ft_split(char const *s, char c)
{
	size_t	i;
	int		j;
	int		num_words;
	char	**res_str;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	num_words = ft_count_words(s, c);
	res_str = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!res_str)
		return (NULL);
	while (j < num_words)
	{
		while (s[i] == c)
			i++;
		res_str[j] = ft_substr(s, i, ft_seg_len(s + i, c));
		if (!res_str[j])
			return (ft_free_arrays(res_str));
		i += ft_seg_len(s + i, c);
		j++;
	}
	res_str[num_words] = NULL;
	return (res_str);
}

/* int	main(void)
{
	char	str[] = "";
	char	c = ' ';
	char	**spt = ft_split(str, c);
	int	i = 0;
	while (spt[i] != 0)
	{
		printf("%s", spt[i]);
		i++;
	}
	printf("%c", '\n');
}
 */
