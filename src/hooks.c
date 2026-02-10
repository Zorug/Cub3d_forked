/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 21:32:20 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/10 21:30:10 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//close and clear leaks
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

int	key_hook(int keycode, t_data *data)
{
	double	speed;

	speed = 5.0;

	if (keycode == KEY_W)
	{
		data->posX += data->dirX * speed;
		data->posY += data->dirY * speed;
	}
	if (keycode == KEY_S)
	{
		data->posX -= data->dirX * speed;
		data->posY -= data->dirY * speed;
	}
	if (keycode == KEY_A)
	{
		data->posX += data->dirY * speed;
		data->posY -= data->dirX * speed;
	}
	if (keycode == KEY_D)
	{
		data->posX -= data->dirY * speed;
		data->posY += data->dirX * speed;
	}
	if (keycode == KEY_LEFT)
		data->angle -= 0.1;
	if (keycode == KEY_RIGHT)
		data->angle += 0.1;
	if (keycode == KEY_ESC)
		close_window(data);

	return (0);
}
