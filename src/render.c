/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:13:17 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/07 21:04:31 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Initialize ray direction and delta distances for DDA algorithm */
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

/* Render single column of 3D view */
static void	render_column(t_data *data, int x)
{
	double			camera_x;
	t_ray			*ray;
	t_wall_render	wr;

	ray = &data->rays[x];
	camera_x = (2.0 * x + 1.0) / (double)data->screen.width - 1.0;
	ray->ray_dir_x = data->dirX + data->planeX * camera_x;
	ray->ray_dir_y = data->dirY + data->planeY * camera_x;
	cast_single_ray(data, ray);
	init_wall_render(&wr, ray, data);
	draw_ceiling(data, x, &wr);
	draw_wall(data, x, ray, &wr);
	draw_floor(data, x, &wr);
}

/* Render 3D view with textured walls, ceiling and floor */
void	render_3d_view(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->screen.width)
	{
		render_column(data, x);
		x++;
	}
}

/* Main render loop: clear screen, draw 3D view, minimap and player */
int	render(t_data *data)
{
	clear_screen(&data->screen);
	render_3d_view(data);
	draw_minimap(data);
	draw_minimap_rays(data);
	draw_player_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win,
		data->screen.img, 0, 0);
	return (0);
}
