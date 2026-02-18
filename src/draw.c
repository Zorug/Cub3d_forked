/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:46:13 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/18 22:39:47 by cgross-s         ###   ########.fr       */
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
