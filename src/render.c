/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:13:17 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/26 17:01:19 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_minimap(t_data *data)
{
	int		x;
	int		y;
	int		tile;
	t_rect	r;

	tile = TILE_SIZE * MINIMAP_SCALE;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1')
			{
				r.pos.x = x * tile + MINIMAP_OFFSET_X;
				r.pos.y = y * tile + MINIMAP_OFFSET_Y;
				r.width = tile;
				r.height = tile;
				//r.color = COLOR_GRAY;
				r.color = MAP_WALL_COLOR;
				draw_rect(&data->screen, &r);
			}
			x++;
		}
		y++;
	}
}

void	draw_player_minimap(t_data *data)
{
	t_circle	player;
	int			tile;

	tile = TILE_SIZE * MINIMAP_SCALE;
	player.center.x = MINIMAP_OFFSET_X + data->posX * tile;
	player.center.y = MINIMAP_OFFSET_Y + data->posY * tile;
	player.radius = tile / 4;
	//player.color = COLOR_RED;
	player.color = MAP_PLAYER_COLOR;
	draw_circle(&data->screen, &player);
}

/*static int	get_wall_color(t_ray *ray)
{
	if (ray->side == 0)
		return (COLOR_RED);
	return (COLOR_GREEN);
	//return (COLOR_RED);
}*/

/*static int	get_wall_color(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (COLOR_WEST);
		else
			return (COLOR_EAST);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (COLOR_NORTH);
		else
			return (COLOR_SOUTH);
	}
}*/

/*static int	get_wall_color(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (COLOR_EAST);
		else
			return (COLOR_WEST);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (COLOR_SOUTH);
		else
			return (COLOR_NORTH);
	}
}*/

/*static int	get_wall_color(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (WALL_EAST_COLOR);
		else
			return (WALL_WEST_COLOR);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (WALL_SOUTH_COLOR);
		else
			return (WALL_NORTH_COLOR);
	}
}*/

static int	get_wall_color(t_ray *ray)
{
	if (ray->wall_side == WALL_NORTH)
		return (WALL_NORTH_COLOR);
	if (ray->wall_side == WALL_SOUTH)
		return (WALL_SOUTH_COLOR);
	if (ray->wall_side == WALL_WEST)
		return (WALL_WEST_COLOR);
	return (WALL_EAST_COLOR);
}

/*static int	apply_shadow(int color)
{
	return (color >> 1) & 0x007F7F7F;
}*/

void	init_ray_from_dir(t_data *data, t_ray *ray)
{
	ray->map_x = (int)data->posX;
	ray->map_y = (int)data->posY;
	ray->hit = 0;

	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);

	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

/*void	render_3d_view(t_data *data)
{
	int		x;
	double	camera_x;
	t_ray	ray;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;
	int		color;

	x = 0;
	while (x < data->screen.width)
	{
		camera_x = 2.0 * x / (double)data->screen.width - 1.0;

		ray.ray_dir_x = data->dirX + data->planeX * camera_x;
		ray.ray_dir_y = data->dirY + data->planeY * camera_x;

		cast_single_ray(data, &ray);

		if (ray.perp_wall_dist < 0.1)
			ray.perp_wall_dist = 0.1;

		line_height = (int)(data->screen.height / ray.perp_wall_dist);

		draw_start = -line_height / 2 + data->screen.height / 2;
		draw_end = line_height / 2 + data->screen.height / 2;

		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= data->screen.height)
			draw_end = data->screen.height - 1;

		color = get_wall_color(&ray);
		if (ray.side == 1)
			color = apply_shadow(color);

		y = draw_start;
		while (y <= draw_end)
		{
			my_mlx_pixel_put(&data->screen, x, y, color);
			y++;
		}
		x++;
	}
}*/

void	render_3d_view(t_data *data)
{
	int		x;
	double	camera_x;
	t_ray	ray;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;
	int		color;

	x = 0;
	while (x < data->screen.width)
	{
		/* 1️⃣ posição da câmera no plano [-1, 1] */
		camera_x = 2.0 * x / (double)data->screen.width - 1.0;

		/* 2️⃣ direção do raio (SEM fish-eye) */
		ray.ray_dir_x = data->dirX + data->planeX * camera_x;
		ray.ray_dir_y = data->dirY + data->planeY * camera_x;

		/* 3️⃣ cast do raio (DDA + distância perpendicular) */
		cast_single_ray(data, &ray);

		if (ray.perp_wall_dist < 0.1)
			ray.perp_wall_dist = 0.1;

		/* 4️⃣ altura da parede */
		line_height = (int)(data->screen.height / ray.perp_wall_dist);

		draw_start = -line_height / 2 + data->screen.height / 2;
		draw_end = line_height / 2 + data->screen.height / 2;

		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= data->screen.height)
			draw_end = data->screen.height - 1;

		/* 5️⃣ TETO */
		y = 0;
		while (y < draw_start)
		{
			my_mlx_pixel_put(&data->screen, x, y, CEILING_COLOR);
			y++;
		}

		/* 6️⃣ PAREDE */
		color = get_wall_color(&ray);
		if (ray.side == 1)
			color = (color >> 1) & 0x007F7F7F; // sombra simples

		y = draw_start;
		while (y <= draw_end)
		{
			my_mlx_pixel_put(&data->screen, x, y, color);
			y++;
		}

		/* 7️⃣ CHÃO */
		y = draw_end + 1;
		while (y < data->screen.height)
		{
			my_mlx_pixel_put(&data->screen, x, y, FLOOR_COLOR);
			y++;
		}

		x++;
	}
}

int	render(t_data *data)
{
	clear_screen(&data->screen);

	// 3D
	render_3d_view(data);

	//desenha o mapa
	draw_minimap(data);

	// Desenha player
	draw_player_minimap(data);

	mlx_put_image_to_window(data->mlx, data->win,
		data->screen.img, 0, 0);

	return (0);
}
