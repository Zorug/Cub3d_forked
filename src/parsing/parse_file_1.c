/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:08:35 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 21:34:39 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../libft/get_next_line.h"

// Validate that file has .cub extension
/*int	validate_file_extension(const char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (error_return("Invalid filename"));
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
		return (error_return("File must have .cub extension"));
	return (1);
}*/

// Remove newline from end of line
static void	remove_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static char	**grow_lines_array(char **lines, int capacity)
{
	char	**new_lines;
	int		i;

	new_lines = ft_calloc(capacity * 2 + 1, sizeof(char *));
	if (!new_lines)
		return (NULL);
	i = 0;
	while (i < capacity)
	{
		new_lines[i] = lines[i];
		i++;
	}
	free(lines);
	return (new_lines);
}

// Read all lines from file using get_next_line (handles files of any size)
static char	**read_lines_loop(int fd, char **lines, int capacity)
{
	char	*line;
	char	**new_lines;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i == capacity)
		{
			new_lines = grow_lines_array(lines, capacity);
			if (!new_lines)
				return (free(line), free_string_array(lines), NULL);
			lines = new_lines;
			capacity *= 2;
		}
		remove_newline(line);
		lines[i++] = line;
		line = get_next_line(fd);
	}
	if (i == 0)
		return (free(lines), NULL);
	lines[i] = NULL;
	return (lines);
}

char	**read_file_lines(const char *filename)
{
	int		fd;
	char	**lines;
	int		capacity;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	capacity = 16;
	lines = ft_calloc(capacity + 1, sizeof(char *));
	if (!lines)
		return (close(fd), NULL);
	lines = read_lines_loop(fd, lines, capacity);
	close(fd);
	return (lines);
}
