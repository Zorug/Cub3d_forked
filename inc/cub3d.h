/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:23:20 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 21:54:32 by tnuno-mo         ###   ########.fr       */
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
# include <stdbool.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define TILE_SIZE 40

typedef enum e_key
{
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_ESC = 65307,
	KEY_M = 109,
	KEY_R = 114
}	t_key;

typedef enum e_color
{
	COLOR_BLACK = 0x00000000,
	COLOR_WHITE = 0x00FFFFFF,
	COLOR_RED = 0x00FF0000,
	COLOR_GREEN = 0x0000FF00,
	COLOR_BLUE = 0x000000FF,
	COLOR_YELLOW = 0x00FFFF00,
	COLOR_CYAN = 0x0000FFFF,
	COLOR_MAGENTA = 0x00FF00FF,
	COLOR_GRAY = 0x00222222
}	t_color;

# define MINIMAP_SCALE 0.25
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10

# define WALL_NORTH_COLOR 0x00FF5555
# define WALL_SOUTH_COLOR 0x0055FF55
# define WALL_WEST_COLOR 0x005555FF
# define WALL_EAST_COLOR 0x00FFFF55

# define CEILING_COLOR 0x0087CEEB
# define FLOOR_COLOR 0x00444444

# define MAP_WALL_COLOR 0x00222222
# define MAP_FLOOR_COLOR 0x00000000
# define MAP_PLAYER_COLOR 0x00FF0000
# define MAP_RAY_COLOR 0x00FFFF00

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

typedef enum e_wall_side
{
	WALL_NORTH,
	WALL_SOUTH,
	WALL_WEST,
	WALL_EAST
}	t_side;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	int		wall_side;
	int		hit;
	double	perp_wall_dist;
	double	hit_x;
	double	hit_y;
}	t_ray;

typedef struct s_scene_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	int		config_flags;
}	t_cfg;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	screen;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	angle;
	double	plane_x;
	double	plane_y;
	double	fov;
	double	move_speed;
	double	rot_speed;
	int		mouse_enabled;
	double	mouse_sensitivity;
	int		win_center_x;
	int		win_center_y;
	char	**map;
	int		map_width;
	int		map_height;
	int		show_rays;
	t_ray	*rays;
	int		rays_count;
	t_cfg	config;
	t_img	tex[4];
}	t_data;

# define FLAG_NO 1
# define FLAG_SO 2
# define FLAG_WE 4
# define FLAG_EA 8
# define FLAG_F 16
# define FLAG_C 32
# define FLAG_ALL 63

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

typedef struct s_rect
{
	t_point	pos;
	int		width;
	int		height;
	int		color;
}	t_rect;

typedef struct s_dda
{
	int		dx;
	int		dy;
	int		steps;
	float	x;
	float	y;
	float	x_inc;
	float	y_inc;
	int		i;
}	t_dda;

typedef struct s_wall_render
{
	int	line_height;
	int	wall_start;
	int	draw_start;
	int	draw_end;
}	t_wall_render;

/* draw.c */
void	draw_circle(t_img *img, t_circle *c);
void	draw_rect(t_img *img, t_rect *r);
void	draw_line(t_img *img, t_line *l);

/* hooks.c */
void	free_map(t_data *data);
int		close_window(t_data *data);
int		key_hook(int keycode, t_data *data);
int		mouse_move(int x, int y, t_data *data);
void	handle_movement(int keycode, t_data *data);
void	handle_rotation(int keycode, t_data *data);
void	rotate_view(t_data *data, double rot);
void	move_player(t_data *data, double move_x, double move_y);
int		is_walkable(t_data *data, double x, double y);

/* initialization.c */
int		init_mlx(t_data *data);
int		init_screen(t_data *data);
int		init_rays_cache(t_data *data);
void	init_player(t_data *data);
void	init_mouse(t_data *data);
int		cleanup_and_exit(t_data *data, int exit_code);
void	init_hooks(t_data *data);

/* raycast/raycast.c */
void	cast_single_ray(t_data *data, t_ray *ray);
void	perform_dda(t_data *data, t_ray *ray);
void	compute_perp_distance(t_data *data, t_ray *ray);
void	compute_hit_position(t_data *data, t_ray *ray);
void	determine_wall_side(t_ray *ray);
/* raycast/init_dda.c */
void	init_dda(t_data *data, t_ray *ray);
/* draw_minimap.c */
void	draw_ray_minimap(t_data *data, t_ray *ray);

/* render.c */
int		render(t_data *data);
void	init_ray_from_dir(t_data *data, t_ray *ray);
void	render_3d_view(t_data *data);
void	draw_minimap(t_data *data);
void	draw_player_minimap(t_data *data);
void	draw_minimap_rays(t_data *data);
int		get_texture_pixel(t_img *tex, int x, int y);
int		get_texture_x(t_ray *ray, int tex_width);
int		get_wall_color(t_data *data, t_ray *ray, int y, t_wall_render *wr);
void	init_wall_render(t_wall_render *wr, t_ray *ray, t_data *data);
void	draw_ceiling(t_data *data, int x, t_wall_render *wr);
void	draw_wall(t_data *data, int x, t_ray *ray, t_wall_render *wr);
void	draw_floor(t_data *data, int x, t_wall_render *wr);

/* utils.c */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	clear_screen(t_img *img);
void	set_player_direction(t_data *data, char c);
void	find_player(t_data *data);

/* --- Map Validation Prototypes --- */
int		validate_map(char **map);
int		is_valid_map_char(char c);
int		is_map_closed(char **map);
int		count_player_positions(char **map);
int		is_player_char(char c);
int		is_line_map(const char *line);

int		parse_scene_file(const char *filename, t_data *data);
int		validate_file_extension(const char *filename);
char	**read_file_lines(const char *filename);

int		parse_texture_line(char *line, t_cfg *cfg);
int		validate_texture_path(const char *path);
int		load_all_textures(t_data *data);

int		parse_color_line(char *line, t_cfg *cfg);
int		parse_rgb_values(const char *str, int *r, int *g, int *b);
int		rgb_to_hex(int r, int g, int b);

int		extract_and_validate_map(char **lines, int start_idx, t_data *data);
int		is_map_line(const char *line);
char	**copy_map_lines(char **lines, int start, int count);

char	*skip_whitespace(char *str);
int		is_empty_line(const char *line);
void	free_string_array(char **arr);
int		str_starts_with(const char *str, const char *prefix);

void	error_exit(t_data *data, const char *message);
int		error_return(const char *message);
void	free_scene_config(t_cfg *cfg);
#endif