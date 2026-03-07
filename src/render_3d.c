/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:35:00 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 21:04:31 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Initialize wall render parameters */
void	init_wall_render(t_wall_render *wr, t_ray *ray, t_data *data)
{
	if (ray->perp_wall_dist < 0.01)
		ray->perp_wall_dist = 0.01;
	wr->line_height = (int)(data->screen.height / ray->perp_wall_dist);
	if (wr->line_height > data->screen.height * 10)
		wr->line_height = data->screen.height * 10;
	wr->wall_start = -wr->line_height / 2 + data->screen.height / 2;
	wr->draw_start = wr->wall_start;
	wr->draw_end = wr->line_height / 2 + data->screen.height / 2;
	if (wr->draw_start < 0)
		wr->draw_start = 0;
	if (wr->draw_end >= data->screen.height)
		wr->draw_end = data->screen.height - 1;
}

/* Draw ceiling for column */
void	draw_ceiling(t_data *data, int x, t_wall_render *wr)
{
	int	y;

	y = 0;
	while (y < wr->draw_start)
	{
		my_mlx_pixel_put(&data->screen, x, y, data->config.ceiling_color);
		y++;
	}
}

/* Draw wall for column */
void	draw_wall(t_data *data, int x, t_ray *ray, t_wall_render *wr)
{
	int	y;
	int	color;

	y = wr->draw_start;
	while (y <= wr->draw_end)
	{
		color = get_wall_color(data, ray, y, wr);
		if (ray->side == 1)
			color = (color >> 1) & 0x007F7F7F;
		my_mlx_pixel_put(&data->screen, x, y, color);
		y++;
	}
}

/* Draw floor for column */
void	draw_floor(t_data *data, int x, t_wall_render *wr)
{
	int	y;

	y = wr->draw_end + 1;
	while (y < data->screen.height)
	{
		my_mlx_pixel_put(&data->screen, x, y, data->config.floor_color);
		y++;
	}
}
