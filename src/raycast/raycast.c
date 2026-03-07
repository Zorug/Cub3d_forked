/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:31:40 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/07 21:54:32 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Check if ray hit map boundaries or wall */
static int	check_hit(t_data *data, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= data->map_height)
		return (1);
	if (ray->map_x >= (int)ft_strlen(data->map[ray->map_y]))
		return (1);
	if (data->map[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

/* DDA algorithm implementation */
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
		if (check_hit(data, ray))
		{
			ray->hit = 1;
			break ;
		}
	}
}

/* Fix fish-eye effect by computing perpendicular distance */
void	compute_perp_distance(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->pos_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->pos_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

/* Calculate exact wall hit position in world coordinates */
void	compute_hit_position(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->hit_x = ray->map_x + (ray->step_x == -1);
		ray->hit_y = data->pos_y
			+ ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		ray->hit_y = ray->map_y + (ray->step_y == -1);
		ray->hit_x = data->pos_x
			+ ray->perp_wall_dist * ray->ray_dir_x;
	}
}

/* Cast a single ray and compute all its properties */
void	cast_single_ray(t_data *data, t_ray *ray)
{
	init_ray_from_dir(data, ray);
	init_dda(data, ray);
	perform_dda(data, ray);
	compute_perp_distance(data, ray);
	determine_wall_side(ray);
	compute_hit_position(data, ray);
}
