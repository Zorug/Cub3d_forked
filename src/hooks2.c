/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:10:00 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 22:12:23 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define COLLISION_BUFFER 0.15

/* Verify if the tile is walkable (not a wall) */
int	is_walkable(t_data *data, double x, double y)
{
	int	map_y;
	int	line_len;

	if (x < 0 || y < 0)
		return (false);
	map_y = (int)y;
	if (map_y >= data->map_height)
		return (false);
	line_len = ft_strlen(data->map[map_y]);
	if (x >= line_len)
		return (false);
	if (data->map[map_y][(int)x] == '1')
		return (false);
	return (true);
}

/* Check collision with buffer zone around player */
static int	check_collision_buffer(t_data *data, double x, double y)
{
	if (!is_walkable(data, x, y))
		return (0);
	if (!is_walkable(data, x + COLLISION_BUFFER, y))
		return (0);
	if (!is_walkable(data, x - COLLISION_BUFFER, y))
		return (0);
	if (!is_walkable(data, x, y + COLLISION_BUFFER))
		return (0);
	if (!is_walkable(data, x, y - COLLISION_BUFFER))
		return (0);
	return (1);
}

/* Move player by checking collision */
void	move_player(t_data *data, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + move_x;
	new_y = data->pos_y + move_y;
	if (check_collision_buffer(data, new_x, data->pos_y))
		data->pos_x = new_x;
	if (check_collision_buffer(data, data->pos_x, new_y))
		data->pos_y = new_y;
}

/* Handle WASD movement */
void	handle_movement(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		move_player(data,
			data->dir_x * data->move_speed,
			data->dir_y * data->move_speed);
	else if (keycode == KEY_S)
		move_player(data,
			-data->dir_x * data->move_speed,
			-data->dir_y * data->move_speed);
	else if (keycode == KEY_D)
		move_player(data,
			-data->dir_y * data->move_speed,
			data->dir_x * data->move_speed);
	else if (keycode == KEY_A)
		move_player(data,
			data->dir_y * data->move_speed,
			-data->dir_x * data->move_speed);
}
