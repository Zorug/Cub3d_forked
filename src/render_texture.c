/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:30:00 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 21:04:31 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Get a pixel from texture at given coordinates */
int	get_texture_pixel(t_img *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

/* Calculate texture X coordinate based on wall hit point */
int	get_texture_x(t_ray *ray, int tex_width)
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

/* Get wall pixel color from texture */
int	get_wall_color(t_data *data, t_ray *ray, int y, t_wall_render *wr)
{
	t_img	*tex;
	int		tex_x;
	int		tex_y;
	int		d;

	tex = &data->tex[ray->wall_side];
	tex_x = get_texture_x(ray, tex->width);
	d = y - wr->wall_start;
	tex_y = d * tex->height / wr->line_height;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	return (get_texture_pixel(tex, tex_x, tex_y));
}
