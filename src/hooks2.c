/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:10:00 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 21:54:32 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

/* Move player by checking collision */
void	move_player(t_data *data, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + move_x;
	new_y = data->pos_y + move_y;
	if (is_walkable(data, new_x, data->pos_y))
		data->pos_x = new_x;
	if (is_walkable(data, data->pos_x, new_y))
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
