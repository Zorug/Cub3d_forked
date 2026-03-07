/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:01:47 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 21:34:21 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Convert RGB values to hexadecimal color format */
int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

/* Check if RGB value is valid (0-255) */
static int	validate_rgb_value(int value)
{
	return (value >= 0 && value <= 255);
}

/* Validate that a string contains only digits (no signs, no invalid chars) */
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

/* Parse comma-separated RGB values from string */
static int	parse_component(char *str, int *value)
{
	char	*trimmed;

	trimmed = ft_strtrim(str, " \t");
	if (!trimmed)
		return (0);
	if (!is_valid_rgb_string(trimmed))
	{
		free(trimmed);
		return (0);
	}
	*value = ft_atoi(trimmed);
	free(trimmed);
	if (!validate_rgb_value(*value))
		return (0);
	return (1);
}

int	parse_rgb_values(const char *str, int *r, int *g, int *b)
{
	char	**components;
	int		result;

	components = ft_split(str, ',');
	if (!components || !components[0] || !components[1]
		|| !components[2] || components[3])
	{
		free_string_array(components);
		return (0);
	}
	result = parse_component(components[0], r)
		&& parse_component(components[1], g)
		&& parse_component(components[2], b);
	free_string_array(components);
	return (result);
}

