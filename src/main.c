/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:42:29 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/22 15:28:51 by cgross-s         ###   ########.fr       */
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
	int		i;

	data.mlx = mlx_init(); // Conecta ao X11. Sem isso, nada funciona

	// Cria uma janela vazia
	data.screen.width = 800; // start
	data.screen.height = 600; // start

	// posiciona o centro da janela (mouse moving)
	//data.win_center_x = data.screen.width / 2;
	//data.win_center_y = data.screen.height / 2;


	data.win = mlx_new_window(data.mlx, //start
		data.screen.width, data.screen.height, "CUB3D");
	// Cria um buffer de pixels na memória. Ainda não sabemos onde ele está
	data.screen.img = mlx_new_image(data.mlx, //start
		data.screen.width, data.screen.height);

	// img.addr aponta para a memória real
	// Você pode manipular pixel por pixel
	// Sem isso, não dá pra desenhar manualmente.
	data.screen.addr = mlx_get_data_addr(data.screen.img, 
		&data.screen.bits_per_pixel, &data.screen.line_length, &data.screen.endian);

	// mapa
	load_map(&data, test_map);

	// player
	find_player(&data);
	data.dirX = cos(data.angle);
	data.dirY = sin(data.angle);

	// fov angle (M_PI is working fine, form math.h)
	data.fov = M_PI / 3;
	data.move_speed = 0.5;
	data.rot_speed = 0.4;
	
	/*data.mouse_init = 0;
	data.mouse_sensitivity = 0.002;
	mlx_hook(data.win, 6, 1L << 6, mouse_move, &data);*/

	// mouse moving stuffs
/*	data.mouse_sensitivity = 0.002;
	data.win_center_x = data.screen.width / 2;
	data.win_center_y = data.screen.height / 2;
	mlx_mouse_hide(data.mlx, data.win);
	mlx_mouse_move(data.mlx, data.win,
		data.win_center_x,
		data.win_center_y);
	mlx_hook(data.win, 6, 1L << 6, mouse_move, &data);*/
	data.mouse_enabled = 0;           // começa desligado
	data.mouse_sensitivity = 0.002;
	data.win_center_x = data.screen.width / 2;
	data.win_center_y = data.screen.height / 2;
	mlx_hook(data.win, 6, 1L << 6, mouse_move, &data);

	// ao apertar esc sai
	mlx_key_hook(data.win, key_hook, &data);
	// fechar clicando no x
	mlx_hook(data.win, 17, 0, close_window, &data);
	//chamar o render
	mlx_loop_hook(data.mlx, render, &data);
	// Mantém a janela aberta. Escuta eventos. Sem isso, o programa fecha imediatamente
	mlx_loop(data.mlx);

}

/*
[ RAM ] ---> imagem (pixels)
   |
   |  mlx_put_image_to_window
   v
[ JANELA ]
*/