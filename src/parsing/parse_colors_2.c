/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:26:29 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/07 21:32:55 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Parse and set floor color from RGB string */
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

/* Parse and set ceiling color from RGB string */
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

/* Parse a color line and update scene config (F for floor, C for ceiling) */
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
