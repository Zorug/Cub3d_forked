/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:20:00 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 20:59:36 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Rotate camera view */
void	rotate_view(t_data *data, double rot)
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

/* Handle arrow key rotation */
void	handle_rotation(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		rotate_view(data, -data->rot_speed);
	else if (keycode == KEY_RIGHT)
		rotate_view(data, data->rot_speed);
}

/* Handle mouse movement for camera rotation */
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
