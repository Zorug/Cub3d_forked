/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:08:35 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 15:49:08 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../libft/get_next_line.h"

// Validate that file has .cub extension
int	validate_file_extension(const char *filename)
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
}

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
char	**read_file_lines(const char *filename)
{
	int		fd;
	char	*line;
	char	**lines;
	int		i;
	int		capacity;
	char	**new_lines;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	capacity = 16;
	lines = ft_calloc(capacity + 1, sizeof(char *));
	if (!lines)
	{
		close(fd);
		return (NULL);
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i == capacity)
		{
			new_lines = grow_lines_array(lines, capacity);
			if (!new_lines)
			{
				free(line);
				free_string_array(lines);
				close(fd);
				return (NULL);
			}
			lines = new_lines;
			capacity *= 2;
		}
		remove_newline(line);
		lines[i] = line;
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	if (i == 0)
	{
		free(lines);
		return (NULL);
	}
	lines[i] = NULL;
	return (lines);
}

// Parse a single config line (texture, color, or map)
static int	parse_config_line(char *line, t_scene_config *cfg)
{
	if (is_empty_line(line))
		return (1);
	if (parse_texture_line(line, cfg))
		return (1);
	if (parse_color_line(line, cfg))
		return (1);
	if (is_map_line(line))
		return (2);
	return (error_return("Invalid configuration line"));
}

// Parse all configuration lines and find where map starts
static int	parse_configuration(char **lines, t_scene_config *cfg, int *idx)
{
	int	result;
	int	i;

	i = 0;
	while (lines[i])
	{
		result = parse_config_line(lines[i], cfg);
		if (result == 0)
			return (0);
		if (result == 2)
		{
			*idx = i;
			break ;
		}
		i++;
	}
	if ((cfg->config_flags & FLAG_ALL) != FLAG_ALL)
		return (error_return("Missing configuration elements"));
	return (1);
}

// Parse scene file: read all lines, config, and map
int	parse_scene_file(const char *filename, t_data *data)
{
	char	**lines;
	int		map_start_idx;

	if (!validate_file_extension(filename))
		return (0);
	lines = read_file_lines(filename);
	if (!lines)
		return (error_return("Cannot open file"));
	ft_bzero(&data->config, sizeof(t_scene_config));
	if (!parse_configuration(lines, &data->config, &map_start_idx))
	{
		free_string_array(lines);
		return (0);
	}
	if (!extract_and_validate_map(lines, map_start_idx, data))
	{
		free_string_array(lines);
		return (0);
	}
	free_string_array(lines);
	return (1);
}
