/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 21:32:20 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/07 14:22:48 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	int	i;

	if (!data)
		exit(0);
	free_scene_config(&data->config);
	free_map(data);
	i = 0;
	while (i < 4)
	{
		if (data->tex[i].img)
			mlx_destroy_image(data->mlx, data->tex[i].img);
		i++;
	}
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
	else if (keycode == KEY_D)
		move_player(data,
			-data->dirY * data->move_speed,
			data->dirX * data->move_speed);
	else if (keycode == KEY_A)
		move_player(data,
			data->dirY * data->move_speed,
			-data->dirX * data->move_speed);
}

static void	rotate_view(t_data *data, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dirX;
	data->dirX = data->dirX * cos(rot) - data->dirY * sin(rot);
	data->dirY = old_dir_x * sin(rot) + data->dirY * cos(rot);

	old_plane_x = data->planeX;
	data->planeX = data->planeX * cos(rot) - data->planeY * sin(rot);
	data->planeY = old_plane_x * sin(rot) + data->planeY * cos(rot);
}

static void	handle_rotation(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		rotate_view(data, -data->rot_speed);
	else if (keycode == KEY_RIGHT)
		rotate_view(data, data->rot_speed);
}

static void	toggle_mouse(t_data *data)
{
	data->mouse_enabled = !data->mouse_enabled;
	if (data->mouse_enabled)
	{
		mlx_mouse_hide(data->mlx, data->win);
		mlx_mouse_move(data->mlx, data->win,
			data->win_center_x,
			data->win_center_y);
	}
	else
		mlx_mouse_show(data->mlx, data->win);
}

int	key_hook(int keycode, t_data *data)
{
	handle_movement(keycode, data);
	handle_rotation(keycode, data);
	if (keycode == KEY_ESC)
		close_window(data);
	if (keycode == KEY_M)
		toggle_mouse(data);
	if (keycode == KEY_R)
		data->show_rays = !data->show_rays;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	int	delta_x;

	(void)y;
	if (!data->mouse_enabled)
		return (0);

	delta_x = x - data->win_center_x;
	rotate_view(data, delta_x * data->mouse_sensitivity);

	mlx_mouse_move(data->mlx, data->win,
		data->win_center_x,
		data->win_center_y);

	return (0);
}
