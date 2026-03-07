/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:34:20 by cgross-s          #+#    #+#             */
/*   Updated: 2026/03/07 21:54:32 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
📌 O que significa?
	- delta_dist_x = distância que o raio percorre para atravessar 1 tile 
	no eixo X
	- delta_dist_y = o mesmo, mas no eixo Y
📐 Matemática:
	- Se ray_dir_x é pequeno → o raio é quase vertical → demora muito 
	para cruzar uma linha vertical
	- Se ray_dir_x == 0 → nunca cruza → usamos um número gigante (1e30)
👉 Isto evita divisão por zero e mantém a lógica do DDA correta.
*/
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

/*
Step: Define para que lado o raio anda no mapa

O que é side_dist_x?
➡️ Distância do jogador até a primeira linha vertical que o raio vai cruzar.
	- Se o raio vai para a esquerda:
		- distância até a borda esquerda do tile
	- Se vai para a direita:
		- distância até a borda direita do tile
O mesmo vale para side_dist_y.
🧠 O DDA usa isto para decidir:
	“Cruzo primeiro uma linha vertical ou horizontal?”
*/
static void	init_step_x(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->pos_x)
			* ray->delta_dist_x;
	}
}

static void	init_step_y(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->pos_y)
			* ray->delta_dist_y;
	}
}

/*Responsável por preparar tudo antes do loop DDA.*/
/*Ela não lança o raio ainda, apenas configura tudo
o que o DDA precisa para funcionar corretamente.
Antes do raio começar a “andar” pelo mapa, precisamos dizer:
- em que direção ele anda
- quanto ele anda por tile
- qual será o primeiro limite que ele vai cruzar*/
/* ray->hit = 0; // ainda não bateu em parede */
void	init_dda(t_data *data, t_ray *ray)
{
	init_delta_dist(ray);
	init_step_x(data, ray);
	init_step_y(data, ray);
	ray->hit = 0;
}
