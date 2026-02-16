/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:31:40 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/16 22:46:16 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* just calculate the ray */
//void cast_single_ray(t_data *data)
void cast_single_ray(t_data *data, double rayAngle)
{
    //double rayDirX; // angulo do raio
    //double rayDirY;

	double rayDirX = cos(rayAngle);
    double rayDirY = sin(rayAngle);

    //rayDirX = cos(data->angle);
    //rayDirY = sin(data->angle);

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

	//printf("Ray at tile (%d, %d)\n", mapX, mapY);
	//Agora precisamos calcular:
		//a distância REAL do jogador até a parede,
		//sem distorção de fish-eye
	double perpWallDist;

	if (side == 0) // Se bateu numa parede vertical (X)
	{
		perpWallDist = (mapX - data->posX + (1 - stepX) / 2) / rayDirX;
	}
	else // Se bateu numa parede horizontal (Y)
	{
		perpWallDist = (mapY - data->posY + (1 - stepY) / 2) / rayDirY;
	}
/*
🔍 O que significa cada parte?

🔹 mapX - posX
➡️ Distância do jogador até o tile atingido

🔹 (1 - stepX) / 2
➡️ Ajuste fino:
stepX = 1 → entra pelo lado esquerdo
stepX = -1 → entra pelo lado direito
Isso posiciona o impacto na borda correta do tile

🔹 / rayDirX
➡️ Projeta a distância perpendicularmente
*/

	//printf("Perp distance: %f\n", perpWallDist);

// Agora você vai transformar distância em altura na tela.
// Converter: distância da parede (perpWallDist)
// em: altura vertical da parede em pixels
/*🧠 A ideia fundamental
Quanto mais perto a parede:
- ela parece mais alta
Quanto mais longe:
- ela parece mais baixa
Isso é perspectiva básica.*/
/*📌 Exemplo:
tela = 600 px
parede a 1.0 tile → 600 px
parede a 2.0 tiles → 300 px
parede a 3.0 tiles → 200 px

	int lineHeight;
	int drawStart;
	int drawEnd;

	lineHeight = (int)(data->screen.height / perpWallDist);

	drawStart = -lineHeight / 2 + data->screen.height / 2;
	drawEnd = lineHeight / 2 + data->screen.height / 2;

	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd >= data->screen.height)
		drawEnd = data->screen.height - 1;
*/

/*	double hitX;
	double hitY;

	if (side == 0)
	{
		hitX = mapX;
		hitY = data->posY + perpWallDist * rayDirY;
	}
	else
	{
		hitY = mapY;
		hitX = data->posX + perpWallDist * rayDirX;
	}*/

	double hitX;
	double hitY;

	if (side == 0) // parede vertical
	{
		hitX = mapX + (stepX == -1 ? 1.0 : 0.0);
		hitY = data->posY + perpWallDist * rayDirY;
	}
	else // parede horizontal
	{
		hitY = mapY + (stepY == -1 ? 1.0 : 0.0);
		hitX = data->posX + perpWallDist * rayDirX;
	}

	t_line ray;

	ray.start.x = data->posX * TILE_SIZE;
	ray.start.y = data->posY * TILE_SIZE;
	ray.end.x = hitX * TILE_SIZE;
	ray.end.y = hitY * TILE_SIZE;
	ray.color = COLOR_YELLOW;

	draw_line(&data->screen, &ray);


}
