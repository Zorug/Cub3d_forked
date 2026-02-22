/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:34:20 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/22 12:34:57 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
