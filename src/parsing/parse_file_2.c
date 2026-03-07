/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:26:47 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/07 21:54:32 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../libft/get_next_line.h"

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

// Parse a single config line (texture, color, or map)
static int	parse_config_line(char *line, t_cfg *cfg)
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
static int	parse_configuration(char **lines, t_cfg *cfg, int *idx)
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
	ft_bzero(&data->config, sizeof(t_cfg));
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
