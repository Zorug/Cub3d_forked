/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 21:33:15 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/17 23:16:07 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr
		+ (y * img->line_length)
		+ (x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/* clear last frame, than we can redraw */
void	clear_screen(t_img *img)
{
	ft_bzero(img->addr, img->line_length * img->height);
}
