/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:20:00 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 21:54:32 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Rotate camera view */
void	rotate_view(t_data *data, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(rot) - data->dir_y * sin(rot);
	data->dir_y = old_dir_x * sin(rot) + data->dir_y * cos(rot);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(rot) - data->plane_y * sin(rot);
	data->plane_y = old_plane_x * sin(rot) + data->plane_y * cos(rot);
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
