/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 21:32:20 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/15 17:42:16 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* close and clear leaks */
int	close_window(t_data *data)
{
	if (!data)
		exit(0);

	if (data->screen.img)
		mlx_destroy_image(data->mlx, data->screen.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
	return (0);
}

/* verify if the tile is a wall */
static int	is_walkable(t_data *data, double x, double y)
{
	if (x < 0 || y < 0)
		//return (0);
		return (false);
	if (x >= data->map_width || y >= data->map_height)
		//return (0);
		return (false);
	if (data->map[(int)y][(int)x] == '1')
		//return (0);
		return (false);
	//return (1);
	return (true);
}

/* Verify if a key was pressed */
int	key_hook(int keycode, t_data *data)
{
	double	newX;
	double	newY;

	if (keycode == KEY_W)
	{
		newX = data->posX + data->dirX * data->move_speed;
		newY = data->posY + data->dirY * data->move_speed;

		if (is_walkable(data, newX, data->posY))
			data->posX = newX;
		if (is_walkable(data, data->posX, newY))
			data->posY = newY;
	}

	if (keycode == KEY_S)
	{
		newX = data->posX - data->dirX * data->move_speed;
		newY = data->posY - data->dirY * data->move_speed;

		if (is_walkable(data, newX, data->posY))
			data->posX = newX;
		if (is_walkable(data, data->posX, newY))
			data->posY = newY;
	}

	if (keycode == KEY_A) // strafe esquerda
	{
		newX = data->posX + data->dirY * data->move_speed;
		newY = data->posY - data->dirX * data->move_speed;

		if (is_walkable(data, newX, data->posY))
			data->posX = newX;
		if (is_walkable(data, data->posX, newY))
			data->posY = newY;
	}

	if (keycode == KEY_D) // strafe direita
	{
		newX = data->posX - data->dirY * data->move_speed;
		newY = data->posY + data->dirX * data->move_speed;

		if (is_walkable(data, newX, data->posY))
			data->posX = newX;
		if (is_walkable(data, data->posX, newY))
			data->posY = newY;
	}

	if (keycode == KEY_LEFT)
		data->angle -= data->rot_speed;
	if (keycode == KEY_RIGHT)
		data->angle += data->rot_speed;
	if (keycode == KEY_ESC)
		close_window(data);

	return (0);
}
