/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/12/08 14:41:42 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2025/03/23 23:52:41 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static char	*read_line(int fd, char *remain, char *buffer);
static char	*set_line(char *line_buffer);

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*remain;

	buffer = (char *)malloc((BUFFER_SIZE +1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if ((fd < 0) || (BUFFER_SIZE < 1))
	{
		free (buffer);
		buffer = NULL;
		return (NULL);
	}
	line = read_line(fd, remain, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	remain = set_line(line);
	return (line);
}

static char	*read_line(int fd, char *remain, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			return (remain);
		if (bytes_read < 0)
		{
			free(remain);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (!remain)
			remain = ft_strdup("");
		temp = remain;
		remain = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			return (remain);
	}
	return (remain);
}

static char	*set_line(char *line_buffer)
{
	char	*next_line_start;
	ssize_t	i;
	ssize_t	l_buf_sz;

	l_buf_sz = ft_strlen(line_buffer);
	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[i + 1] == '\0')
		return (NULL);
	next_line_start = ft_substr(line_buffer, i + 1, l_buf_sz - i - 1);
	if (*next_line_start == '\0')
	{
		free(next_line_start);
		next_line_start = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (next_line_start);
}
/*
#include <stdio.h>

int main (void)
{
	int		fd;
	char	*res;

	fd = open ("test.txt", O_RDONLY);
	res = "a";
	if (!fd)
		return (-1);
	while (res)
	{
		res = get_next_line(fd);
		if (!res)
			break;
		printf ("%s", res);
		free(res);
	}
	close (fd);
	return (0);
}
*/
