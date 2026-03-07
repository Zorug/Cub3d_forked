/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 21:33:15 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/07 14:22:48 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr
		+ (y * img->line_length)
		+ (x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// clear last frame, than we can redraw
void	clear_screen(t_img *img)
{
	ft_bzero(img->addr, img->line_length * img->height);
}

// direction of the player
void	set_player_direction(t_data *data, char c)
{
	if (c == 'N')
		data->angle = -M_PI / 2;
	else if (c == 'S')
		data->angle = M_PI / 2;
	else if (c == 'E')
		data->angle = 0;
	else if (c == 'W')
		data->angle = M_PI;

	data->dirX = cos(data->angle);
	data->dirY = sin(data->angle);
}

// Player start position
void	find_player(t_data *data)
{
	int	y;
	int	x;
	int	line_len;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		line_len = ft_strlen(data->map[y]);
		while (x < line_len)
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				data->posX = x + 0.5;
				data->posY = y + 0.5;
				set_player_direction(data, data->map[y][x]);
				data->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
