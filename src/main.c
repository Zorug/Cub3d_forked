/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:42:29 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/16 22:39:49 by cgross-s         ###   ########.fr       */
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

/* direction of the player */
void	set_player_direction(t_data *data, char c)
{
	if (c == 'N')
		data->angle = -M_PI / 2;
	else if (c == 'S')
		data->angle = M_PI / 2;
	else if (c == 'E')
		data->angle = 0;
	else if (c == 'W')
		data->angle = M_PI;

	data->dirX = cos(data->angle);
	data->dirY = sin(data->angle);
}

/* Player start position */
void	find_player(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				data->posX = x + 0.5;
				data->posY = y + 0.5;
				set_player_direction(data, data->map[y][x]);
				data->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

int	render(t_data *data)
{
	double	left_angle;
	double	right_angle;
	int	left_x;
	int	left_y;
	int	right_x;
	int	right_y;

	clear_screen(&data->screen);

	//desenha o mapa
	draw_map(data);

	// Atualiza vetor principal
	data->dirX = cos(data->angle);
	data->dirY = sin(data->angle);

	// Desenha player
	/*draw_circle(&data->screen,
		data->posX * TILE_SIZE,
		data->posY * TILE_SIZE,
		TILE_SIZE / 4,
		COLOR_RED);*/
	t_circle	player;
	player.center.x = data->posX * TILE_SIZE;
	player.center.y = data->posY * TILE_SIZE;
	player.radius = TILE_SIZE / 4;
	player.color = COLOR_RED;
	draw_circle(&data->screen, &player);


	/*draw_line(&data->screen,
		data->posX * TILE_SIZE,
		data->posY * TILE_SIZE,
		(data->posX + data->dirX) * TILE_SIZE,
		(data->posY + data->dirY) * TILE_SIZE,
		COLOR_GREEN);*/
	t_line	dir;
	dir.start.x = data->posX * TILE_SIZE;
	dir.start.y = data->posY * TILE_SIZE;
	dir.end.x = (data->posX + data->dirX) * TILE_SIZE;
	dir.end.y = (data->posY + data->dirY) * TILE_SIZE;
	dir.color = COLOR_GREEN;
	draw_line(&data->screen, &dir);

	// Limites do FOV
	left_angle = data->angle - data->fov / 2;
	right_angle = data->angle + data->fov / 2;

	//right_x = (data->posX + cos(right_angle)) * TILE_SIZE;
	//right_y = (data->posY + sin(right_angle)) * TILE_SIZE;
	dir.end.x = (data->posX + cos(right_angle)) * TILE_SIZE;
	dir.end.y = (data->posY + sin(right_angle)) * TILE_SIZE;
	dir.color = COLOR_BLUE;

	/*draw_line(&data->screen, // linha limite FOV
		data->posX * TILE_SIZE,
		data->posY * TILE_SIZE,
		right_x,
		right_y,
		COLOR_BLUE);*/
	draw_line(&data->screen, &dir);

	//left_x = (data->posX + cos(left_angle)) * TILE_SIZE;
	//left_y = (data->posY + sin(left_angle)) * TILE_SIZE;
	dir.end.x = (data->posX + cos(left_angle)) * TILE_SIZE;
	dir.end.y = (data->posY + sin(left_angle)) * TILE_SIZE;
	/*draw_line(&data->screen, // linha limite FOV esquerdo
		data->posX * TILE_SIZE,
		data->posY * TILE_SIZE,
		left_x,
		left_y,
		COLOR_BLUE);*/
	draw_line(&data->screen, &dir);

	// first ray to cast
	//cast_single_ray(data);
	int i;
	int rays = 60;
	double startAngle = data->angle - data->fov / 2;
	double angleStep = data->fov / rays;

	for (i = 0; i < rays; i++)
	{
		cast_single_ray(data, startAngle + i * angleStep);
	}


	mlx_put_image_to_window(data->mlx, data->win,
		data->screen.img, 0, 0);

	return (0);
}

int	main(void)
{
	t_data	data;
	int		i;

	data.mlx = mlx_init(); // Conecta ao X11. Sem isso, nada funciona

	// Cria uma janela vazia
	data.screen.width = 800;
	data.screen.height = 600;

	data.win = mlx_new_window(data.mlx,
		data.screen.width, data.screen.height, "CUB3D");
	// Cria um buffer de pixels na memória. Ainda não sabemos onde ele está
	data.screen.img = mlx_new_image(data.mlx,
		data.screen.width, data.screen.height);

	// img.addr aponta para a memória real
	// Você pode manipular pixel por pixel
	// Sem isso, não dá pra desenhar manualmente.
	data.screen.addr = mlx_get_data_addr(data.screen.img, 
		&data.screen.bits_per_pixel, &data.screen.line_length, &data.screen.endian);

	// mapa
	i = 0;
	data.map_height = 0;// aqui estava a dar um segfail
	//data.map = test_map;
	while (test_map[data.map_height]) // evitando erro, não esquece: free
		data.map_height++;
	data.map = malloc(sizeof(char *) * (data.map_height + 1)); //FREE IT!
	while (i < data.map_height)
	{
		data.map[i] = ft_strdup(test_map[i]);
		i++;
	}
	data.map[i] = NULL;
	data.map_width = ft_strlen(data.map[0]);

	// player
	find_player(&data);
	//data.angle = 0; // olhando para a direita
	data.dirX = cos(data.angle);
	data.dirY = sin(data.angle);

	// fov angle (M_PI is working fine, form math.h)
	data.fov = M_PI / 3;
	data.move_speed = 0.5;
	data.rot_speed = 0.4;
	
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