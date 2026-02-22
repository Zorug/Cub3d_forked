/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 21:32:20 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/22 13:38:33 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*clear map leaks*/
void	free_map(t_data *data)
{
	int	i;

	if (!data->map)
		return ;
	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
}


/* close and clear leaks */
int	close_window(t_data *data)
{
	free_map(data);
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
		return (false);
	if (x >= data->map_width || y >= data->map_height)
		return (false);
	if (data->map[(int)y][(int)x] == '1')
		return (false);
	return (true);
}

static void	move_player(t_data *data, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = data->posX + move_x;
	new_y = data->posY + move_y;
	if (is_walkable(data, new_x, data->posY))
		data->posX = new_x;
	if (is_walkable(data, data->posX, new_y))
		data->posY = new_y;
}

static void	handle_movement(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		move_player(data,
			data->dirX * data->move_speed,
			data->dirY * data->move_speed);
	else if (keycode == KEY_S)
		move_player(data,
			-data->dirX * data->move_speed,
			-data->dirY * data->move_speed);
	else if (keycode == KEY_A)
		move_player(data,
			data->dirY * data->move_speed,
			-data->dirX * data->move_speed);
	else if (keycode == KEY_D)
		move_player(data,
			-data->dirY * data->move_speed,
			data->dirX * data->move_speed);
}

static void	handle_rotation(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		data->angle -= data->rot_speed;
	else if (keycode == KEY_RIGHT)
		data->angle += data->rot_speed;
}

int	key_hook(int keycode, t_data *data)
{
	handle_movement(keycode, data);
	handle_rotation(keycode, data);
	if (keycode == KEY_ESC)
		close_window(data);
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	int	delta_x;

	(void)y;

	if (!data->mouse_init)
	{
		data->mouse_x = x;
		data->mouse_init = 1;
		return (0);
	}

	delta_x = x - data->mouse_x;
	data->mouse_x = x;

	data->angle += delta_x * data->mouse_sensitivity;

	// Mantém o ângulo sempre entre 0 e 2π
	if (data->angle < 0)
		data->angle += 2 * M_PI;
	if (data->angle > 2 * M_PI)
		data->angle -= 2 * M_PI;

	return (0);
}
