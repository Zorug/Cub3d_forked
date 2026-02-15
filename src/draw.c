/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:46:13 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/15 17:50:01 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* (x - cx)² + (y - cy)² <= r² */
void	draw_circle(t_img *img, int cx, int cy, int radius, int color)
{
	int	x;
	int	y;
	int	dx; // distância horizontal ao centro
	int	dy; // distância vertical ao centro

	y = -radius;

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
