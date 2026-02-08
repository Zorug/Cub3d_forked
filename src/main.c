/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:42:29 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/08 18:26:06 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#define KEY_ESC 65307 //tecla esc

typedef struct	s_data {
	void	*img; // Ponteiro opaco da MLX para a imagem
	char	*addr; // Endereço real da memória dos pixels
	int		bits_per_pixel; // Quantos bits cada pixel ocupa (normalmente 32)
	int		line_length; // Quantos bytes existem em uma linha
	int		endian; // Ordem dos bytes (quase sempre 0 no Linux)
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr // começo da imagem na memória
		+ (y * data->line_length) // pula y linhas
		+ (x * (data->bits_per_pixel / 8)); //pula x pixels na linha
	*(unsigned int*)dst = color; // Escreve a cor diretamente na memória
}

// fechar clicando no x
int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

// Ao apertar esc sair
int	key_hook(int keycode, void *param)
{
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	main(void)
{
	void	*mlx; // conexão com o servidor gráfico
	void	*mlx_win; // janela
	t_data	img; // imagem (buffer de pixels)

	mlx = mlx_init(); // Conecta ao X11. Sem isso, nada funciona
	// Cria uma janela vazia
	mlx_win = mlx_new_window(mlx, 800, 600, "Hello world!");
	// Cria um buffer de pixels na memória. Ainda não sabemos onde ele está
	img.img = mlx_new_image(mlx, 800, 600);
	// img.addr aponta para a memória real
	// Você pode manipular pixel por pixel
	// Sem isso, não dá pra desenhar manualmente.
	img.addr = mlx_get_data_addr(img.img, 
		&img.bits_per_pixel, &img.line_length, &img.endian);
	// Desenha um pixel vermelho. Coordenada (10,10)
	my_mlx_pixel_put(&img, 10, 10, 0x00FF0000);
	//A imagem vira visível. Copia o buffer para a janela
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// fechar clicando no x
	mlx_hook(mlx_win, 17, 0, close_window, NULL);
	// ao apertar esc sai
	mlx_key_hook(mlx_win, key_hook, NULL);
	// Mantém a janela aberta. Escuta eventos. Sem isso, o programa fecha imediatamente
	mlx_loop(mlx);
}

/*
[ RAM ] ---> imagem (pixels)
   |
   |  mlx_put_image_to_window
   v
[ JANELA ]
*/