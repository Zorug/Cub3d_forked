/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:42:29 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/07 20:57:07 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Parse scene file and validate map */
static int	load_scene(char *file, t_data *data)
{
	if (!parse_scene_file(file, data))
	{
		free_scene_config(&data->config);
		free_map(data);
		return (0);
	}
	return (1);
}

/* Initialize MLX, textures, screen and rays */
static void	init_game(t_data *data)
{
	if (!init_mlx(data))
		error_exit(data, "Failed to initialize MLX");
	if (!load_all_textures(data))
		error_exit(data, "Failed to load textures");
	if (!init_screen(data))
		error_exit(data, "Failed to initialize screen");
	if (!init_rays_cache(data))
		error_exit(data, "Failed to initialize rays cache");
	init_player(data);
	init_mouse(data);
	init_hooks(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./cub3D <map.cub>", 2);
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	if (!load_scene(argv[1], &data))
		return (1);
	init_game(&data);
	mlx_loop(data.mlx);
	return (0);
}
