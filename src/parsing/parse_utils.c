/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parse_utils.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/02/28 23:19:12 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2026/03/01 00:08:46 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Skip spaces and tabs from the beginning of string
char	*skip_whitespace(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

// Check if a line contains only whitespace or \n
int	is_empty_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

// Free all strings in an array and the array itself
void	free_string_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// Check if a string starts with a given prefix
int	str_starts_with(const char *str, const char *prefix)
{
	int	i;

	i = 0;
	while (prefix[i])
	{
		if (str[i] != prefix[i])
			return (0);
		i++;
	}
	return (1);
}