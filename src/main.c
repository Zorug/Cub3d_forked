/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:42:29 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/22 16:37:17 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* map for test */
static char *test_map[] = {
	"11111111111111111111",
	"10000000011000000001",
	"10000000011000000001",
	"1000000000000000E001",
	"10010000011001000001",
	"10011101011001110101",
	"10000101011000010101",
	"10000101011000010101",
	"10000000011000000001",
	"11111111111111111111",
	NULL
};

void	load_map(t_data *data, char **src_map)
{
	int	i;

	i = 0;
	data->map_height = 0;
	while (src_map[data->map_height])
		data->map_height++;
	data->map = malloc(sizeof(char *) * (data->map_height + 1)); // cuidar com o free!!
	if (!data->map)
		return ; // depois você pode tratar erro melhor
	while (i < data->map_height)
	{
		data->map[i] = ft_strdup(src_map[i]);
		i++;
	}
	data->map[i] = NULL;
	data->map_width = ft_strlen(data->map[0]);
}

int	main(void)
{
	t_data	data;

	init_mlx(&data);
	init_screen(&data);

	load_map(&data, test_map);
	init_player(&data);
	init_mouse(&data);
	init_hooks(&data);

	mlx_loop(data.mlx);
	return (0);
}

/*
[ RAM ] ---> imagem (pixels)
   |
   |  mlx_put_image_to_window
   v
[ JANELA ]
*/