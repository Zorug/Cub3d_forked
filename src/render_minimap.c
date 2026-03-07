/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:30:00 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 21:04:31 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Draw walls on minimap */
static void	draw_wall_tile(t_data *data, int x, int y, int tile)
{
	t_rect	r;

	r.pos.x = x * tile + MINIMAP_OFFSET_X;
	r.pos.y = y * tile + MINIMAP_OFFSET_Y;
	r.width = tile;
	r.height = tile;
	r.color = MAP_WALL_COLOR;
	draw_rect(&data->screen, &r);
}

/* Draw minimap in the top-left corner of the screen */
void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	tile;
	int	line_len;

	tile = TILE_SIZE * MINIMAP_SCALE;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		line_len = ft_strlen(data->map[y]);
		while (x < line_len)
		{
			if (data->map[y][x] == '1')
				draw_wall_tile(data, x, y, tile);
			x++;
		}
		y++;
	}
}

/* Draw player position as a circle on the minimap */
void	draw_player_minimap(t_data *data)
{
	t_circle	player;
	int			tile;

	tile = TILE_SIZE * MINIMAP_SCALE;
	player.center.x = MINIMAP_OFFSET_X + data->posX * tile;
	player.center.y = MINIMAP_OFFSET_Y + data->posY * tile;
	player.radius = tile / 4;
	player.color = MAP_PLAYER_COLOR;
	draw_circle(&data->screen, &player);
}

/* Draw rays on minimap if enabled */
void	draw_minimap_rays(t_data *data)
{
	int	x;

	if (!data->show_rays)
		return ;
	x = 0;
	while (x < data->screen.width)
	{
		draw_ray_minimap(data, &data->rays[x]);
		x++;
	}
}
