/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:31:40 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/15 22:21:04 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* just calculate the ray */
void cast_single_ray(t_data *data)
{
    double rayDirX; // angulo do raio
    double rayDirY;

    rayDirX = cos(data->angle);
    rayDirY = sin(data->angle);

	//posição no mapa em tile sizes
	int mapX = (int)data->posX;
    int mapY = (int)data->posY;

    // daqui para baixo: DDA
	//printf("rayDir: %f %f\n", rayDirX, rayDirY);
	//printf("map tile: (%d, %d)\n", mapX, mapY);

	// quanto o raio precisa andar para atravessar 1 tile no eixo X ou Y
	double deltaDistX;
	double deltaDistY;
	if (rayDirX == 0)
		deltaDistX = 1e30;
	else
		deltaDistX = fabs(1 / rayDirX);
	if (rayDirY == 0)
		deltaDistY = 1e30;
	else
		deltaDistY = fabs(1 / rayDirY);

	// Quando o raio anda no mapa, ele anda para qual lado?
	int stepX;
	int stepY;

	if (rayDirX < 0)
		stepX = -1;
	else
		stepX = 1;

	if (rayDirY < 0)
		stepY = -1;
	else
		stepY = 1;

// Qual é a distância do jogador até a primeira borda do tile em X e Y?
	double sideDistX;
	double sideDistY;

	if (rayDirX < 0)
		sideDistX = (data->posX - mapX) * deltaDistX;
	else
		sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;

	if (rayDirY < 0)
		sideDistY = (data->posY - mapY) * deltaDistY;
	else
		sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;

	// Loop DDA:
	//	comparar sideDistX vs sideDistY
	//	avançar no mapa
	//	detectar parede
	int hit = 0;      // bateu na parede?
	int side;         // 0 = X, 1 = Y

	while (hit == 0)
	{
		if (sideDistX < sideDistY) // Decide qual linha o raio cruza primeiro
		{
			sideDistX += deltaDistX; // Prepara a próxima borda
			mapX += stepX; // Anda exatamente 1 tile
			side = 0; // parede vertical (E/W)
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1; // parede horizontal (N/S)
		}

		if (data->map[mapY][mapX] == '1') // Aqui o raio bateu, fim do loop
			hit = 1;
	}

	printf("Ray at tile (%d, %d)\n", mapX, mapY);

}
