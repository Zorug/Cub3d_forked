/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:31:40 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/22 12:40:00 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*set initial directions and position in the map (in map pos [0, 1])*/
void	init_ray_direction(t_data *data, t_ray *ray, double ray_angle)
{
	ray->ray_dir_x = cos(ray_angle);
	ray->ray_dir_y = sin(ray_angle);
	ray->map_x = (int)data->posX;
	ray->map_y = (int)data->posY;
}

/*Aqui acontece o algoritmo DDA em si.*/
void	perform_dda(t_data *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= data->map_width
			|| ray->map_y < 0 || ray->map_y >= data->map_height)
			break ;
		if (data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

/*Responsável por corrigir o fish-eye.*/
void	compute_perp_distance(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->posX
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->posY
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

/*Aqui calculamos onde exatamente o raio bateu, em coordenadas do mundo.*/
void	compute_hit_position(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->hit_x = ray->map_x + (ray->step_x == -1);
		ray->hit_y = data->posY
			+ ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		ray->hit_y = ray->map_y + (ray->step_y == -1);
		ray->hit_x = data->posX
			+ ray->perp_wall_dist * ray->ray_dir_x;
	}
}

/*Somente visualização no minimapa.*/
void	draw_ray_debug(t_data *data, t_ray *ray)
{
	t_line	line;

	line.start.x = data->posX * TILE_SIZE;
	line.start.y = data->posY * TILE_SIZE;
	line.end.x = ray->hit_x * TILE_SIZE;
	line.end.y = ray->hit_y * TILE_SIZE;
	line.color = COLOR_YELLOW;
	draw_line(&data->screen, &line);
}

void	cast_single_ray(t_data *data, double ray_angle)
{
	t_ray	ray;

	init_ray_direction(data, &ray, ray_angle);
	init_dda(data, &ray);
	perform_dda(data, &ray);
	compute_perp_distance(data, &ray);
	compute_hit_position(data, &ray);
	draw_ray_debug(data, &ray);
}
