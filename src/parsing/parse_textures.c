/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:02:42 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 21:54:32 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Validate that texture file exists and has .xpm extension
int	validate_texture_path(const char *path)
{
	int		fd;
	int		len;

	if (!path || !*path)
		return (0);
	len = ft_strlen(path);
	if (len < 4 || ft_strcmp(path + len - 4, ".xpm") != 0)
		return (error_return("Texture must be .xpm file"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_return("Cannot open texture file"));
	close(fd);
	return (1);
}

// Set texture path in config for the specified direction (N/S/W/E)
static int	set_texture_path(char *value, t_cfg *cfg, int flag)
{
	char	*path;

	path = skip_whitespace(value);
	if (!validate_texture_path(path))
		return (0);
	if (flag == FLAG_NO && !(cfg->config_flags & FLAG_NO))
		cfg->no_path = ft_strdup(path);
	else if (flag == FLAG_SO && !(cfg->config_flags & FLAG_SO))
		cfg->so_path = ft_strdup(path);
	else if (flag == FLAG_WE && !(cfg->config_flags & FLAG_WE))
		cfg->we_path = ft_strdup(path);
	else if (flag == FLAG_EA && !(cfg->config_flags & FLAG_EA))
		cfg->ea_path = ft_strdup(path);
	else
		return (error_return("Duplicate texture definition"));
	cfg->config_flags |= flag;
	return (1);
}

// Parse a texture line and set the corresponding path in config
int	parse_texture_line(char *line, t_cfg *cfg)
{
	char	*ptr;

	ptr = skip_whitespace(line);
	if (str_starts_with(ptr, "NO "))
		return (set_texture_path(ptr + 3, cfg, FLAG_NO));
	else if (str_starts_with(ptr, "SO "))
		return (set_texture_path(ptr + 3, cfg, FLAG_SO));
	else if (str_starts_with(ptr, "WE "))
		return (set_texture_path(ptr + 3, cfg, FLAG_WE));
	else if (str_starts_with(ptr, "EA "))
		return (set_texture_path(ptr + 3, cfg, FLAG_EA));
	return (0);
}

// Load a single texture from file and get its data address
static int	load_single_texture(t_data *data, char *path, int index)
{
	data->tex[index].img = mlx_xpm_file_to_image(data->mlx, path,
			&data->tex[index].width, &data->tex[index].height);
	if (!data->tex[index].img)
		return (error_return("Failed to load texture"));
	data->tex[index].addr = mlx_get_data_addr(data->tex[index].img,
			&data->tex[index].bits_per_pixel,
			&data->tex[index].line_length,
			&data->tex[index].endian);
	if (!data->tex[index].addr)
		return (error_return("Failed to get texture data"));
	return (1);
}

// Load all four textures (N, S, W, E) from config paths
int	load_all_textures(t_data *data)
{
	if (!load_single_texture(data, data->config.no_path, 0))
		return (0);
	if (!load_single_texture(data, data->config.so_path, 1))
		return (0);
	if (!load_single_texture(data, data->config.we_path, 2))
		return (0);
	if (!load_single_texture(data, data->config.ea_path, 3))
		return (0);
	return (1);
}
