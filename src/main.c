/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:42:29 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/09 23:26:26 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	clear_screen(t_img *img)
{
	ft_bzero(img->addr, img->line_length * img->height);
}


/*void	render(t_data *data)
{
	clear_screen(&data->screen);
	draw_circle(&data->screen, data->posX, data->posY, 10, RED);
	mlx_put_image_to_window(data->mlx, data->win, data->screen.img, 0, 0);
}*/

void	draw_circle(t_img *img, int cx, int cy, int radius, int color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			dx = x;
			dy = y;
			if (dx * dx + dy * dy <= radius * radius)
			{
				if (cx + x >= 0 && cx + x < img->width
					&& cy + y >= 0 && cy + y < img->height)
					my_mlx_pixel_put(img, cx + x, cy + y, color);
			}
			x++;
		}
		y++;
	}
}


int	render(t_data *data)
{
	clear_screen(&data->screen);

/*	// teste visual: ponto andando sozinho
	my_mlx_pixel_put(&data->screen,
		(int)data->posX,
		(int)data->posY,
		COLOR_RED);*/

	draw_circle(
		&data->screen,
		(int)data->posX,
		(int)data->posY,
		10,
		COLOR_RED
	);

	mlx_put_image_to_window(
		data->mlx,
		data->win,
		data->screen.img,
		0,
		0);

	return (0);
}

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

	// Desenha um pixel vermelho. Coordenada (X,Y)
	//my_mlx_pixel_put(&data.screen, 10, 10, RED);
	data.posX = 400;
	data.posY = 300;
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