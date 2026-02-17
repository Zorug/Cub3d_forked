/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:46:13 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/17 23:19:46 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* (x - cx)² + (y - cy)² <= r² */
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
					my_mlx_pixel_put(img, c->center.x + x,
						c->center.y + y, c->color);
			}
			x++;
		}
		y++;
	}
}

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
			my_mlx_pixel_put(img, s->pos.x + j,
				s->pos.y + i, s->color);
			j++;
		}
		i++;
	}
}

/* Draw a line using DDA algorithm */
/*void	draw_line(t_img *img, t_line *l)
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
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
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
}*/

/* variables used in draw_line(), draw.c*/
/*typedef struct s_dda
{
	int		dx; // distância horizontal total
	int		dy; // distância vertical total
	int		steps; // quantos pixels desenhar
	float	x; // posição atual X
	float	y; // posição atual Y
	float	x_inc; // avanço em X por passo
	float	y_inc; // avanço em Y por passo
	int		i; // contador do loop
}	t_dda;*/

/* Draw a line using DDA algorithm */
void	draw_line(t_img *img, t_line *l)
{
	t_dda	d;

	d.dx = l->end.x - l->start.x;
	d.dy = l->end.y - l->start.y;
	if (abs(d.dx) > abs(d.dy))
		d.steps = abs(d.dx);
	else
		d.steps = abs(d.dy);
	d.x_inc = d.dx / (float)d.steps;
	d.y_inc = d.dy / (float)d.steps;
	d.x = l->start.x;
	d.y = l->start.y;
	d.i = 0;
	while (d.i <= d.steps)
	{
		if (d.x >= 0 && d.x < img->width
			&& d.y >= 0 && d.y < img->height)
			my_mlx_pixel_put(img, (int)d.x, (int)d.y, l->color);
		d.x += d.x_inc;
		d.y += d.y_inc;
		d.i++;
	}
}

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
				tile.color = COLOR_GRAY;
			draw_square(&data->screen, &tile);
			x++;
		}
		y++;
	}
}
