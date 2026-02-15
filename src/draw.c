/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:46:13 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/15 19:33:40 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* (x - cx)² + (y - cy)² <= r² */
/*void	draw_circle(t_img *img, int cx, int cy, int radius, int color)
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
			
	* dx * dx + dy * dy = distância² do centro
	* evita sqrt (caríssimo)
	* compara com radius²
	👉 se passar, o pixel está dentro do círculo
			if (dx * dx + dy * dy <= radius * radius)
			{
	Evita:
	* escrever fora da imagem
	* segmentation fault
	* comportamento indefinido 
				if (cx + x >= 0 && cx + x < img->width
					&& cy + y >= 0 && cy + y < img->height)
					my_mlx_pixel_put(img, cx + x, cy + y, color);
			}
			x++;
		}
		y++;
	}
}*/
void	draw_circle(t_img *img, t_circle *c)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = -c->radius;
	while (y <= c->radius)
	{
		x = -c->radius;
		while (x <= c->radius)
		{
			dx = x;
			dy = y;
			if (dx * dx + dy * dy <= c->radius * c->radius)
			{
				if (c->center.x + x >= 0 && c->center.x + x < img->width
					&& c->center.y + y >= 0 && c->center.y + y < img->height)
					my_mlx_pixel_put(
						img,
						c->center.x + x,
						c->center.y + y,
						c->color);
			}
			x++;
		}
		y++;
	}
}

/*void	draw_square(t_img *img, int x, int y, int size, int color)
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
}*/
void	draw_square(t_img *img, t_square *s)
{
	int	i;
	int	j;

	i = 0;
	while (i < s->size)
	{
		j = 0;
		while (j < s->size)
		{
			my_mlx_pixel_put(
				img,
				s->pos.x + j,
				s->pos.y + i,
				s->color);
			j++;
		}
		i++;
	}
}

/*void	draw_line(t_img *img,
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
}*/
void	draw_line(t_img *img, t_line *l)
{
	int		dx;
	int		dy;
	int		steps;
	float	x;
	float	y;
	float	x_inc;
	float	y_inc;
	int		i;

	dx = l->end.x - l->start.x;
	dy = l->end.y - l->start.y;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;

	x = l->start.x;
	y = l->start.y;

	i = 0;
	while (i <= steps)
	{
		if (x >= 0 && x < img->width && y >= 0 && y < img->height)
			my_mlx_pixel_put(img, (int)x, (int)y, l->color);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

/*void	draw_map(t_data *data)
{
	//int	x;
	//int	y;
	t_square	tile;

	tile.size = TILE_SIZE;
	
	//y = 0;
	tile.pos.y = 0;
	while (tile.pos.y < data->map_height)
	{
		tile.pos.x = 0;
		while (tile.pos.x < data->map_width)
		{
			if (data->map[tile.pos.y][tile.pos.x] == '1')
			{
				tile.color = COLOR_WHITE;
				draw_square(&data->screen, &tile);
			}
				//draw_square(&data->screen,
				//	x * TILE_SIZE,
				//	tile.pos.y * TILE_SIZE,
				//	TILE_SIZE,
				//	COLOR_WHITE);
			else
			{
				tile.color = 0x00222222;
				draw_square(&data->screen, &tile);
			}
				//draw_square(&data->screen,
				//	x * TILE_SIZE,
				//	y * TILE_SIZE,
				//	TILE_SIZE,
				//	0x00222222);
			tile.pos.x++;
		}
		tile.pos.y++;
	}
}*/

void	draw_map(t_data *data)
{
	int			x;
	int			y;
	t_square	tile;

	tile.size = TILE_SIZE;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			tile.pos.x = x * TILE_SIZE;
			tile.pos.y = y * TILE_SIZE;

			if (data->map[y][x] == '1')
				tile.color = COLOR_WHITE;
			else
				tile.color = 0x00222222;

			draw_square(&data->screen, &tile);
			x++;
		}
		y++;
	}
}
