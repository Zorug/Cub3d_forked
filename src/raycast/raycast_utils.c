/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:50:00 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 21:08:55 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* Determine which wall side was hit */
void	determine_wall_side(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			ray->wall_side = WALL_EAST;
		else
			ray->wall_side = WALL_WEST;
	}
	else
	{
		if (ray->step_y > 0)
			ray->wall_side = WALL_SOUTH;
		else
			ray->wall_side = WALL_NORTH;
	}
}
