/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 16:35:11 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/06 01:15:12 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Inicialização da MLX e janela */
int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);

	data->screen.width = 800;
	data->screen.height = 600;

	data->win = mlx_new_window(
		data->mlx,
		data->screen.width,
		data->screen.height,
		"CUB3D"
	);
	if (!data->win)
		return (0);
	return (1);
}

/* Inicialização da imagem (framebuffer) */
int	init_screen(t_data *data)
{
	data->screen.img = mlx_new_image(
		data->mlx,
		data->screen.width,
		data->screen.height
	);
	if (!data->screen.img)
		return (0);

	data->screen.addr = mlx_get_data_addr(
		data->screen.img,
		&data->screen.bits_per_pixel,
		&data->screen.line_length,
		&data->screen.endian
	);
	if (!data->screen.addr)
		return (0);
	return (1);
}

/* Inicialização do jogador e parâmetros do jogo */
void	init_player(t_data *data)
{
	find_player(data);

	data->dirX = cos(data->angle);
	data->dirY = sin(data->angle);

	data->fov = M_PI / 3;
	data->move_speed = 0.5;
	data->rot_speed = 0.4;

	data->planeX = -data->dirY * tan(data->fov / 2);
	data->planeY =  data->dirX * tan(data->fov / 2);
}

/* Inicialização do mouse */
void	init_mouse(t_data *data)
{
	data->mouse_enabled = 0;
	data->mouse_sensitivity = 0.002;
	data->win_center_x = data->screen.width / 2;
	data->win_center_y = data->screen.height / 2;

	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
}

/* Hooks gerais (teclado, fechar, loop) */
void	init_hooks(t_data *data)
{
	mlx_key_hook(data->win, key_hook, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, render, data);

	// raios visiveis
	data->show_rays = 1;
}
