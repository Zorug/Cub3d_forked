/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:43:00 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/07 21:06:08 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_ray_minimap(t_data *data, t_ray *ray)
{
	t_line	line;
	int		tile;

	tile = TILE_SIZE * MINIMAP_SCALE;
	line.start.x = (int)round(MINIMAP_OFFSET_X + data->posX * tile);
	line.start.y = (int)round(MINIMAP_OFFSET_Y + data->posY * tile);
	line.end.x = (int)round(MINIMAP_OFFSET_X + ray->hit_x * tile);
	line.end.y = (int)round(MINIMAP_OFFSET_Y + ray->hit_y * tile);
	line.color = MAP_RAY_COLOR;
	draw_line(&data->screen, &line);
}
