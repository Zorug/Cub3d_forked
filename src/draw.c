/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:46:13 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/07 21:00:43 by tnuno-mo         ###   ########.fr       */
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

// Draw a line using DDA algorithm https://www.youtube.com/watch?v=Oyp3eq580jA
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
