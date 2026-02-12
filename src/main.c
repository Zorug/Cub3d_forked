/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:42:29 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/12 23:17:55 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

# define TILE_SIZE 40

static char *test_map[] = {
	"1111111111",
	"1000000001",
	"1000000001",
	"1000000001",
	"1001000001",
	"1001110101",
	"1000010101",
	"1000010101",
	"1000000001",
	"1111111111",
	NULL
};


/*void	clear_screen(t_img *img)
{
	int	x;
	int	y;

	y = 0;
//	while (y < 600)
	while (y < img->height)
	{
		x = 0;
		//while (x < 800)
		while (x < img->width)
		{
			my_mlx_pixel_put(img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}*/

/*
** Apaga o frame anterior

*/
void	clear_screen(t_img *img)
{
	ft_bzero(img->addr, img->line_length * img->height);
}

void	draw_circle(t_img *img, int cx, int cy, int radius, int color)
{
	int	x;
	int	y;
	int	dx; // distância horizontal ao centro
	int	dy; // distância vertical ao centro

	y = -radius;

	// (x - cx)² + (y - cy)² <= r²

	while (y <= radius) // Você percorre um quadrado centrado no círculo:
	{
		x = -radius;
		while (x <= radius)
		{
			dx = x;
			dy = y;
			
/*	* dx * dx + dy * dy = distância² do centro
	* evita sqrt (caríssimo)
	* compara com radius²
	👉 se passar, o pixel está dentro do círculo*/
			if (dx * dx + dy * dy <= radius * radius)
			{
/*	Evita:
	* escrever fora da imagem
	* segmentation fault
	* comportamento indefinido */
				if (cx + x >= 0 && cx + x < img->width
					&& cy + y >= 0 && cy + y < img->height)
					my_mlx_pixel_put(img, cx + x, cy + y, color);
			}
			x++;
		}
		y++;
	}
}

void	draw_square(t_img *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_img *img,
	int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	steps;
	float	x;
	float	y;
	float	x_inc;
	float	y_inc;
	int	i;

	// Vetor da linha
	dx = x1 - x0;
	dy = y1 - y0;

	// Quantos passos?
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	// Incrementos por passo
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;

	// Caminhada do pixel
	x = x0;
	y = y0;

	// Loop principal
	i = 0;
	while (i <= steps)
	{
		// checa limites
		if (x >= 0 && x < img->width && y >= 0 && y < img->height)
			// converte float → int (pixel mais próximo)
			my_mlx_pixel_put(img, (int)x, (int)y, color);

		// Avanço: anda pixel a pixel pela linha.
		x += x_inc;
		y += y_inc;
		i++;
	}
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1')
				draw_square(&data->screen,
					x * TILE_SIZE,
					y * TILE_SIZE,
					TILE_SIZE,
					COLOR_WHITE);
			else
				draw_square(&data->screen,
					x * TILE_SIZE,
					y * TILE_SIZE,
					TILE_SIZE,
					0x00222222);
			x++;
		}
		y++;
	}
}

/*int	render(t_data *data)
{
	int	line_len;
	int	end_x;
	int	end_y;

	clear_screen(&data->screen);

	// círculo = player
	draw_circle(
		&data->screen,
		(int)data->posX,
		(int)data->posY,
		10,
		COLOR_RED
	);

	// vetor de direção
	line_len = 40;
	data->dirX = cos(data->angle);
	data->dirY = sin(data->angle);

	end_x = data->posX + data->dirX * line_len;
	end_y = data->posY + data->dirY * line_len;

	draw_line(
		&data->screen,
		data->posX,
		data->posY,
		end_x,
		end_y,
		COLOR_GREEN
	);

	mlx_put_image_to_window(
		data->mlx,
		data->win,
		data->screen.img,
		0,
		0
	);

	return (0);
}*/

int	render(t_data *data)
{
	int	line_len;
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
	draw_circle(&data->screen,
		data->posX,
		data->posY,
		10,
		COLOR_RED);

	// Linha principal (direção)
	line_len = 80;

	draw_line(&data->screen,
		data->posX,
		data->posY,
		data->posX + data->dirX * line_len,
		data->posY + data->dirY * line_len,
		COLOR_GREEN);

	// Limites do FOV
	left_angle = data->angle - data->fov / 2;
	right_angle = data->angle + data->fov / 2;

	left_x = data->posX + cos(left_angle) * line_len;
	left_y = data->posY + sin(left_angle) * line_len;

	right_x = data->posX + cos(right_angle) * line_len;
	right_y = data->posY + sin(right_angle) * line_len;

	draw_line(&data->screen,
		data->posX,
		data->posY,
		left_x,
		left_y,
		COLOR_BLUE);

	draw_line(&data->screen,
		data->posX,
		data->posY,
		right_x,
		right_y,
		COLOR_BLUE);

	mlx_put_image_to_window(data->mlx,
		data->win,
		data->screen.img,
		0,
		0);

	return (0);
}

/*int	render(t_data *data)
{
	clear_screen(&data->screen);

	draw_map(data);

	draw_circle(&data->screen,
		data->posX,
		data->posY,
		10,
		COLOR_RED);

	mlx_put_image_to_window(data->mlx,
		data->win,
		data->screen.img,
		0,
		0);

	return (0);
}*/


int	main(void)
{
	t_data	data;

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

	// Initial position of the player in the map
	data.posX = 400;
	data.posY = 300;

	// mapa
	data.map = test_map;
	data.map_height = 10;
	data.map_width = 10;

	// vetor
	data.angle = 0; // olhando para a direita
	data.dirX = cos(data.angle);
	data.dirY = sin(data.angle);

	// fov angle (M_PI is working fine, form math.h)
	data.fov = M_PI / 3; // 60 graus


	//my_mlx_pixel_put(&data.screen, data.posX, data.posY, RED);
	
	//A imagem vira visível. Copia o buffer para a janela
	//mlx_put_image_to_window(data.mlx, data.win, data.screen.img, 0, 0);
	
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