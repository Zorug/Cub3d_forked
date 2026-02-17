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
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

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

/*
	// Parsing Data (Person B)
	char	**map;				// Map matrix
	char	*tex_path[4];		// Paths NO, SO, WE, EA [cite: 141]
	t_img	tex[4];				// Loaded textures
	int		floor_color;		// Floor color in Hexadecimal [cite: 161]
	int		ceiling_color;		// Ceiling color in Hexadecimal [cite: 168]
	int		map_width;
	int		map_height;*/

	// Player State (Person A)
	double	posX;				// Initial X coordinate
	double	posY;				// Initial Y coordinate
	
	double	dirX;				// Direction vector
	double	dirY;
	double	angle;   // position angle of the player throught the map

	double	fov;	// player FOV angle (rad)
	double	move_speed; // speed of the player
	double	rot_speed; // speed of rotation
	//double	planeX;				// Camera plane (for FOV)
	//double	planeY;

	// relativo ao mapa
	char	**map;
	int		map_width;
	int		map_height;

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


/* draw.c */
//void	draw_circle(t_img *img, int cx, int cy, int radius, int color);
void	draw_circle(t_img *img, t_circle *c);
//void	draw_square(t_img *img, int x, int y, int size, int color);
void	draw_square(t_img *img, t_square *s);
//void	draw_line(t_img *img,
//	int x0, int y0, int x1, int y1, int color);
void	draw_line(t_img *img, t_line *l);
void	draw_map(t_data *data);

/* hooks.c */
int	close_window(t_data *data);
int	key_hook(int keycode, t_data *data);

/* raycast.c */
//void cast_single_ray(t_data *data);
void cast_single_ray(t_data *data, double rayAngle);

/* utils.c */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	clear_screen(t_img *img);

/* --- Map Validation Prototypes --- */
int		validate_scene_file(const char *filename);
int		validate_map_file(const char *filename);
int		validate_map(char **map);
int		is_valid_map_char(char c);
int		is_map_closed(char **map);
int		count_player_positions(char **map);
int		is_player_char(char c);
int		is_line_map(const char *line);
void	free_map(char **map);

#endif