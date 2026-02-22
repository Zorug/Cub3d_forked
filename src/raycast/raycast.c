/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:31:40 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/22 12:11:34 by cgross-s         ###   ########.fr       */
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

// -----------------------------------------------------------------
/*Responsável por preparar tudo antes do loop DDA.*/
/*Ela não lança o raio ainda, apenas configura tudo
o que o DDA precisa para funcionar corretamente.
Antes do raio começar a “andar” pelo mapa, precisamos dizer:
- em que direção ele anda
- quanto ele anda por tile
- qual será o primeiro limite que ele vai cruzar*/
static void	init_delta_dist(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	init_step_x(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->posX - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->posX)
			* ray->delta_dist_x;
	}
}

static void	init_step_y(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->posY - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->posY)
			* ray->delta_dist_y;
	}
}

void	init_dda(t_data *data, t_ray *ray)
{
	init_delta_dist(ray);
	init_step_x(data, ray);
	init_step_y(data, ray);
	ray->hit = 0;
}

//---------------------------------------------------------------

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
