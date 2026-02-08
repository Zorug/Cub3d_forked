/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:42:29 by cgross-s          #+#    #+#             */
/*   Updated: 2026/02/08 18:54:37 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#define KEY_ESC 65307 //tecla esc

/*
typedef struct	s_data {
	void	*img; // Ponteiro opaco da MLX para a imagem
	char	*addr; // Endereço real da memória dos pixels
	int		bits_per_pixel; // Quantos bits cada pixel ocupa (normalmente 32)
	int		line_length; // Quantos bytes existem em uma linha
	int		endian; // Ordem dos bytes (quase sempre 0 no Linux)
}				t_data;*/

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_data;


/*void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr // começo da imagem na memória
		+ (y * data->line_length) // pula y linhas
		+ (x * (data->bits_per_pixel / 8)); //pula x pixels na linha
	*(unsigned int*)dst = color; // Escreve a cor diretamente na memória
}*/

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr
		+ (y * img->line_length)
		+ (x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


/*
//liberar as memórias do minilibx
int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}*/


// fechar clicando no x
/*int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}*/

int	close_window(t_data *data)
{
	if (!data)
		exit(0);

	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
	return (0);
}

// Ao apertar esc sair
/*
int	key_hook(int keycode, void *param)
{
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}*/

int	key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	return (0);
}

int	main(void)
{
	//void	*mlx; // conexão com o servidor gráfico
	//void	*mlx_win; // janela
	//t_data	img; // imagem (buffer de pixels)
	t_data	data;

	data.mlx = mlx_init(); // Conecta ao X11. Sem isso, nada funciona
	// Cria uma janela vazia
	data.win = mlx_new_window(data.mlx, 800, 600, "Hello world!");
	// Cria um buffer de pixels na memória. Ainda não sabemos onde ele está
	data.img.img = mlx_new_image(data.mlx, 800, 600);
	// img.addr aponta para a memória real
	// Você pode manipular pixel por pixel
	// Sem isso, não dá pra desenhar manualmente.
	data.img.addr = mlx_get_data_addr(data.img.img, 
		&data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	// Desenha um pixel vermelho. Coordenada (10,10)
	my_mlx_pixel_put(&data.img, 10, 10, 0x00FF0000);
	//A imagem vira visível. Copia o buffer para a janela
	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
	// ao apertar esc sai
	mlx_key_hook(data.win, key_hook, &data);
	// fechar clicando no x
	mlx_hook(data.win, 17, 0, close_window, &data);
	// Mantém a janela aberta. Escuta eventos. Sem isso, o programa fecha imediatamente
	mlx_loop(data.mlx);
}

/*
[ RAM ] ---> imagem (pixels)
   |
   |  mlx_put_image_to_window
   v
[ JANELA ]
*/