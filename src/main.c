/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:42:29 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/01 00:26:54 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./cub3D <map.cub>", 2);
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	if (!parse_scene_file(argv[1], &data))
		return (1);
	init_mlx(&data);
	if (!load_all_textures(&data))
		error_exit(&data, "Failed to load textures");
	init_screen(&data);
	init_player(&data);
	init_mouse(&data);
	init_hooks(&data);
	mlx_loop(data.mlx);
	return (0);
}
