typedef struct s_data {
	void	*mlx;			// MLX instance (A)
	void	*win;			// Window (A)
	char	**map;			// 2D map matrix (B)
	char	*tex_path[4];	// Paths NO, SO, WE, EA (B)
	int		f_color;		// Floor color in HEX (B)
	int		c_color;		// Ceiling color in HEX (B)
	double	posX, posY;		// Player position (A/B)
	double	dirX, dirY;		// Direction vector (A)
}	t_data;
