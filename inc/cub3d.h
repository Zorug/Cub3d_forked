#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
//# include <mlx.h>
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* --- Key Definitions (Linux) --- */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

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
//	t_img	screen;
	t_img	img;

/*
	// Parsing Data (Person B)
	char	**map;				// Map matrix
	char	*tex_path[4];		// Paths NO, SO, WE, EA [cite: 141]
	t_img	tex[4];				// Loaded textures
	int		floor_color;		// Floor color in Hexadecimal [cite: 161]
	int		ceiling_color;		// Ceiling color in Hexadecimal [cite: 168]
	int		map_width;
	int		map_height;

	// Player State (Person A)
	double	posX;				// Initial X coordinate
	double	posY;				// Initial Y coordinate
	double	dirX;				// Direction vector
	double	dirY;
	double	planeX;				// Camera plane (for FOV)
	double	planeY;*/
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

#endif