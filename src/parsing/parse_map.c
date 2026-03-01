/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:05:19 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/01 00:17:31 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Check if a line contains only valid map characters
int	is_map_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_valid_map_char(line[i]) && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

// Count the number of consecutive map lines starting from given index
static int	count_map_lines(char **lines, int start)
{
	int	count;

	count = 0;
	while (lines[start + count] && is_map_line(lines[start + count]))
		count++;
	return (count);
}

// Copy map lines from file into a new array, removing newline characters
char	**copy_map_lines(char **lines, int start, int count)
{
	char	**map;
	int		i;
	int		len;

	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < count)
	{
		len = ft_strlen(lines[start + i]);
		if (lines[start + i][len - 1] == '\n')
			lines[start + i][len - 1] = '\0';
		map[i] = ft_strdup(lines[start + i]);
		if (!map[i])
		{
			free_string_array(map);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;
	return (map);
}

// Calculate and store map dimensions (width and height)
static int	calculate_map_dimensions(char **map, t_data *data)
{
	int	i;
	int	len;

	data->map_height = 0;
	data->map_width = 0;
	while (map[data->map_height])
	{
		len = ft_strlen(map[data->map_height]);
		if (len > data->map_width)
			data->map_width = len;
		data->map_height++;
	}
	if (data->map_height == 0 || data->map_width == 0)
		return (error_return("Empty map"));
	return (1);
}

// Extract map from file lines and validate its structure
int	extract_and_validate_map(char **lines, int start_idx, t_data *data)
{
	int		map_line_count;

	map_line_count = count_map_lines(lines, start_idx);
	if (map_line_count == 0)
		return (error_return("No map found in file"));
	data->map = copy_map_lines(lines, start_idx, map_line_count);
	if (!data->map)
		return (error_return("Failed to allocate map memory"));
	if (!calculate_map_dimensions(data->map, data))
		return (0);
	if (!validate_map(data->map))
		return (error_return("Invalid map structure"));
	return (1);
}