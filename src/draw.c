/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:46:13 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/22 17:26:37 by cgross-s         ###   ########.fr       */
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

/*void	draw_square(t_img *img, t_square *s)
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
}*/

void	draw_rect(t_img *img, t_rect *r)
{
	int	x;
	int	y;

	y = 0;
	while (y < r->height)
	{
		x = 0;
		while (x < r->width)
		{
			if (r->pos.x + x >= 0 && r->pos.x + x < img->width
				&& r->pos.y + y >= 0 && r->pos.y + y < img->height)
				my_mlx_pixel_put(
					img,
					r->pos.x + x,
					r->pos.y + y,
					r->color
				);
			x++;
		}
		y++;
	}
}

void	draw_square(t_img *img, t_square *s)
{
	t_rect	r;

	r.pos = s->pos;
	r.width = s->size;
	r.height = s->size;
	r.color = s->color;
	draw_rect(img, &r);
}

/* Draw a line using DDA algorithm 
https://www.youtube.com/watch?v=Oyp3eq580jA */
void	draw_line(t_img *img, t_line *l)
{
	t_dda	d;

	d.dx = l->end.x - l->start.x;
	d.dy = l->end.y - l->start.y;
	if (abs(d.dx) > abs(d.dy)) // the size of the step is based on the bigger value
		d.steps = abs(d.dx);
	else
		d.steps = abs(d.dy);
	d.x_inc = d.dx / (float)d.steps; // incremento em x
	d.y_inc = d.dy / (float)d.steps; // incremento em y
	d.x = l->start.x; // x inicial
	d.y = l->start.y; // y inicial
	d.i = 0; // counter
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
