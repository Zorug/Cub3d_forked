/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 21:32:20 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/07 20:59:36 by tnuno-mo         ###   ########.fr       */
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

/* Free textures and screen image */
static void	cleanup_graphics(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->tex[i].img)
			mlx_destroy_image(data->mlx, data->tex[i].img);
		i++;
	}
	if (data->screen.img)
		mlx_destroy_image(data->mlx, data->screen.img);
	if (data->rays)
		free(data->rays);
}

/* Close and clear leaks */
int	cleanup_and_exit(t_data *data, int exit_code)
{
	if (!data)
		exit(exit_code);
	free_scene_config(&data->config);
	free_map(data);
	cleanup_graphics(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(exit_code);
	return (0);
}

int	close_window(t_data *data)
{
	return (cleanup_and_exit(data, 0));
}

int	key_hook(int keycode, t_data *data)
{
	handle_movement(keycode, data);
	handle_rotation(keycode, data);
	if (keycode == KEY_ESC)
		close_window(data);
	if (keycode == KEY_M)
	{
		data->mouse_enabled = !data->mouse_enabled;
		if (data->mouse_enabled)
		{
			mlx_mouse_hide(data->mlx, data->win);
			mlx_mouse_move(data->mlx, data->win,
				data->win_center_x, data->win_center_y);
		}
		else
			mlx_mouse_show(data->mlx, data->win);
	}
	if (keycode == KEY_R)
		data->show_rays = !data->show_rays;
	return (0);
}
