/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:23:20 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 14:23:38 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	KEY_W	 = 119,
	KEY_A	 = 97,
	KEY_S	 = 115,
	KEY_D	 = 100,
	KEY_LEFT  = 65361,
	KEY_RIGHT = 65363,
	KEY_ESC   = 65307,
	KEY_M	 = 109,	// mouse activation
	KEY_R	  = 114		// show rays
}	t_key;

typedef enum e_color
{
	COLOR_BLACK   = 0x00000000,
	COLOR_WHITE   = 0x00FFFFFF,
	COLOR_RED	 = 0x00FF0000,
	COLOR_GREEN   = 0x0000FF00,
	COLOR_BLUE	= 0x000000FF,
	COLOR_YELLOW  = 0x00FFFF00,
	COLOR_CYAN	= 0x0000FFFF,
	COLOR_MAGENTA = 0x00FF00FF,
	COLOR_GRAY	= 0x00222222
}	t_color;

// teste
typedef enum e_wall_side
{
	WALL_NORTH,
	WALL_SOUTH,
	WALL_WEST,
	WALL_EAST
}	t_wall_side;

#define MINIMAP_SCALE 0.25
#define MINIMAP_OFFSET_X 10
#define MINIMAP_OFFSET_Y 10

/* ================= WALL DEBUG COLORS ================= */
# define WALL_NORTH_COLOR  0x00FF5555
# define WALL_SOUTH_COLOR  0x0055FF55
# define WALL_WEST_COLOR   0x005555FF
# define WALL_EAST_COLOR   0x00FFFF55

/* ================= FLOOR & CEILING ================= */
# define CEILING_COLOR  0x0087CEEB   // azul céu
# define FLOOR_COLOR	0x00444444   // cinza escuro

/* ================= MAP COLORS ================= */
# define MAP_WALL_COLOR	0x00222222
# define MAP_FLOOR_COLOR   0x00000000
# define MAP_PLAYER_COLOR  0x00FF0000
# define MAP_RAY_COLOR	 0x00FFFF00

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

/* ================= PARSING STRUCTURES ================= */
typedef struct s_scene_config
{
	char	*no_path;	  // North texture path
	char	*so_path;	  // South texture path
	char	*we_path;	  // West texture path
	char	*ea_path;	  // East texture path
	int		floor_color;   // Floor RGB in hex (0x00RRGGBB)
	int		ceiling_color; // Ceiling RGB in hex (0x00RRGGBB)
	int		config_flags;  // Bitmask: which elements are set
}	t_scene_config;

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
	int				show_rays;

	t_scene_config	config;		// Scene configuration
	t_img			tex[4];		// Loaded textures [NO, SO, WE, EA]
}	t_data;

// Config flags bitmask- serve para ver se os elementos estão configurados
# define FLAG_NO  (1 << 0)  // 0b000001
# define FLAG_SO  (1 << 1)  // 0b000010
# define FLAG_WE  (1 << 2)  // 0b000100
# define FLAG_EA  (1 << 3)  // 0b001000
# define FLAG_F   (1 << 4)  // 0b010000
# define FLAG_C   (1 << 5)  // 0b100000
# define FLAG_ALL (FLAG_NO | FLAG_SO | FLAG_WE | FLAG_EA | FLAG_F | FLAG_C)

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
	int		side;		// 0 = vertical, 1 = horizontal
	t_wall_side	wall_side;  // <-- NOVO
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
int		init_mlx(t_data *data);
int		init_screen(t_data *data);
void	init_player(t_data *data);
void	init_mouse(t_data *data);
void	init_hooks(t_data *data);

/* raycast/raycast.c */
void	cast_single_ray(t_data *data, t_ray *ray);
/* raycast/init_dda.c */
void	init_dda(t_data *data, t_ray *ray);
/* draw_minimap.c */
void	draw_ray_minimap(t_data *data, t_ray *ray);
void	draw_ray_debug(t_data *data, t_ray *ray);

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

// ================= PARSING FUNCTIONS =================
// parse_file.c
int		parse_scene_file(const char *filename, t_data *data);
int		validate_file_extension(const char *filename);
char	**read_file_lines(const char *filename);

// parse_textures.c
int		parse_texture_line(char *line, t_scene_config *cfg);
int		validate_texture_path(const char *path);
int		load_all_textures(t_data *data);

// parse_colors.c
int		parse_color_line(char *line, t_scene_config *cfg);
int		parse_rgb_values(const char *str, int *r, int *g, int *b);
int		rgb_to_hex(int r, int g, int b);

// parse_map.c
int		extract_and_validate_map(char **lines, int start_idx, t_data *data);
int		is_map_line(const char *line);
char	**copy_map_lines(char **lines, int start, int count);

// parse_utils.c
char	*skip_whitespace(char *str);
int		is_empty_line(const char *line);
void	free_string_array(char **arr);
int		str_starts_with(const char *str, const char *prefix);

// errors.c
void	error_exit(t_data *data, const char *message);
int	error_return(const char *message);
void	free_scene_config(t_scene_config *cfg);
#endif