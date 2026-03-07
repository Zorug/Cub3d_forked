/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   draw_minimap.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cgross-s <cgross-s@student.42porto.com>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/02/26 14:43:00 by cgross-s		  #+#	#+#			 */
/*   Updated: 2026/02/26 16:02:12 by cgross-s		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_ray_minimap(t_data *data, t_ray *ray)
{
	t_line	line;
	int		tile;

	tile = TILE_SIZE * MINIMAP_SCALE;
	line.start.x = MINIMAP_OFFSET_X + data->posX * tile;
	line.start.y = MINIMAP_OFFSET_Y + data->posY * tile;
	line.end.x = MINIMAP_OFFSET_X + ray->hit_x * tile;
	line.end.y = MINIMAP_OFFSET_Y + ray->hit_y * tile;
	//line.color = COLOR_YELLOW;
	line.color = MAP_RAY_COLOR;
	draw_line(&data->screen, &line);
}

/* Verify if option show_rays is selected, R button,
 than show */
void	draw_ray_debug(t_data *data, t_ray *ray)
{
	if (!data->show_rays)
		return ;
	draw_ray_minimap(data, ray);
}
