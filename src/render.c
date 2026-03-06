/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:13:17 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/06 01:52:57 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Draw minimap in the top-left corner of the screen
void	draw_minimap(t_data *data)
{
	int		x;
	int		y;
	int		tile;
	int		line_len;
	t_rect	r;

	tile = TILE_SIZE * MINIMAP_SCALE;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		line_len = ft_strlen(data->map[y]);
		while (x < line_len)
		{
			if (data->map[y][x] == '1')
			{
			r.pos.x = x * tile + MINIMAP_OFFSET_X;
			r.pos.y = y * tile + MINIMAP_OFFSET_Y;
			r.width = tile;
			r.height = tile;
			r.color = MAP_WALL_COLOR;
			draw_rect(&data->screen, &r);
			}
			x++;
		}
		y++;
	}
}

// Draw player position as a circle on the minimap
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

// Get a pixel from texture at given coordinates
static int	get_texture_pixel(t_img *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

// Calculate texture X coordinate based on wall hit point
static int	get_texture_x(t_ray *ray, int tex_width)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = ray->hit_y;
	else
		wall_x = ray->hit_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex_width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = tex_width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

// Get wall pixel color from texture
static int	render_wall_pixel(t_data *data, t_ray *ray, int y, int line_height, int draw_start)
{
	t_img	*tex;
	int		tex_x;
	int		tex_y;
	int		d;

	tex = &data->tex[ray->wall_side];
	tex_x = get_texture_x(ray, tex->width);
	d = y - draw_start;
	tex_y = d * tex->height / line_height;
	return (get_texture_pixel(tex, tex_x, tex_y));
}

/*static int	apply_shadow(int color)
{
	return (color >> 1) & 0x007F7F7F;
}*/

// Initialize ray direction and delta distances for DDA algorithm
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

// Render 3D view with textured walls, ceiling and floor
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
		y = 0;
		while (y < draw_start)
		{
			my_mlx_pixel_put(&data->screen, x, y, data->config.ceiling_color);
			y++;
		}
		y = draw_start;
		while (y <= draw_end)
		{
			color = render_wall_pixel(data, &ray, y, line_height, draw_start);
			if (ray.side == 1)
				color = (color >> 1) & 0x007F7F7F;
			my_mlx_pixel_put(&data->screen, x, y, color);
			y++;
		}
		y = draw_end + 1;
		while (y < data->screen.height)
		{
			my_mlx_pixel_put(&data->screen, x, y, data->config.floor_color);
			y++;
		}
		x++;
	}
}

// Main render loop: clear screen, draw 3D view, minimap and player
int	render(t_data *data)
{
	clear_screen(&data->screen);
	render_3d_view(data);
	draw_minimap(data);
	draw_player_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win,
		data->screen.img, 0, 0);
	return (0);
}
