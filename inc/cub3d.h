#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>	// true and false

# define TILE_SIZE 40 // size of a square

/* --- Key Definitions (Linux) --- */
typedef enum e_key
{
	KEY_W     = 119,
	KEY_A     = 97,
	KEY_S     = 115,
	KEY_D     = 100,
	KEY_LEFT  = 65361,
	KEY_RIGHT = 65363,
	KEY_ESC   = 65307,
	KEY_M     = 109,	// mouse activation
	KEY_R	  = 114		// show rays
}	t_key;

typedef enum e_color
{
	COLOR_BLACK   = 0x00000000,
	COLOR_WHITE   = 0x00FFFFFF,
	COLOR_RED     = 0x00FF0000,
	COLOR_GREEN   = 0x0000FF00,
	COLOR_BLUE    = 0x000000FF,
	COLOR_YELLOW  = 0x00FFFF00,
	COLOR_CYAN    = 0x0000FFFF,
	COLOR_MAGENTA = 0x00FF00FF,
	COLOR_GRAY    = 0x00222222
}	t_color;

#define MINIMAP_SCALE 0.25
#define MINIMAP_OFFSET_X 10
#define MINIMAP_OFFSET_Y 10

/* --- Image Structures (MLX) --- */
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* --- Main Structure --- */
typedef struct s_data {
	// MLX and Window (Person A)
	void	*mlx;
	void	*win;
	t_img	screen;

	// Player State (Person A)
	double	posX;				// Initial X coordinate
	double	posY;				// Initial Y coordinate
	
	double	dirX;				// Direction vector
	double	dirY;
	double	angle;   // position angle of the player throught the map

	double	planeX;		// Camera plane (for FOV)?
	double	planeY;

	double	fov;	// player FOV angle (rad)
	double	move_speed; // speed of the player
	double	rot_speed; // speed of rotation

	// related to moving with mouse
	int		mouse_enabled;
	double	mouse_sensitivity;
	int		win_center_x;
	int		win_center_y;

	// relativo ao mapa
	char	**map;		// Map matrix
	int		map_width;
	int		map_height;

	// activate and deactivate raycasting in minimap
	int	show_rays;
	/*
	// Parsing Data (Person B)
	char	*tex_path[4];		// Paths NO, SO, WE, EA [cite: 141]
	t_img	tex[4];				// Loaded textures
	int		floor_color;		// Floor color in Hexadecimal [cite: 161]
	int		ceiling_color;		// Ceiling color in Hexadecimal [cite: 168]*/
}	t_data;

/*
// --- Prototypes: Parsing (Person B) --- 
int		init_parser(t_data *data, char *file_path);
int		validate_map(t_data *data);
void	parse_error(char *message);	// Must print "Error\n" [cite: 190]

// --- Prototypes: Graphics Engine (Person A) --- 
int		init_window(t_data *data);
void	start_raycasting(t_data *data);
int		handle_keys(int keycode, t_data *data);
int		close_game(t_data *data);*/

/* Estruturas geométricas */
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_circle
{
	t_point	center;
	int		radius;
	int		color;
}	t_circle;

typedef struct s_line
{
	t_point	start;
	t_point	end;
	int		color;
}	t_line;

typedef struct s_square
{
	t_point	pos;
	int		size;
	int		color;
}	t_square;

typedef struct s_rect
{
	t_point	pos;
	int		width;
	int		height;
	int		color;
}	t_rect;

/* variables used in draw_line(), draw.c*/
typedef struct s_dda
{
	int		dx;		// distância horizontal total
	int		dy;		// distância vertical total
	int		steps;	// quantos pixels desenhar
	float	x;		// posição atual X
	float	y;		// posição atual Y
	float	x_inc;	// avanço em X por passo
	float	y_inc;	// avanço em Y por passo
	int		i;		// contador do loop
}	t_dda;

/*Essa struct guarda tudo o que o raio precisa saber para andar, raycast.c*/
typedef struct s_ray
{
	// Direção do raio (normalizado)
	// São as componentes do vetor direção do raio.
	double	ray_dir_x;
	double	ray_dir_y;

	// Posição atual do raio no mapa (em tiles)
	// A célula do mapa (data->map[y][x]) onde o raio está agora.
	int		map_x;
	int		map_y;

	// Distância para atravessar 1 tile (deltaDist)
	// Quanto o raio precisa andar (em distância real) para cruzar 1 
	// linha vertical ou 1 linha horizontal do grid.
	double	delta_dist_x;
	double	delta_dist_y;

	// Distância até a próxima borda do tile
	// Distância desde a posição atual do jogador até:
	double	side_dist_x; // a próxima linha vertical
	double	side_dist_y; // a próxima linha horizontal

	// Direção do passo no mapa
	// Dizem para qual lado o raio anda no grid.
	// +1 → direita / baixo
	// -1 → esquerda / cima
	int		step_x;
	int		step_y;

	// Indica qual tipo de parede foi atingida:
	int		side;        // 0 = vertical, 1 = horizontal
	// 0 → ainda não bateu
	// 1 → encontrou parede ('1')
	int		hit;

	// Distância perpendicular à parede
	// A distância real e corrigida do jogador até a parede.
	double	perp_wall_dist;

	// Ponto exato de impacto (em coordenadas do mundo)
	// O ponto exato onde o raio bateu na parede, em coordenadas do mundo (tiles).
	double	hit_x;
	double	hit_y;
}	t_ray;

/* draw.c */
void	draw_circle(t_img *img, t_circle *c);
void	draw_rect(t_img *img, t_rect *r);
void	draw_square(t_img *img, t_square *s);
void	draw_line(t_img *img, t_line *l);
void	draw_map(t_data *data);

/* hooks.c */
void	free_map(t_data *data);
int		close_window(t_data *data);
int		key_hook(int keycode, t_data *data);
int		mouse_move(int x, int y, t_data *data);

/* initialization.c */
void	init_mlx(t_data *data);
void	init_screen(t_data *data);
void	init_player(t_data *data);
void	init_mouse(t_data *data);
void	init_hooks(t_data *data);

/* raycast/raycast.c */
//void	cast_single_ray(t_data *data, double ray_angle, t_ray *ray);
void	cast_single_ray(t_data *data, t_ray *ray);
/* raycast/init_dda.c */
void	init_dda(t_data *data, t_ray *ray);

/* render.c */
int		render(t_data *data);
void	init_ray_from_dir(t_data *data, t_ray *ray);
//int		render(t_data *data);
void	render_3d_view(t_data *data);

/* utils.c */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	clear_screen(t_img *img);
void	set_player_direction(t_data *data, char c);
void	find_player(t_data *data);

/* --- Map Validation Prototypes --- */
int		validate_scene_file(const char *filename);
int		validate_map_file(const char *filename);
int		validate_map(char **map);
int		is_valid_map_char(char c);
int		is_map_closed(char **map);
int		count_player_positions(char **map);
int		is_player_char(char c);
int		is_line_map(const char *line);
//void	free_map(char **map);

#endif