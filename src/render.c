/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:13:17 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/22 21:38:31 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_minimap(t_data *data)
{
	int		x;
	int		y;
	int		tile;
	t_rect	r;

	tile = TILE_SIZE * MINIMAP_SCALE;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1')
			{
				r.pos.x = x * tile + MINIMAP_OFFSET_X;
				r.pos.y = y * tile + MINIMAP_OFFSET_Y;
				r.width = tile;
				r.height = tile;
				r.color = COLOR_GRAY;
				draw_rect(&data->screen, &r);
			}
			x++;
		}
		y++;
	}
}

void	draw_player_minimap(t_data *data)
{
	t_circle	player;
	int			tile;

	tile = TILE_SIZE * MINIMAP_SCALE;
	player.center.x = MINIMAP_OFFSET_X + data->posX * tile;
	player.center.y = MINIMAP_OFFSET_Y + data->posY * tile;
	player.radius = tile / 4;
	player.color = COLOR_RED;
	draw_circle(&data->screen, &player);
}

void	render_3d_view(t_data *data)
{
	int		x;
	double	camera_x;
	double	ray_angle;
	t_ray	ray;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;

	x = 0;
	while (x < data->screen.width)
	{
		camera_x = 2.0 * x / (double)data->screen.width - 1.0;
		ray_angle = data->angle
			+ atan(camera_x * tan(data->fov / 2));

		cast_single_ray(data, ray_angle, &ray);

		line_height = (int)(data->screen.height / ray.perp_wall_dist);

		draw_start = -line_height / 2 + data->screen.height / 2;
		draw_end = line_height / 2 + data->screen.height / 2;

		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= data->screen.height)
			draw_end = data->screen.height - 1;

		y = draw_start;
		while (y <= draw_end)
		{
			my_mlx_pixel_put(&data->screen, x, y, COLOR_RED);
			y++;
		}
		x++;
	}
}

int	render(t_data *data)
{
	//double	left_angle;
	//double	right_angle;
	//int	left_x;
	//int	left_y;
	//int	right_x;
	//int	right_y;

	clear_screen(&data->screen);

	// 3D
	render_3d_view(data);

	//desenha o mapa
	//draw_map(data);
	draw_minimap(data);

	// Atualiza vetor principal
	//data->dirX = cos(data->angle);
	//data->dirY = sin(data->angle);

	// Desenha player
	draw_player_minimap(data);

	// first ray to cast
	//int i;
	//int rays = 60;
	//double startAngle = data->angle - data->fov / 2;
	//double angleStep = data->fov / rays;

	//for (i = 0; i < rays; i++)
	//{
	//	cast_single_ray(data, startAngle + i * angleStep);
	//}

	mlx_put_image_to_window(data->mlx, data->win,
		data->screen.img, 0, 0);

	return (0);
}
