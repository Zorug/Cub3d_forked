/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 16:35:11 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/22 16:37:21 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Inicialização da MLX e janela */
void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	//if (!data->mlx)
	//	exit_error("mlx_init failed");

	data->screen.width = 800;
	data->screen.height = 600;

	data->win = mlx_new_window(
		data->mlx,
		data->screen.width,
		data->screen.height,
		"CUB3D"
	);
	//if (!data->win)
	//	exit_error("mlx_new_window failed");
}

/* Inicialização da imagem (framebuffer) */
void	init_screen(t_data *data)
{
	data->screen.img = mlx_new_image(
		data->mlx,
		data->screen.width,
		data->screen.height
	);
	//if (!data->screen.img)
	//	exit_error("mlx_new_image failed");

	data->screen.addr = mlx_get_data_addr(
		data->screen.img,
		&data->screen.bits_per_pixel,
		&data->screen.line_length,
		&data->screen.endian
	);
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
}
