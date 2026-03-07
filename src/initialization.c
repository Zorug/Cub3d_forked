/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 16:35:11 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/07 21:54:32 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Initialize MLX and window */
int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->screen.width = 800;
	data->screen.height = 600;
	data->win = mlx_new_window(data->mlx, data->screen.width,
			data->screen.height, "CUB3D");
	if (!data->win)
		return (0);
	return (1);
}

/* Initialize image (framebuffer) */
int	init_screen(t_data *data)
{
	data->screen.img = mlx_new_image(data->mlx,
			data->screen.width, data->screen.height);
	if (!data->screen.img)
		return (0);
	data->screen.addr = mlx_get_data_addr(data->screen.img,
			&data->screen.bits_per_pixel,
			&data->screen.line_length, &data->screen.endian);
	if (!data->screen.addr)
		return (0);
	return (1);
}

/* Allocate ray cache for minimap rendering */
int	init_rays_cache(t_data *data)
{
	data->rays = (t_ray *)ft_calloc(data->screen.width, sizeof(t_ray));
	if (!data->rays)
		return (0);
	data->rays_count = data->screen.width;
	return (1);
}

/* Initialize player and game parameters */
void	init_player(t_data *data)
{
	find_player(data);
	data->dir_x = cos(data->angle);
	data->dir_y = sin(data->angle);
	data->fov = M_PI / 3;
	data->move_speed = 0.5;
	data->rot_speed = 0.4;
	data->plane_x = -data->dir_y * tan(data->fov / 2);
	data->plane_y = data->dir_x * tan(data->fov / 2);
}

/* Initialize mouse */
void	init_mouse(t_data *data)
{
	data->mouse_enabled = 0;
	data->mouse_sensitivity = 0.002;
	data->win_center_x = data->screen.width / 2;
	data->win_center_y = data->screen.height / 2;
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
}
