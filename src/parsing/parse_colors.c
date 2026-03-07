/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:01:47 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 14:22:49 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Convert RGB values to hexadecimal color format
int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

// Check if RGB value is valid (0-255)
static int	validate_rgb_value(int value)
{
	return (value >= 0 && value <= 255);
}

// Validate that a string contains only digits (no signs, no invalid chars)
static int	is_valid_rgb_string(const char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// Parse comma-separated RGB values from string
int	parse_rgb_values(const char *str, int *r, int *g, int *b)
{
	char	**components;
	char	*trimmed;

	components = ft_split(str, ',');
	if (!components || !components[0] || !components[1] || !components[2])
	{
		free_string_array(components);
		return (0);
	}
	if (components[3])
	{
		free_string_array(components);
		return (0);
	}
	trimmed = ft_strtrim(components[0], " \t");
	if (!is_valid_rgb_string(trimmed))
	{
		free(trimmed);
		free_string_array(components);
		return (0);
	}
	*r = ft_atoi(trimmed);
	free(trimmed);
	trimmed = ft_strtrim(components[1], " \t");
	if (!is_valid_rgb_string(trimmed))
	{
		free(trimmed);
		free_string_array(components);
		return (0);
	}
	*g = ft_atoi(trimmed);
	free(trimmed);
	trimmed = ft_strtrim(components[2], " \t");
	if (!is_valid_rgb_string(trimmed))
	{
		free(trimmed);
		free_string_array(components);
		return (0);
	}
	*b = ft_atoi(trimmed);
	free(trimmed);
	free_string_array(components);
	if (!validate_rgb_value(*r) || !validate_rgb_value(*g)
		|| !validate_rgb_value(*b))
		return (0);
	return (1);
}

// Parse and set floor color from RGB string
static int	set_floor_color(char *value_str, t_scene_config *cfg)
{
	int	r;
	int	g;
	int	b;

	if (cfg->config_flags & FLAG_F)
		return (error_return("Duplicate floor color definition"));
	if (!parse_rgb_values(value_str, &r, &g, &b))
		return (error_return("Invalid floor color format"));
	cfg->floor_color = rgb_to_hex(r, g, b);
	cfg->config_flags |= FLAG_F;
	return (1);
}

// Parse and set ceiling color from RGB string
static int	set_ceiling_color(char *value_str, t_scene_config *cfg)
{
	int	r;
	int	g;
	int	b;

	if (cfg->config_flags & FLAG_C)
		return (error_return("Duplicate ceiling color definition"));
	if (!parse_rgb_values(value_str, &r, &g, &b))
		return (error_return("Invalid ceiling color format"));
	cfg->ceiling_color = rgb_to_hex(r, g, b);
	cfg->config_flags |= FLAG_C;
	return (1);
}

// Parse a color line and update scene config (F for floor, C for ceiling)
int	parse_color_line(char *line, t_scene_config *cfg)
{
	char	*ptr;

	ptr = skip_whitespace(line);
	if (*ptr == 'F' && *(ptr + 1) == ' ')
		return (set_floor_color(skip_whitespace(ptr + 2), cfg));
	else if (*ptr == 'C' && *(ptr + 1) == ' ')
		return (set_ceiling_color(skip_whitespace(ptr + 2), cfg));
	return (0);
}