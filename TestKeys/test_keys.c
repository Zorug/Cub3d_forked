#include "../minilibx-linux/mlx.h"
#include <stdio.h>

int	key_press(int keycode, void *param __attribute__((unused)))
{
	printf("Keycode: %d\n", keycode);
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, 260, 260, "Test the keys!");
	if (!win)
		return (1);
	mlx_key_hook(win, key_press, NULL);
	mlx_loop(mlx);
	return (0);
}
