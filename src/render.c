/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:13:17 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/20 22:21:58 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	render(t_data *data)
{
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
	t_circle	player;
	///////////////////
	player.center.x = data->posX * TILE_SIZE;
	player.center.y = data->posY * TILE_SIZE;
	player.radius = TILE_SIZE / 4;
	player.color = COLOR_RED;
	draw_circle(&data->screen, &player);

	// desenha linha
	t_line	dir;
	/////////////7
	dir.start.x = data->posX * TILE_SIZE;
	dir.start.y = data->posY * TILE_SIZE;
	dir.end.x = (data->posX + data->dirX) * TILE_SIZE;
	dir.end.y = (data->posY + data->dirY) * TILE_SIZE;
	dir.color = COLOR_GREEN;
	draw_line(&data->screen, &dir);

	// Limites do FOV
	left_angle = data->angle - data->fov / 2;
	right_angle = data->angle + data->fov / 2;

	dir.end.x = (data->posX + cos(right_angle)) * TILE_SIZE;
	dir.end.y = (data->posY + sin(right_angle)) * TILE_SIZE;
	dir.color = COLOR_BLUE;

	draw_line(&data->screen, &dir);

	dir.end.x = (data->posX + cos(left_angle)) * TILE_SIZE;
	dir.end.y = (data->posY + sin(left_angle)) * TILE_SIZE;
	draw_line(&data->screen, &dir);

	// first ray to cast
	int i;
	int rays = 60;
	double startAngle = data->angle - data->fov / 2;
	double angleStep = data->fov / rays;

	for (i = 0; i < rays; i++)
	{
		cast_single_ray(data, startAngle + i * angleStep);
	}

	mlx_put_image_to_window(data->mlx, data->win,
		data->screen.img, 0, 0);

	return (0);
}
